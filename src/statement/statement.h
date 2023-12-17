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
class BreakStatement;
class ContinueStatement;
class FunctionStatement;
class ReturnStatement;
class ImportStatement;
class PackageStatement;


class StatementProcessor
{
public:
	virtual void process_expression	(ExpressionStatement&)	= 0;
	virtual void process_block		(BlockStatement&)		= 0;
	virtual void process_print		(PrintStatement&)		= 0;
	virtual void process_var		(VarStatement&)			= 0;
	virtual void process_if			(IfStatement&)			= 0;
	virtual void process_while		(WhileStatement&)		= 0;
	virtual void process_break		(BreakStatement&)		= 0;
	virtual void process_continue	(ContinueStatement&)	= 0;
	virtual void process_function	(FunctionStatement&) 	= 0;
	virtual void process_return		(ReturnStatement&) 		= 0;
	virtual void process_import		(ImportStatement&)		= 0;
	virtual void process_package	(PackageStatement&)		= 0;
};




class Statement
{
public:
	virtual void process(StatementProcessor&) = 0;
};





// expression ";"
class ExpressionStatement : public Statement
{
public:
	explicit ExpressionStatement(Expression* expr);


	void process(StatementProcessor& processor) override {
		processor.process_expression(*this);
	}


	Expression* expr = nullptr;
};




// "{" statements* "}"
class BlockStatement : public Statement
{
public:
	explicit BlockStatement(const std::vector<Statement*>& statements);


	void process(StatementProcessor& processor) override {
		processor.process_block(*this);
	}


	std::vector<Statement*> statements;
};




// "print" expression ";"
class PrintStatement : public Statement
{
public:
	explicit PrintStatement(Expression* value);


	void process(StatementProcessor& processor) override {
		processor.process_print(*this);
	}


	Expression* value = nullptr;
};




// "var" <name> ("=" expression)? ";"
class VarStatement : public Statement
{
public:
	VarStatement(const Token& name, Expression* value);


	void process(StatementProcessor& processor) override {
		processor.process_var(*this);
	}


	Token		name;
	Expression*	value = nullptr;
};




// "if" "(" expression ")" then_statement ("else" else_statement)?
class IfStatement : public Statement
{
public:
	IfStatement(Expression* condition, Statement* then_statement, Statement* else_statement);


	void process(StatementProcessor& processor) override {
		processor.process_if(*this);
	}


	Expression*	condition = nullptr;
	Statement*	then_statement = nullptr;
	Statement*	else_statement = nullptr;
};




// "while" "(" expression ")" statement
class WhileStatement : public Statement
{
public:
	WhileStatement(Expression* condition, Statement* body);


	void process(StatementProcessor& processor) override {
		processor.process_while(*this);
	}


	Expression*	condition = nullptr;
	Statement*	body = nullptr;
};




// "break" ";"
class BreakStatement : public Statement
{
public:
	struct Signal {};


	BreakStatement() = default;

	void process(StatementProcessor& processor) override {
		processor.process_break(*this);
	}
};

// "continue" ";"
class ContinueStatement : public Statement
{
public:
	struct Signal {};


	ContinueStatement() = default;

	void process(StatementProcessor& processor) override {
		processor.process_continue(*this);
	}
};




// "function" <name> "(" <params>* ")" "{" statement* "}"
class FunctionStatement : public Statement
{
public:
	FunctionStatement() = default;
	FunctionStatement(const Token& name, const std::vector<Token>& params, const std::vector<Statement*>& body);


	void process(StatementProcessor& processor) override {
		processor.process_function(*this);
	}


	Token					name;
	std::vector<Token>		params;
	std::vector<Statement*>	body;
};




// "return" expression? ";"
class ReturnStatement : public Statement
{
public:
	explicit ReturnStatement(Expression* value);


	void process(StatementProcessor& processor) override {
		processor.process_return(*this);
	}


	Expression* value = nullptr;
};




class ImportStatement : public Statement
{
public:
	explicit ImportStatement(const Token& path);


	void process(StatementProcessor& processor) override {
		processor.process_import(*this);
	}


	Token path;
};




class PackageStatement : public Statement
{
public:
	PackageStatement(const Token& name, const std::vector<Statement*>& declarations);


	void process(StatementProcessor& processor) override {
		processor.process_package(*this);
	}


	Token name;
	std::vector<Statement*> declarations;
};