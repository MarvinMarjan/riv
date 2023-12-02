#pragma once

#include <vector>

#include <expression/expression.h>



// creates an AST based on a sequence of tokens
class Parser
{
public:
	Parser(const std::vector<Token>& tokens);


	Expression* parse();


private:
	std::vector<Token> tokens_;

	size_t current_;


	Token peek()		const	noexcept;
	Token advance()				noexcept;
	Token previous()	const	noexcept;

	bool match(const std::initializer_list<TokenType>& tokens) noexcept;
	bool check(const TokenType type) const noexcept;
	bool at_end() const noexcept;


	Token consume(const TokenType type, const std::string& errmsg);


	Expression* expression();
	Expression* equality();
	Expression* comparison();
	Expression* term();
	Expression* factor();
	Expression* unary();
	Expression* primary();
};