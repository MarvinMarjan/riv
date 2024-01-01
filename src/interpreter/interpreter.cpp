#include <interpreter/interpreter.h>

#include <specter/output/ostream.h>

#include <language/error_codes.h>
#include <type/function.h>
#include <type/package.h>
#include <system/exception.h>
#include <system/sysstate.h>
#include <system/init.h>
#include <common/filesys.h>



Interpreter::Interpreter()
{
	environment = new Environment;
	global = environment;
}



void Interpreter::interpret(const std::vector<Statement*>& statements)
{
	try
	{
		for (Statement* const statement : statements)
			execute(statement);

		// do not execute the "main" function in import mode
		if (importing_)
			return;

		Type main_func = environment->get("main");

		if (!main_func.is_func())
			throw riv_e306(); // function "main" not declared

		main_func.as_func()->call(*this, {});
	}
	catch (const Exception& e)
	{
		log_error(e);
	}
}






// ************* Statements *************

void Interpreter::process_expression(ExpressionStatement& statement)
{
	evaluate(statement.expr);
}


void Interpreter::process_block(BlockStatement& statement)
{
	execute_block(statement.statements, ScopeConfig(environment, new Environment(environment)));
}


void Interpreter::process_print(PrintStatement& statement)
{
	sp::println(evaluate(statement.value).to_string());
}


void Interpreter::process_var(VarStatement& statement)
{
	Type value = evaluate(statement.value);
	value.set_mutability(statement.mutability);

	environment->declare(statement.name, value);
}


void Interpreter::process_if(IfStatement& statement)
{
	if (Type::truthy(evaluate(statement.condition)))
		execute(statement.then_statement);

	else if (statement.else_statement)
		execute(statement.else_statement);
}


void Interpreter::process_while(WhileStatement& statement)
{
	while (Type::truthy(evaluate(statement.condition)))
	{
		try
		{
			execute(statement.body);
		}
		catch (const BreakStatement::Signal&)
		{
			break;
		}
		catch (const ContinueStatement::Signal&)
		{
			continue;
		}
	}
}


void Interpreter::process_break(BreakStatement&)
{
	throw BreakStatement::Signal();
}


void Interpreter::process_continue(ContinueStatement&)
{
	throw ContinueStatement::Signal();
}


void Interpreter::process_function(FunctionStatement& statement)
{
	Type object = new RivFunction(statement, nullptr);

	object.set_mutability(statement.mutability);


	environment->declare(statement.name, object);
	environment->data_[statement.name.lexeme].value.as_func()->closure = environment;
}


void Interpreter::process_return(ReturnStatement& statement)
{
	throw RivFunction::ReturnSignal(evaluate(statement.value));
}


void Interpreter::process_import(ImportStatement& statement)
{

	const std::filesystem::path path = get_path_from_import_symbols(statement.symbols);

	if (std::filesystem::is_directory(path))
		import_dir(path);

	else if (path.extension() == ".riv")
		import_file(path);

	else if (path.extension() == ".so")
		import_lib(path);

//	std::filesystem::current_path(sys_state().absolute_source_path_parent);
}


void Interpreter::process_package(PackageStatement& statement)
{
	Environment* old_env = environment;
	Environment* new_env = new Environment(old_env);

	environment = new_env;

	for (Statement* const declaration : statement.declarations)
		execute(declaration);

	environment = old_env;

	environment->declare(statement.name, new RivPackage(new_env));
}


void Interpreter::execute_block(const std::vector<Statement*>& statements, const ScopeConfig& config)
{
	Environment* const old_env = config.old_env;
	Environment* const new_env = config.new_env;

	environment = new_env;

	try
	{
		for (Statement* const statement : statements)
			execute(statement);
	}
	catch (const RivFunction::ReturnSignal& signal)
	{
		// make sure to recover the old environment
		environment = old_env;
		throw signal;
	}

	// delete the inner scope at end
	delete new_env;

	environment = old_env;
}






// ************* Expressions *************

