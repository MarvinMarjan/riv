#include <expression/expression.h>



BinaryExpression::BinaryExpression(Expression* const left, const Token& op, Expression* const right)
{
	this->left = left;
	this->op = op;
	this->right = right;
}


UnaryExpression::UnaryExpression(const Token& op, Expression* const right)
{
	this->op = op;
	this->right = right;
}


GroupingExpression::GroupingExpression(Expression* const expr)
{
	this->expr = expr;
}


LiteralExpression::LiteralExpression(const Type& value)
{
	this->value = value;
}