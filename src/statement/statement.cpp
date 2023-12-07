#include <statement/statement.h>



ExpressionStatement::ExpressionStatement(Expression* const expr)
{
	this->expr = expr;
}


BlockStatement::BlockStatement(const std::vector<Statement*>& statements)
{
	this->statements = statements;
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


IfStatement::IfStatement(Expression* const condition, Statement* const then_statement, Statement* const else_statement)
{
	this->condition = condition;
	this->then_statement = then_statement;
	this->else_statement = else_statement;
}


WhileStatement::WhileStatement(Expression* const condition, Statement* const body)
{
	this->condition = condition;
	this->body = body;
}