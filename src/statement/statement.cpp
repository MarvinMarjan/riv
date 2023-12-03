#include <statement/statement.h>



ExpressionStatement::ExpressionStatement(Expression* const expr)
{
	this->expr = expr;
}


PrintStatement::PrintStatement(Expression* const value)
{
	this->value = value;
}