Type Interpreter::process_binary(BinaryExpression& expr)
{
	const Type left  = evaluate(expr.left);
	const Type right = evaluate(expr.right);

	switch (expr.op.type)
	{
		// x + y
	case TokenType::Plus:
		if (are_values_of_type({ left, right }, TypeIndex::Number))
			return left.as_num() + right.as_num();

		if (are_values_of_type({ left, right }, TypeIndex::String))
			return left.as_str() + right.as_str();

		// x - y
	case TokenType::Minus: throw_if_type_differs({ left, right }, TypeIndex::Number, riv_e300({ left, right }, expr.op));
		return left.as_num() - right.as_num();

		// x * y
	case TokenType::Star: throw_if_type_differs({ left, right }, TypeIndex::Number, riv_e300({ left, right }, expr.op));
		return left.as_num() * right.as_num();

		// x / y
	case TokenType::Slash: throw_if_type_differs({ left, right }, TypeIndex::Number, riv_e300({ left, right }, expr.op));
		return left.as_num() / right.as_num();



		// x > y
	case TokenType::Greater:
		if (are_values_of_type({ left, right }, TypeIndex::Number))
			return left.as_num() > right.as_num();

		if (are_values_of_type({ left, right }, TypeIndex::String))
			return left.as_str().size() > right.as_str().size();

		// x < y
	case TokenType::Lesser:
		if (are_values_of_type({ left, right }, TypeIndex::Number))
			return left.as_num() < right.as_num();

		if (are_values_of_type({ left, right }, TypeIndex::String))
			return left.as_str().size() < right.as_str().size();

		// x >= y
	case TokenType::GreaterEqual:
		if (are_values_of_type({ left, right }, TypeIndex::Number))
			return left.as_num() >= right.as_num();

		if (are_values_of_type({ left, right }, TypeIndex::String))
			return left.as_str().size() >= right.as_str().size();

		// x <= y
	case TokenType::LesserEqual:
		if (are_values_of_type({ left, right }, TypeIndex::Number))
			return left.as_num() <= right.as_num();

		if (are_values_of_type({ left, right }, TypeIndex::String))
			return left.as_str().size() <= right.as_str().size();



		// x == y
	case TokenType::EqualEqual: return Type::equals(left, right);

		// x != y
	case TokenType::BangEqual: return !Type::equals(left, right);
	}

	return {};
}


Type Interpreter::process_unary(UnaryExpression& expr)
{
	const Type right = evaluate(expr.right);

	switch (expr.op.type)
	{
		// -x
	case TokenType::Minus: throw_if_type_differs({ right }, TypeIndex::Number, riv_e300({ right }, expr.op));
		return -right.as_num();

		// !x
	case TokenType::Bang: return !Type::truthy(right);
	}

	return {};
}


Type Interpreter::process_grouping(GroupingExpression& expr)
{
	return evaluate(expr.expr);
}


Type Interpreter::process_literal(LiteralExpression& expr)
{
	return expr.value;
}


Type Interpreter::process_literal_array(LiteralArrayExpression& expr)
{
	ArrayType array;

	for (Expression* const expression : expr.array)
		array.push_back(evaluate(expression));

	return array;
}


Type Interpreter::process_indexing(IndexingExpression& expr)
{
	const Type value = evaluate(expr.expression);

	if (!value.is_array() && !value.is_str())
		throw riv_e312(expr.brace.pos); // only arrays or string can be indexed

	const Type index = evaluate(expr.index);

	if (!index.is_num())
		throw riv_e313(expr.brace.pos); // expect number as index

	const bool is_array = value.is_array();

	const int int_index = (int)index.as_num();
	const int int_size  = (int)(is_array ? value.as_array().size() : value.as_str().size());

	if (int_index < 0 || int_index >= int_size)
		throw riv_e314(expr.brace.pos); // index out of range

	return is_array ? value.as_array().at(int_index) : std::string(1, value.as_str().at(int_index));
}


Type Interpreter::process_identifier(IdentifierExpression& expr)
{
	const Type value = environment->get(expr.token);

	if (value.is_non_assignable())
		throw riv_e308(expr.token.pos, value.as_non_assignable()->type_name()); // invalid non-assignable type "..."

	return value;
}


Type Interpreter::process_assignment(AssignmentExpression& expr)
{
	IdentifierExpression       * identifier_expression = nullptr;
	PackageResolutionExpression* package_expression    = nullptr;
	IndexingExpression         * indexing_expression   = nullptr;


	// variable assignment
	if ((identifier_expression = dynamic_cast<IdentifierExpression*>(expr.identifier)))
		return assign_variable(identifier_expression->token, evaluate(expr.value));

		// package member assignment
	else if ((package_expression = dynamic_cast<PackageResolutionExpression*>(expr.identifier)))
		return assign_package_member(expr, package_expression);

	else if ((indexing_expression = dynamic_cast<IndexingExpression*>(expr.identifier)))
		return assign_array_item(expr, indexing_expression);

	throw riv_e309(expr.op.pos); // only variables can be assigned
}


Type Interpreter::process_call(CallExpression& expr)
{
	Type callee = evaluate(expr.callee);

	if (!callee.is_func() && !callee.is_symbol())
		throw riv_e302(expr.paren.pos); // only functions can be called

	std::vector<Type> arguments;

	for (Expression* const arg : expr.arguments)
		arguments.push_back(evaluate(arg));


	// calling

	if (callee.is_func())
		return call_function(callee, arguments, expr.paren.pos);

	else if (callee.is_symbol())
		return call_symbol(callee, arguments, expr.paren.pos);
}


Type Interpreter::process_package_resolution(PackageResolutionExpression& expr)
{
	const Type              package_object = get_package_object_from_expression(expr);
	const RivPackage* const package        = package_object.as_package();

	return package->environment->get(expr.identifier);
}


Type Interpreter::process_ternary(TernaryExpression& expr)
{
	if (evaluate(expr.condition).as_bool())
		return evaluate(expr.left);
	else
		return evaluate(expr.right);
}


Type Interpreter::evaluate(Expression* const expr)
{
	if (!expr)
		return {};

	return expr->process(*this);
}






