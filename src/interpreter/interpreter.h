#pragma once

#include <expression/expression.h>



class Exception;


// interpret statements
class Interpreter : public ExpressionProcessor
{
public:
	Interpreter() = default;

	Type interpret(Expression* expr);


private:
	Type evaluate(Expression* expr) {
		return expr->process(*this);
	}

	Type process_binary		(BinaryExpression&);
	Type process_unary		(UnaryExpression&);
	Type process_grouping	(GroupingExpression&);
	Type process_literal	(LiteralExpression&);


	static bool equals(const Type& left, const Type& right) noexcept;
	static bool truthy(const Type& value) noexcept;

	static bool are_values_of_type(const std::initializer_list<Type>& values, const TypeIndex type) noexcept;

	static void throw_if_type_differs(const std::initializer_list<Type>& values, const TypeIndex type, const Exception& err);
};