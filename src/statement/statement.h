#pragma once

#include <vector>

#include <scanner/token.h>



class Expression;


class ExpressionStatement;
class BlockStatement;
class PrintStatement;
class VarStatement;
class IfStatement;
class WhileStatement;


class StatementProcessor
{
public:
	virtual void process_expression	(ExpressionStatement&)	= 0;
	virtual void process_block		(BlockStatement&)		= 0;
	virtual void process_print		(PrintStatement&)		= 0;
	virtual void process_var		(VarStatement&)			= 0;
	virtual void process_if			(IfStatement&)			= 0;
	virtual void process_while		(WhileStatement&)		= 0;
};




class Statement
{
public:
	virtual void process(StatementProcessor&) = 0;
};





class ExpressionStatement : public Statement
{
public:
	ExpressionStatement(Expression* const expr);


	void process(StatementProcessor& processor) override {
		processor.process_expression(*this);
	}


	Expression* expr = nullptr;
};




class BlockStatement : public Statement
{
public:
	BlockStatement(const std::vector<Statement*>& statements);


	void process(StatementProcessor& processor) override {
		processor.process_block(*this);
	}


	std::vector<Statement*> statements;
};




class PrintStatement : public Statement
{
public:
	PrintStatement(Expression* const value);


	void process(StatementProcessor& processor) override {
		processor.process_print(*this);
	}


	Expression* value = nullptr;
};




class VarStatement : public Statement
{
public:
	VarStatement(const Token& name, Expression* const value);


	void process(StatementProcessor& processor) override {
		processor.process_var(*this);
	}


	Token		name;
	Expression*	value = nullptr;
};




class IfStatement : public Statement
{
public:
	IfStatement(Expression* const condition, Statement* const then_statement, Statement* const else_statement);


	void process(StatementProcessor& processor) {
		processor.process_if(*this);
	}


	Expression*	condition = nullptr;
	Statement*	then_statement = nullptr;
	Statement*	else_statement = nullptr;
};




class WhileStatement : public Statement
{
public:
	WhileStatement(Expression* const condition, Statement* const body);


	void process(StatementProcessor& processor) {
		processor.process_while(*this);
	}


	Expression*	condition = nullptr;
	Statement*	body = nullptr;
};