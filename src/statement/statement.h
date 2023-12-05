#pragma once

#include <expression/expression.h>



class ExpressionStatement;
class PrintStatement;
class VarStatement;


class StatementProcessor
{
public:
	virtual void process_expression	(ExpressionStatement&)	= 0;
	virtual void process_print		(PrintStatement&)		= 0;
	virtual void process_var		(VarStatement&)			= 0;
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