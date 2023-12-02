#include <interpreter/interpreter.h>

#include <system/exception.h>



Type Interpreter::interpret(Expression* expr)
{
	try {
		return evaluate(expr);	
	}
	catch (const Exception& e)
	{
		log_error(e);
		return Type();
	}
}




Type Interpreter::process_binary(BinaryExpression& expr)
{
	const Type left = evaluate(expr.left);
	const Type right = evaluate(expr.right);

	switch (expr.op.type)
	{
	case TokenType::Plus:
		throw_if_type_differs({ left, right }, TypeIndex::Number, expr.op);
		return left.as_num() + right.as_num();

	case TokenType::Minus:
		throw_if_type_differs({ left, right }, TypeIndex::Number, expr.op);
		return left.as_num() - right.as_num();

	case TokenType::Star:
		throw_if_type_differs({ left, right }, TypeIndex::Number, expr.op);
		return left.as_num() * right.as_num();

	case TokenType::Slash:
		throw_if_type_differs({ left, right }, TypeIndex::Number, expr.op);
		return left.as_num() / right.as_num();



	case TokenType::Greater:
		throw_if_type_differs({ left, right }, TypeIndex::Number, expr.op);
		return left.as_num() > right.as_num();
	
	case TokenType::Lesser:
		throw_if_type_differs({ left, right }, TypeIndex::Number, expr.op);
		return left.as_num() < right.as_num();

	case TokenType::GreaterEqual:
		throw_if_type_differs({ left, right }, TypeIndex::Number, expr.op);
		return left.as_num() >= right.as_num();

	case TokenType::LesserEqual:
		throw_if_type_differs({ left, right }, TypeIndex::Number, expr.op);
		return left.as_num() <= right.as_num();


	
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
		throw_if_type_differs({ right }, TypeIndex::Number, expr.op);
		return !right.as_num();

	case TokenType::Bang:
		throw_if_type_differs({ right }, TypeIndex::Bool, expr.op);
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



void Interpreter::throw_if_type_differs(const std::initializer_list<Type>& values, const TypeIndex type, const Token& op)
{
	for (const Type& value : values)
		if (!value.is_typeof(type))
			throw Exception("Expect " + type_index_to_string(type) + " value.", op.pos);


// improve exception throwing
//	throw Exception("Operator '" + op.lexeme + "' doesn't support the following types: " + type_index_to_string(type) + " value.", op.pos);

}