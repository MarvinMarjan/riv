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
	explicit Parser(const std::vector<Token>& tokens);


	std::vector<Statement*> parse();


private:
	Statement* declaration(bool force_declaration = false);
	Statement* statement();
	Statement* expression_statement();
	Statement* block_statement();
	Statement* print_statement();
	Statement* var_statement();
	Statement* if_statement();
	Statement* while_statement();
	Statement* for_statement();
	Statement* loop_statement();
	Statement* break_statement();
	Statement* continue_statement();
	Statement* function_statement();
	Statement* return_statement();
	Statement* import_statement();
	Statement* package_statement();



	Expression* expression();
	Expression* assignment();
	Expression* desugarize_assignment(Expression* identifier, const Token& assignment_operator, Expression* value);
	Expression* equality();
	Expression* comparison();
	Expression* term();
	Expression* factor();
	Expression* unary();
	Expression* call();
	Expression* finish_call(Expression* expr);
	Expression* primary();





	// parses a block statement
	std::vector<Statement*> block(bool force_declaration = false);
	
	void synchronize() noexcept;


	Token peek()					const	noexcept;
	Token advance()							noexcept;
	Token previous(int amount = 1)	const	noexcept;

	bool match(const std::initializer_list<TokenType>& tokens) noexcept;
	bool check(TokenType type) const noexcept;
	bool at_end() const noexcept;


	Token consume(TokenType type, const Exception& err);


	bool at_global_scope() const noexcept { return !scope_depth_; }


	int loop_depth_ = 0;
	int function_depth_ = 0;
	int scope_depth_ = 0;


	std::vector<Token> tokens_;

	size_t current_;
};