#include <statement/statement.h>



ExpressionStatement::ExpressionStatement(Expression* const expr)
{
	this->expr = expr;
}


PrintStatement::PrintStatement(Expression* const value)
{
	this->value = value;
}


VarStatement::VarStatement(const Token& name, Expression* const value)
{
	this->name = name;
	this->value = value;
}