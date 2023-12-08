#pragma once

#include <vector>

#include <scanner/token.h>



class BinaryExpression;
class UnaryExpression;
class GroupingExpression;
class LiteralExpression;
class IdentifierExpression;
class AssignmentExpression;
class CallExpression;


// visitor pattern
class ExpressionProcessor
{
public:
	virtual Type process_binary		(BinaryExpression&)		= 0;
	virtual Type process_unary		(UnaryExpression&)		= 0;
	virtual Type process_grouping	(GroupingExpression&)	= 0;
	virtual Type process_literal	(LiteralExpression&)	= 0;
	virtual Type process_identifier	(IdentifierExpression&)	= 0;
	virtual Type process_assignment	(AssignmentExpression&)	= 0;
	virtual Type process_call		(CallExpression&)		= 0;
};




class Expression
{
public:
	virtual Type process(ExpressionProcessor&) = 0;
};





// two-operands expression
class BinaryExpression : public Expression
{
public:
	BinaryExpression(Expression* const left, const Token& op, Expression* const right);


	Type process(ExpressionProcessor& processor) override {
		return processor.process_binary(*this);
	}


	Expression* left = nullptr;
	Token 		op;
	Expression* right = nullptr;
};




// single-operand expression
class UnaryExpression : public Expression
{
public:
	UnaryExpression(const Token& op, Expression* const right);


	Type process(ExpressionProcessor& processor) override {
		return processor.process_unary(*this);
	}


	Token 		op;
	Expression* right = nullptr;
};




// increase an expression precedence
class GroupingExpression : public Expression
{
public:
	GroupingExpression(Expression* const expr);


	Type process(ExpressionProcessor& processor) override {
		return processor.process_grouping(*this);
	}


	Expression* expr = nullptr;
};




// literal values: numbers, strings, booleans...
class LiteralExpression : public Expression
{
public:
	LiteralExpression(const Type& value = Type());


	Type process(ExpressionProcessor& processor) override {
		return processor.process_literal(*this);
	}


	Type value;
};




// references the value of an identifier
class IdentifierExpression : public Expression
{
public:
	IdentifierExpression(const Token& token);


	Type process(ExpressionProcessor& processor) override {
		return processor.process_identifier(*this);
	}


	Token token;
};




class CallExpression : public Expression
{
public:
	CallExpression(Expression* const callee, const Token& paren, const std::vector<Expression*>& arguments);


	Type process(ExpressionProcessor& processor) override {
		return processor.process_call(*this);
	}


	Expression*					callee;
	Token						paren;
	std::vector<Expression*>	arguments;
};




// assigns a value to identifier
class AssignmentExpression : public Expression
{
public:
	AssignmentExpression(const Token& identifier, Expression* const value);


	Type process(ExpressionProcessor& processor) override {
		return processor.process_assignment(*this);
	}


	Token		identifier;
	Expression* value = nullptr;
};