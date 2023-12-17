#pragma once

#include <expression/expression.h>



class ExprPrinter : public ExpressionProcessor
{
public:
	std::string print(Expression* const expr) noexcept {
		if (!expr) return {};
		return expr->process(*this).as_str();
	}


private:

	// stringifies an expression
	Type parenthesize(const std::initializer_list<Expression* const>& exprs, const std::string& op) noexcept;



	Type process_binary(BinaryExpression& expr) override {
		return parenthesize({ expr.left, expr.right }, expr.op.lexeme);
	}


	Type process_unary(UnaryExpression& expr) override {
		return parenthesize({ expr.right }, expr.op.lexeme);
	}


	Type process_grouping(GroupingExpression& expr) override {
		return parenthesize({ expr.expr }, "group");
	}


	Type process_literal(LiteralExpression& expr) override {
		return expr.value.to_string();
	}
};