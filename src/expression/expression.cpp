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


LiteralArrayExpression::LiteralArrayExpression(const std::vector<Expression*>& array)
{
	this->array = array;
}


IndexingExpression::IndexingExpression(Expression* const array, Expression* const index, const Token& brace)
{
	this->array = array;
	this->index = index;
	this->brace = brace;
}


IdentifierExpression::IdentifierExpression(const Token& token)
{
	this->token = token;
}


AssignmentExpression::AssignmentExpression(Expression* const identifier, const Token& op, Expression* const value)
{
	this->identifier = identifier;
	this->op = op;
	this->value = value;
}


CallExpression::CallExpression(Expression* const callee, const Token& paren, const std::vector<Expression*>& arguments)
{
	this->callee = callee;
	this->paren = paren;
	this->arguments = arguments;
}


PackageResolutionExpression::PackageResolutionExpression(Expression *object, const Token &identifier, const Token& op)
{
	this->object = object;
	this->identifier = identifier;
	this->op = op;
}


TernaryExpression::TernaryExpression(Expression* const condition, Expression* const left, Expression* const right)
{
	this->condition = condition;
	this->left = left;
	this->right = right;
}