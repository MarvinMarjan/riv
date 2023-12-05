#pragma once

#include <vector>

#include <expression/expression.h>



struct Exception;

class Statement;


// creates an AST based on a sequence of tokens
class Parser
{
public:
	Parser(const std::vector<Token>& tokens);


	std::vector<Statement*> parse();


private:
	Statement* declaration();
	Statement* statement();
	Statement* expression_statement();
	Statement* print_statement();
	Statement* var_declaration();



	Expression* expression();
	Expression* assignment();
	Expression* equality();
	Expression* comparison();
	Expression* term();
	Expression* factor();
	Expression* unary();
	Expression* call();
	Expression* primary();


	void synchronize() noexcept;


	Token peek()		const	noexcept;
	Token advance()				noexcept;
	Token previous()	const	noexcept;

	bool match(const std::initializer_list<TokenType>& tokens) noexcept;
	bool check(const TokenType type) const noexcept;
	bool at_end() const noexcept;


	Token consume(const TokenType type, const Exception& err);




	std::vector<Token> tokens_;

	size_t current_;
};