#pragma once

#include <vector>



enum class TokenType;

struct Exception;
struct Token;

class Statement;
class Expression;
class IdentifierExpression;


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
	Statement* block_statement();
	Statement* print_statement();
	Statement* var_declaration();
	Statement* if_statement();
	Statement* while_statement();
	Statement* for_statement();
	Statement* loop_statement();



	Expression* expression();
	Expression* assignment();
	Expression* desugarize_assignment(IdentifierExpression* const identifier, const Token& assignment_operator, Expression* const value);
	Expression* equality();
	Expression* comparison();
	Expression* term();
	Expression* factor();
	Expression* unary();
	Expression* call();
	Expression* primary();


	// parses a block statement
	std::vector<Statement*> block();
	
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