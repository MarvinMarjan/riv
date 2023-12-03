#include <interpreter/interpreter.h>

#include <language/error_codes.h>
#include <system/exception.h>



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






void Interpreter::process_print(PrintStatement& statement)
{
	sp::println(evaluate(statement.value).to_string());
}


void Interpreter::process_expression(ExpressionStatement& statement)
{
	evaluate(statement.expr);
}






Type Interpreter::process_binary(BinaryExpression& expr)
{
	const Type left = evaluate(expr.left);
	const Type right = evaluate(expr.right);

	switch (expr.op.type)
	{
	case TokenType::Plus:
		if (are_values_of_type({ left, right }, TypeIndex::Number))
			return left.as_num() + right.as_num();
		
		if (are_values_of_type({ left, right }, TypeIndex::String))
			return left.as_str() + right.as_str();

	case TokenType::Minus:
		throw_if_type_differs({ left, right }, TypeIndex::Number, riv_e201({ left, right }, expr.op));
		return left.as_num() - right.as_num();

	case TokenType::Star:
		throw_if_type_differs({ left, right }, TypeIndex::Number, riv_e201({ left, right }, expr.op));
		return left.as_num() * right.as_num();

	case TokenType::Slash:
		throw_if_type_differs({ left, right }, TypeIndex::Number, riv_e201({ left, right }, expr.op));
		return left.as_num() / right.as_num();



	case TokenType::Greater:
		if (are_values_of_type({ left, right }, TypeIndex::Number))
			return left.as_num() > right.as_num();
	
		if (are_values_of_type({ left, right }, TypeIndex::String))
			return left.as_str().size() > right.as_str().size();

	case TokenType::Lesser:
		if (are_values_of_type({ left, right }, TypeIndex::Number))
			return left.as_num() < right.as_num();
	
		if (are_values_of_type({ left, right }, TypeIndex::String))
			return left.as_str().size() < right.as_str().size();

	case TokenType::GreaterEqual:
		if (are_values_of_type({ left, right }, TypeIndex::Number))
			return left.as_num() >= right.as_num();
	
		if (are_values_of_type({ left, right }, TypeIndex::String))
			return left.as_str().size() >= right.as_str().size();

	case TokenType::LesserEqual:
		if (are_values_of_type({ left, right }, TypeIndex::Number))
			return left.as_num() <= right.as_num();
	
		if (are_values_of_type({ left, right }, TypeIndex::String))
			return left.as_str().size() <= right.as_str().size();


	
	case TokenType::EqualEqual:
		return equals(left, right);

	case TokenType::BangEqual:
		return !equals(left, right);
	}
}


Type Interpreter::process_unary(UnaryExpression& expr)
{
	const Type right = evaluate(expr.right);

	switch (expr.op.type)
	{
	case TokenType::Minus:
		throw_if_type_differs({ right }, TypeIndex::Number, riv_e201({ right }, expr.op));
		return !right.as_num();

	case TokenType::Bang:
		throw_if_type_differs({ right }, TypeIndex::Bool, riv_e201({ right }, expr.op));
		return !truthy(right);
	}
}


Type Interpreter::process_grouping(GroupingExpression& expr)
{
	return evaluate(expr.expr);
}


Type Interpreter::process_literal(LiteralExpression& expr)
{
	return expr.value;
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