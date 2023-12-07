#include <parser/parser.h>

#include <language/error_codes.h>
#include <system/exception.h>
#include <statement/statement.h>
#include <expression/expression.h>



Parser::Parser(const std::vector<Token>& tokens)
{
	tokens_ = tokens;
	current_ = 0;
}


std::vector<Statement*> Parser::parse()
{
	std::vector<Statement*> statements;

	while (!at_end())
		statements.push_back(declaration());

	return statements;
}






Statement* Parser::declaration()
{
	try
	{
		if (match({ TokenType::Var }))
			return var_declaration();

		return statement();
	}
	catch (const Exception& e)
	{
		log_error(e);
		synchronize();
		return nullptr;
	}
}


Statement* Parser::statement()
{
	if (match({ TokenType::LeftCurlyBrace }))
		return block_statement();

	if (match({ TokenType::Print }))
		return print_statement();

	if (match({ TokenType::If }))
		return if_statement();

	if (match({ TokenType::While }))
		return while_statement();

	if (match({ TokenType::For }))
		return for_statement();

	return expression_statement();	
}


Statement* Parser::expression_statement()
{
	Expression* expression = this->expression();
	consume(TokenType::SemiColon, riv_e202(previous().pos)); // expect ";" after statement
	return new ExpressionStatement(expression);
}


Statement* Parser::block_statement()
{
	return new BlockStatement(block());
}


Statement* Parser::print_statement()
{
	Expression* value = expression();
	consume(TokenType::SemiColon, riv_e202(previous().pos)); // expect ";" after statement
	return new PrintStatement(value);
}


Statement* Parser::var_declaration()
{
	Token name = consume(TokenType::Identifier, riv_e203(previous().pos)); // expect variable name after "var"
	Expression* value = nullptr;

	if (match({ TokenType::Equal }))
		value = expression();

	consume(TokenType::SemiColon, riv_e202(previous().pos)); // expect ";" after statement

	return new VarStatement(name, value);
}


Statement* Parser::if_statement()
{
	consume(TokenType::LeftParen, riv_e206(previous().pos)); // expect "(" after "if" statement
	Expression* const condition = expression();
	consume(TokenType::RightParen, riv_e207(previous().pos)); // expect ")" after "if" condition

	Statement* then_statement = statement();
	Statement* else_statement = nullptr;

	if (match({ TokenType::Else }))
		else_statement = statement();

	return new IfStatement(condition, then_statement, else_statement);
}


Statement* Parser::while_statement()
{
	consume(TokenType::LeftParen, riv_e208(previous().pos)); // expect "(" after "while" statement
	Expression* const condition = expression();
	consume(TokenType::RightParen, riv_e209(previous().pos)); // expect ")" after "while" condition

	Statement* statement = this->statement();

	return new WhileStatement(condition, statement);
}


#include <specter/output/ostream.h>


Statement* Parser::for_statement()
{
	consume(TokenType::LeftParen, riv_e210(previous().pos)); // expect "(" after "for" statement


	// initializer

	Statement* initializer;

	if (match({ TokenType::SemiColon }))
		initializer = nullptr;

	else if (match({ TokenType::Var }))
		initializer = var_declaration();

	else
		initializer = expression_statement();


	// condition

	Expression* condition = nullptr;

	if (!check(TokenType::SemiColon))
		condition = expression();

	consume(TokenType::SemiColon, riv_e211(previous().pos)); // expect ";" after "for" condition


	// increment
	
	Expression* increment = nullptr;

	if (!check(TokenType::RightParen))
		increment = expression();

	consume(TokenType::RightParen, riv_e212(previous().pos)); // expect ")" after "for" increment


	// statement

	Statement* body = this->statement();


	// desugarization

	if (increment)
		body = new BlockStatement({ body, new ExpressionStatement(increment) });

	if (!condition)
		condition = new LiteralExpression(true);

	body = new WhileStatement(condition, body);

	if (initializer)
		body = new BlockStatement({ initializer, body });

	// { initializer, While(condition, { ..., increment }) }
	return body;
}






Expression* Parser::expression()
{
	return assignment();
}


Expression* Parser::assignment()
{
	Expression* expr = equality();

	if (match({ TokenType::Equal, TokenType::PlusEqual, TokenType::MinusEqual, TokenType::StarEqual, TokenType::SlashEqual }))
	{
		IdentifierExpression* const identifier = dynamic_cast<IdentifierExpression*>(expr);
		const Token equal = previous();

		// it's not a identifier
		if (!identifier)
			throw riv_e204(equal.pos); // only variables can be assigned

		Expression* value = assignment();
		
		// +=, -=, *=, ...
		if (equal.type != TokenType::Equal)
			value = desugarize_assignment(identifier, equal, value);

		return new AssignmentExpression(identifier->token, value);
	}

	return expr;
}


Expression* Parser::desugarize_assignment(IdentifierExpression* const identifier, const Token& assignment_operator, Expression* const value)
{
	Token op = assignment_operator;

	switch (op.type)
	{
	case TokenType::PlusEqual:
		op.type = TokenType::Plus;
		break;

	case TokenType::MinusEqual:
		op.type = TokenType::Minus;
		break;

	case TokenType::StarEqual:
		op.type = TokenType::Star;
		break;

	case TokenType::SlashEqual:
		op.type = TokenType::Slash;
		break;
	}

	// right value must have higher precedence
	return new BinaryExpression(identifier, op, new GroupingExpression(value));
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

	return call();
}


Expression* Parser::call()
{
	Expression* expression = primary();

	return expression;
}


Expression* Parser::primary()
{
	if (match({ TokenType::String, TokenType::Number, TokenType::Bool, TokenType::Null }))
		return new LiteralExpression(previous().value);

	if (match({ TokenType::Identifier }))
		return new IdentifierExpression(previous());

	if (match({ TokenType::LeftParen }))
	{
		Expression* expr = expression();
		consume(TokenType::RightParen, riv_e201(peek().pos)); // expect ')' to close grouping expression
		return new GroupingExpression(expr);
	}

	throw riv_e200(previous().pos); // expression expected
}





std::vector<Statement*> Parser::block()
{
	std::vector<Statement*> statements;

	while (!check(TokenType::RightCurlyBrace) && !at_end())
		statements.push_back(declaration());

	consume(TokenType::RightCurlyBrace, riv_e205(previous().pos));

	return statements;
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
		case TokenType::Var:
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
	for (const TokenType token_type : tokens)
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