// ************* Statement Utilities *************


std::filesystem::path Interpreter::get_path_from_import_symbols(const std::vector<Token>& symbols) const
{
	std::filesystem::path path;
	const std::vector<std::string> import_paths = sys_state().import_paths;

	// only append the import path once
	bool import_path_has_used = false;

	for (const Token& token : symbols)
	{
		path /= token.lexeme;

		if (path_exists(path))
			continue;

		// is there any import path?
		if (!import_paths.empty() && !import_path_has_used)
		{
			for (const std::string& import_path : import_paths)
			{
				// todo: make this work
				sp::println("path: ", (import_path / path).string());
				sp::println("current: ", std::filesystem::current_path().string());

				if (path_exists(import_path / path))
				{
					import_path_has_used = true;
					break;
				}
			}
		}

		else
			throw riv_e304(token.pos); // invalid import symbol
	}

	return path;
}


void Interpreter::import_file(const std::string& path) noexcept
{
	const SystemState old = sys_state();

	init_state_using_srcfile(path, old.argc, old.argv);

	Interpreter interpreter;
	interpreter.importing_ = true; // interpret with import mode

	interpreter.interpret(parse(scan(sys_state().strsource)));

	environment->import(interpreter.environment->data());

	init_state_using_copy(old);
}


void Interpreter::import_dir(const std::string& path) noexcept
{
	for (const auto& file : std::filesystem::directory_iterator(path))
		import_file(file.path().string());
}


void Interpreter::import_lib(const std::string& path) noexcept
{
	// add the lib to the global scope
	global->import(load_library(path.c_str()));
}






// ************* Expression Utilities *************

Type Interpreter::assign_variable(const Token& identifier, const Type& value)
{
	environment->assign(identifier, value);
	return value;
}


Type Interpreter::assign_package_member(AssignmentExpression& assignment_expression, PackageResolutionExpression* const package_expression)
{
	RivPackage* const package = get_package_object_from_expression(*package_expression).as_package();

	const Type value = evaluate(assignment_expression.value);
	package->environment->assign(package_expression->identifier, value);

	return value;
}


Type Interpreter::assign_array_item(AssignmentExpression& assignment_expression, IndexingExpression* const indexing)
{
	IdentifierExpression* identifier = nullptr;

	if (!(identifier = dynamic_cast<IdentifierExpression*>(indexing->expression)))
		throw riv_e309(assignment_expression.op.pos);

	const Type array = evaluate(identifier);

	if (!array.is_array())
		throw riv_e312(indexing->brace.pos); // only arrays can be indexed

	const Type index = evaluate(indexing->index);

	if (!index.is_num())
		throw riv_e313(indexing->brace.pos); // expect number as array index

	const ArrayType array_type = array.as_array();
	const int int_index = (int)index.as_num();

	if (int_index < 0 || int_index >= (int)array_type.size())
		throw riv_e314(indexing->brace.pos); // index out of range

	const Type evaluated_value = evaluate(assignment_expression.value);

	environment->data_[identifier->token.lexeme].value.as_array().at(int_index) = evaluated_value;

	return evaluated_value;
}


Type Interpreter::get_package_object_from_expression(PackageResolutionExpression& package_expression)
{
	IdentifierExpression* const identifier = dynamic_cast<IdentifierExpression*>(package_expression.object);

	if (!identifier)
		throw riv_e307(package_expression.op.pos); // expect package at left of "::"

	// note: do not use Interpreter::process_identifier to get packages
	const Type type_object = environment->get(identifier->token);

	if (!type_object.is_package())
		throw riv_e307(package_expression.op.pos); // expect package at left of "::"

	return type_object;
}




Type Interpreter::call_function(Type& callee, const std::vector<Type>& arguments, const TokenPosition& paren_pos)
{
	RivFunction* func = callee.as_func();

	const int arity = (int)func->arity();
	const int argc  = (int)arguments.size();

	if (arity != argc)
		throw riv_e303(arity, argc, paren_pos); // expect ... arguments, got ...

	return func->call(*this, arguments);
}


Type Interpreter::call_symbol(Type& callee, const std::vector<Type>& arguments, const TokenPosition& paren_pos)
{
	LibSymbol symbol = callee.as_symbol();

	const int arity = (int)lib_get_arity_from_symbol(symbol.lib, symbol.name);
	const int argc  = (int)arguments.size();

	if (arity != argc)
		throw riv_e303(arity, argc, paren_pos);

	APICallData data = new_call_data();

	data.args = type_objs_to_api_type_array(arguments);

	// call it
	symbol.symbol(&data);

	return api_type_to_type_obj(data.return_value);
}






bool Interpreter::are_values_of_type(const std::initializer_list<Type>& values, const TypeIndex type) noexcept
{
	for (const Type& value : values)
		if (!value.is_typeof(type))
			return false;

	return true;
}


void Interpreter::throw_if_type_differs(const std::initializer_list<Type>& values, const TypeIndex type, const Exception& err)
{
	if (!are_values_of_type(values, type))
		throw err;
}