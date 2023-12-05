#include <parser/parser.h>

#include <language/error_codes.h>
#include <system/exception.h>
#include <statement/statement.h>



Parser::Parser(const std::vector<Token>& tokens)
{
	tokens_ = tokens;
	current_ = 0;
}


std::vector<Statement*> Parser::parse()
{
	std::vector<Statement*> statements;

	while (!at_end())
		statements.push_back(statement());

	return statements;
}






Statement* Parser::statement()
{
	try
	{
		if (match({ TokenType::Print }))
			return print_statement();

		return expression_statement();
	}
	catch (const Exception& e)
	{
		log_error(e);
		synchronize();
		return nullptr;
	}
}


Statement* Parser::print_statement()
{
	Expression* value = expression();
	consume(TokenType::SemiColon, riv_e202(previous().pos));
	return new PrintStatement(value);
}


Statement* Parser::expression_statement()
{
	Expression* expression = this->expression();
	consume(TokenType::SemiColon, riv_e202(previous().pos));
	return new ExpressionStatement(expression);
}






Expression* Parser::expression()
{
	return equality();
}


Expression* Parser::equality()
{
	Expression* expr = comparison();

	while (match({ TokenType::EqualEqual, TokenType::BangEqual }))
	{
		const Token op = previous();
		Expression* right = comparison();
		expr = new BinaryExpression(expr, op, right);
	}

	return expr;
}


Expression* Parser::comparison()
{
	Expression* expr = term();

	while (match({ TokenType::Greater, TokenType::Lesser, TokenType::GreaterEqual, TokenType::LesserEqual }))
	{
		const Token op = previous();
		Expression* right = term();
		expr = new BinaryExpression(expr, op, right);
	}

	return expr;
}


Expression* Parser::term()
{
	Expression* expr = factor();

	while (match({ TokenType::Plus, TokenType::Minus }))
	{
		const Token op = previous();
		Expression* right = factor();
		expr = new BinaryExpression(expr, op, right);
	}

	return expr;
}


Expression* Parser::factor()
{
	Expression* expr = unary();

	while (match({ TokenType::Star, TokenType::Slash }))
	{
		const Token op = previous();
		Expression* right = unary();
		expr = new BinaryExpression(expr, op, right);
	}

	return expr;
}


Expression* Parser::unary()
{
	if (match({ TokenType::Minus, TokenType::Bang }))
	{
		const Token op = previous();
		Expression* right = unary();
		return new UnaryExpression(op, right);
	}

	return primary();
}


Expression* Parser::primary()
{
	if (match({ TokenType::String, TokenType::Number, TokenType::Bool, TokenType::Null })) return new LiteralExpression(previous().value);

	if (match({ TokenType::LeftParen }))
	{
		Expression* expr = expression();
		consume(TokenType::RightParen, riv_e201(peek().pos)); // expect ')' to close grouping expression
		return new GroupingExpression(expr);
	}

	throw riv_e200(peek().pos); // expression expected
}





void Parser::synchronize() noexcept
{
	advance();

	while (!at_end())
	{
		if (previous().type == TokenType::SemiColon)
			return;

		switch (peek().type)
		{
		case TokenType::Print:
			return;
		}

		advance();
	}
}





Token Parser::peek() const noexcept
{
	return tokens_[(at_end()) ? current_ - 1 : current_];
}


Token Parser::advance() noexcept
{
	if (!at_end())
		current_++;

	return previous();
}


Token Parser::previous() const noexcept
{
	return tokens_[current_ - 1];
}



bool Parser::match(const std::initializer_list<TokenType>& tokens) noexcept
{
	for (const TokenType token_type: tokens)
		if (check(token_type))
		{
			advance();
			return true;
		}
	
	return false;
}


bool Parser::check(const TokenType type) const noexcept
{
	if (at_end())
		return false;

	return peek().type == type;
}


bool Parser::at_end() const noexcept
{
	return current_ >= tokens_.size();
}



Token Parser::consume(const TokenType type, const Exception& err)
{
	if (check(type))
		return advance();

	throw err;
}