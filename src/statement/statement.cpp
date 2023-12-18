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


VarStatement::VarStatement(const Token& name, Expression* const value, const Type::Mutability mutability)
{
	this->name = name;
	this->value = value;
	this->mutability = mutability;
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


FunctionStatement::FunctionStatement(const Token& name, const std::vector<Token>& params, const std::vector<Statement*>& body)
{
	this->name = name;
	this->params = params;
	this->body = body;
}


ReturnStatement::ReturnStatement(Expression* const value)
{
	this->value = value;
}


ImportStatement::ImportStatement(const Token& path)
{
	this->path = path;
}


PackageStatement::PackageStatement(const Token &name, const std::vector<Statement*>& declarations)
{
	this->name = name;
	this->declarations = declarations;
}