#pragma once

#include <vector>

#include <statement/statement.h>



class Exception;


// interpret statements
class Interpreter : public ExpressionProcessor, public StatementProcessor
{
public:
	Interpreter() = default;

	void interpret(const std::vector<Statement*>& statements);


private:
	void process_print		(PrintStatement&)		override;
	void process_expression	(ExpressionStatement&)	override;

	void execute(Statement* const statement) {
		statement->process(*this);
	}



	Type process_binary		(BinaryExpression&)		override;
	Type process_unary		(UnaryExpression&)		override;
	Type process_grouping	(GroupingExpression&)	override;
	Type process_literal	(LiteralExpression&)	override;

	Type evaluate(Expression* expr) {
		return expr->process(*this);
	}



	static bool equals(const Type& left, const Type& right) noexcept;
	static bool truthy(const Type& value) noexcept;

	static bool are_values_of_type(const std::initializer_list<Type>& values, const TypeIndex type) noexcept;

	static void throw_if_type_differs(const std::initializer_list<Type>& values, const TypeIndex type, const Exception& err);
};