#include <interpreter/interpreter.h>

#include <specter/output/ostream.h>

#include <language/error_codes.h>
#include <system/exception.h>
#include <type/function.h>
#include <system/debug.h>



void Interpreter::interpret(const std::vector<Statement*>& statements)
{
	try {
		for (Statement* const statement : statements)
			execute(statement);	
	}
	catch (const Exception& e)
	{
		log_error(e);
	}
}






void Interpreter::process_expression(ExpressionStatement& statement)
{
	evaluate(statement.expr);
}


void Interpreter::process_block(BlockStatement& statement)
{
	execute_block(statement.statements, ScopeConfig(environment, Environment(), true));
}


void Interpreter::process_print(PrintStatement& statement)
{
	sp::println(evaluate(statement.value).to_string());
}


void Interpreter::process_var(VarStatement& statement)
{
	environment.declare(statement.name.lexeme, evaluate(statement.value));
}


void Interpreter::process_if(IfStatement& statement)
{
	if (truthy(evaluate(statement.condition)))
		execute(statement.then_statement);

	else if (statement.else_statement)
		execute(statement.else_statement);
}


void Interpreter::process_while(WhileStatement& statement)
{
	while (truthy(evaluate(statement.condition)))
	{
		try {
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
	environment.declare(statement.name.lexeme, new RivFunction(statement));
}


void Interpreter::process_return(ReturnStatement& statement)
{
	throw RivFunction::ReturnSignal(evaluate(statement.value));
}




void Interpreter::execute_block(const std::vector<Statement*>& statements, const ScopeConfig& config)
{
	Environment old_env = std::move(config.old_env);
	Environment new_env = std::move(config.new_env);

	if (config.enclose_old)
		new_env.set_enclosing(&old_env);

	environment = std::move(new_env);

	for (Statement* const statement : statements)
		execute(statement);

	environment = std::move(old_env);
}





Type Interpreter::process_binary(BinaryExpression& expr)
{
	const Type left = evaluate(expr.left);
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
	case TokenType::Minus:
		throw_if_type_differs({ left, right }, TypeIndex::Number, riv_e300({ left, right }, expr.op));
		return left.as_num() - right.as_num();

	// x * y
	case TokenType::Star:
		throw_if_type_differs({ left, right }, TypeIndex::Number, riv_e300({ left, right }, expr.op));
		return left.as_num() * right.as_num();

	// x / y
	case TokenType::Slash:
		throw_if_type_differs({ left, right }, TypeIndex::Number, riv_e300({ left, right }, expr.op));
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
	case TokenType::EqualEqual:
		return equals(left, right);

	// x != y
	case TokenType::BangEqual:
		return !equals(left, right);
	}

	return Type();
}


Type Interpreter::process_unary(UnaryExpression& expr)
{
	const Type right = evaluate(expr.right);

	switch (expr.op.type)
	{
	// -x
	case TokenType::Minus:
		throw_if_type_differs({ right }, TypeIndex::Number, riv_e300({ right }, expr.op));
		return -right.as_num();

	// !x
	case TokenType::Bang:
		return !truthy(right);
	}

	return Type();
}


Type Interpreter::process_grouping(GroupingExpression& expr)
{
	return evaluate(expr.expr);
}


Type Interpreter::process_literal(LiteralExpression& expr)
{
	return expr.value;
}


Type Interpreter::process_identifier(IdentifierExpression& expr)
{
	return environment.get(expr.token);
}


// x = y
Type Interpreter::process_assignment(AssignmentExpression& expr)
{
	const Type value = evaluate(expr.value);
	environment.assign(expr.identifier, value);
	return value;
}


Type Interpreter::process_call(CallExpression& expr)
{
	Type callee = evaluate(expr.callee);

	if (!callee.is_func())
		throw riv_e302(expr.paren.pos); // only functions can be called

	std::vector<Type> arguments;

	for (Expression* const arg : expr.arguments)
		arguments.push_back(evaluate(arg));

	RivFunction* func = callee.as_func();

	if (func->arity() != arguments.size())
		throw riv_e303(func->arity(), arguments.size(), expr.paren.pos); // expect ... arguments, got ...

	return func->call(*this, arguments);
}



Type Interpreter::evaluate(Expression* const expr)
{
	if (!expr)
		return Type();

	return expr->process(*this);
}






bool Interpreter::equals(const Type& left, const Type& right) noexcept
{
	if (left.is_null() && right.is_null())
		return true;
	
	if (left.is_null())
		return false;

	return left == right;
}



bool Interpreter::truthy(const Type& value) noexcept
{
	if (value.is_null())
		return false;

	if (value.is_num())
		return value.as_num();

	if (value.is_bool())
		return value.as_bool();

	return true;
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