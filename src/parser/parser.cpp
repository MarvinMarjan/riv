#include <parser/parser.h>

#include <language/error_codes.h>
#include <system/exception.h>
#include <statement/statement.h>
#include <expression/expression.h>
#include <common/vector.h>
#include <language/riv.h>



Parser::Parser(const std::vector<Token>& tokens)
{
	tokens_  = tokens;
	current_ = 0;
}


std::vector<Statement*> Parser::parse()
{
	std::vector<Statement*> statements;

	while (!at_end())
	{
		Statement* const statement = declaration(true);

		// if it's not valid, jump
		if (!statement)
		{
			advance();
			continue;
		}

		statements.push_back(statement);
	}

	return statements;
}






// ************* Statements *************

Statement* Parser::declaration(const bool force_declaration)
{
	try
	{
		if (match({ TokenType::Var }))
			return var_statement();

		if (match({ TokenType::Function }))
			return function_statement();

		if (match({ TokenType::Package }))
			return package_statement();

		if (match({ TokenType::Import }))
			return import_statement();


		if (!force_declaration)
			return statement();

		else if (!exists(lang_modifiers(), peek().type))
			throw riv_e222(peek().pos); // expect declaration statement
	}
	catch (const Exception& e)
	{
		log_error(e);
		synchronize();
	}

	return nullptr;
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

	if (match({ TokenType::Loop }))
		return loop_statement();

	if (match({ TokenType::Break }))
		return break_statement();

	if (match({ TokenType::Continue }))
		return continue_statement();

	if (match({ TokenType::Return }))
		return return_statement();

	// is it modifier? (then ignore)
	if (exists(lang_modifiers(), peek().type))
		return nullptr;

	return expression_statement();
}


Statement* Parser::expression_statement()
{
	Expression* const expression = this->expression();
	consume(TokenType::SemiColon, riv_e202(peek().pos)); // expect ";" after statement
	return new ExpressionStatement(expression);
}


Statement* Parser::block_statement()
{
	return new BlockStatement(block());
}


Statement* Parser::print_statement()
{
	Expression* const value = expression();
	consume(TokenType::SemiColon, riv_e202(peek().pos)); // expect ";" after statement
	return new PrintStatement(value);
}


Statement* Parser::var_statement()
{
	// mutable by default
	const Type::Mutability mutability = Type::get_mutability_from_modifier(previous(2).type, Type::Mutable);

	const Token name = consume(TokenType::Identifier, riv_e203(peek().pos)); // expect variable name after "var"
	Expression* value = nullptr;

	if (match({ TokenType::Equal }))
		value = expression();

	consume(TokenType::SemiColon, riv_e202(peek().pos)); // expect ";" after statement

	return new VarStatement(name, value, mutability);
}


Statement* Parser::if_statement()
{
	consume(TokenType::LeftParen, riv_e205(peek().pos)); // expect "(" after "if" statement
	Expression* const condition = expression();
	consume(TokenType::RightParen, riv_e206(peek().pos)); // expect ")" after "if" condition

	Statement* const then_statement = statement();
	Statement*       else_statement = nullptr;

	if (match({ TokenType::Else }))
		else_statement = statement();

	return new IfStatement(condition, then_statement, else_statement);
}


Statement* Parser::while_statement()
{
	consume(TokenType::LeftParen, riv_e207(peek().pos)); // expect "(" after "while" statement
	Expression* const condition = expression();
	consume(TokenType::RightParen, riv_e208(peek().pos)); // expect ")" after "while" condition

	loop_depth_++;
	Statement* const statement = this->statement();
	loop_depth_--;

	return new WhileStatement(condition, statement);
}


Statement* Parser::for_statement()
{
	consume(TokenType::LeftParen, riv_e209(peek().pos)); // expect "(" after "for" statement


	// initializer

	Statement* initializer;

	if (match({ TokenType::SemiColon }))
		initializer = nullptr;

	else if (match({ TokenType::Var }))
		initializer = var_statement();

	else
		initializer = expression_statement();


	// condition

	Expression* condition = nullptr;

	if (!check(TokenType::SemiColon))
		condition = expression();

	consume(TokenType::SemiColon, riv_e210(peek().pos)); // expect ";" after "for" condition


	// increment
	
	Expression* increment = nullptr;

	if (!check(TokenType::RightParen))
		increment = expression();

	consume(TokenType::RightParen, riv_e211(peek().pos)); // expect ")" after "for" increment


	// statement

	loop_depth_++;
	Statement* body = this->statement();
	loop_depth_--;


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


Statement* Parser::loop_statement()
{
	loop_depth_++;
	Statement* const body = statement();
	loop_depth_--;

	return new WhileStatement(new LiteralExpression(true), body);
}


Statement* Parser::break_statement()
{
	if (!loop_depth_)
		throw riv_e212(previous().pos);

	consume(TokenType::SemiColon, riv_e202(peek().pos)); // expect ";" after statement
	return new BreakStatement;
}


Statement* Parser::continue_statement()
{
	if (!loop_depth_)
		throw riv_e213(peek().pos);

	consume(TokenType::SemiColon, riv_e202(peek().pos)); // expect ";" after statement
	return new ContinueStatement;
}


Statement* Parser::function_statement()
{
	// immutable by default
	const Type::Mutability mutability = Type::get_mutability_from_modifier(previous(2).type, Type::Immutable);

	const Token name = consume(TokenType::Identifier, riv_e214(peek().pos)); // expect function name after "function" statement


	// parameter list

	consume(TokenType::LeftParen, riv_e215(peek().pos)); // expect "(" after function name

	std::vector<Token> params;

	if (check(TokenType::Identifier))
		do {
			params.push_back(consume(TokenType::Identifier, riv_e217(peek().pos))); // expect parameter after ","
		} while(match({ TokenType::Comma })); 
	
	consume(TokenType::RightParen, riv_e216(peek().pos)); // expect ")" after parameter list


	// body

	consume(TokenType::LeftCurlyBrace, riv_e218(peek().pos)); // expect function body


	function_depth_++;
	const std::vector<Statement*> body = block();
	function_depth_--;


	return new FunctionStatement(name, params, body, mutability);
}


Statement* Parser::return_statement()
{
	if (!function_depth_)
		throw riv_e220(previous().pos); // cannot use "return" statement outside a function

	Expression* value = nullptr;

	if (!check(TokenType::SemiColon))
		value = expression();

	consume(TokenType::SemiColon, riv_e202(peek().pos)); // expect ";" after statement
	return new ReturnStatement(value);
}


Statement* Parser::import_statement()
{
	const Token path = consume(TokenType::String, riv_e221(peek().pos)); // expect module path string after "import" statement
	consume(TokenType::SemiColon, riv_e202(peek().pos)); // expect ";" after statement
	return new ImportStatement(path);
}


Statement* Parser::package_statement()
{
	const Token name = consume(TokenType::Identifier, riv_e223(peek().pos)); // expect package name

	consume(TokenType::LeftCurlyBrace, riv_e224(peek().pos)); // expect package body
	const std::vector<Statement*> declarations = block(true);

	return new PackageStatement(name, declarations);
}






// ************* Expressions *************

Expression* Parser::expression()
{
	return ternary();
}


Expression* Parser::ternary()
{
	Expression* expr = assignment(); // condition

	if (match({ TokenType::QuestionMark }))
	{
		Expression* left = ternary();

		if (!match({ TokenType::Else }))
			throw riv_e226(peek().pos);

		Expression* right = ternary();

		return new TernaryExpression(expr, left, right);
	}

	return expr;
}


Expression* Parser::assignment()
{
	Expression* expr = equality();

	if (match({ TokenType::Equal, TokenType::PlusEqual, TokenType::MinusEqual, TokenType::StarEqual, TokenType::SlashEqual }))
	{
		const Token equal = previous();

		Expression* value = assignment();

		// +=, -=, *=, ...
		if (equal.type != TokenType::Equal)
			value = desugarize_assignment(expr, equal, value);

		return new AssignmentExpression(expr, equal, value);
	}

	return expr;
}


Expression* Parser::equality()
{
	Expression* expr = comparison();

	while (match({ TokenType::EqualEqual, TokenType::BangEqual }))
	{
		const Token       op = previous();
		Expression* const right = comparison();
		expr = new BinaryExpression(expr, op, right);
	}

	return expr;
}


Expression* Parser::comparison()
{
	Expression* expr = term();

	while (match({ TokenType::Greater, TokenType::Lesser, TokenType::GreaterEqual, TokenType::LesserEqual }))
	{
		const Token       op = previous();
		Expression* const right = term();
		expr = new BinaryExpression(expr, op, right);
	}

	return expr;
}


Expression* Parser::term()
{
	Expression* expr = factor();

	while (match({ TokenType::Plus, TokenType::Minus }))
	{
		const Token       op = previous();
		Expression* const right = factor();
		expr = new BinaryExpression(expr, op, right);
	}

	return expr;
}


Expression* Parser::factor()
{
	Expression* expr = unary();

	while (match({ TokenType::Star, TokenType::Slash }))
	{
		const Token       op = previous();
		Expression* const right = unary();
		expr = new BinaryExpression(expr, op, right);
	}

	return expr;
}


Expression* Parser::unary()
{
	if (match({ TokenType::Minus, TokenType::Bang }))
	{
		const Token       op = previous();
		Expression* const right = unary();
		return new UnaryExpression(op, right);
	}

	return call();
}


Expression* Parser::call()
{
	Expression* expr = primary();

	while (true)
	{
		if (match({ TokenType::LeftParen }))
			expr = finish_function_call(expr);

		else if (match({ TokenType::ColonColon }))
			expr = finish_package_resolution(expr);

		else if (match({ TokenType::LeftBrace }))
			expr = finish_indexing(expr);

		else if (match({ TokenType::Colon }))
			expr = desugarize_argument_simplification(expr);

		else
			break;
	}

	return expr;
}


Expression* Parser::primary()
{
	if (match({ TokenType::String, TokenType::Number, TokenType::Bool, TokenType::Null }))
		return new LiteralExpression(previous().value);

	if (match({ TokenType::LeftBrace }))
		return new LiteralArrayExpression(array());

	if (match({ TokenType::Identifier }))
		return new IdentifierExpression(previous());

	if (match({ TokenType::LeftParen }))
	{
		Expression* expr = expression();
		consume(TokenType::RightParen, riv_e201(peek().pos)); // expect ")" to close grouping expression
		return new GroupingExpression(expr);
	}

	throw riv_e200(peek().pos); // expression expected
}






// ************* Statement Utilities *************

std::vector<Statement*> Parser::block(const bool force_declaration)
{
	std::vector<Statement*> statements;

	// entered into a block, increase scope meter
	scope_depth_++;

	while (!check(TokenType::RightCurlyBrace) && !at_end())
	{
		Statement* const statement = declaration(force_declaration);

		// if invalid, skip
		if (!statement)
			continue;

		statements.push_back(statement);
	}

	// decrease on exit
	scope_depth_--;

	consume(TokenType::RightCurlyBrace, riv_e204(peek().pos));

	return statements;
}






// ************* Expression Utilities *************

Expression* Parser::desugarize_assignment(Expression* const identifier, const Token& assignment_operator, Expression* const value)
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


Expression* Parser::finish_function_call(Expression* const left)
{
	const Token paren = previous();
	std::vector<Expression*> arguments;

	if (!check(TokenType::RightParen))
		do {
			arguments.push_back(expression());
		} while (match({ TokenType::Comma }));

	consume(TokenType::RightParen, riv_e219(peek().pos)); // expect ")" after function arguments

	return new CallExpression(left, paren, arguments);
}


Expression* Parser::finish_package_resolution(Expression* const left)
{
	const Token op = previous();
	const Token identifier = consume(TokenType::Identifier, riv_e225(peek().pos));

	return new PackageResolutionExpression(left, identifier, op);
}


Expression* Parser::finish_indexing(Expression* const left)
{
	const Token brace = previous();
	Expression* const index = expression();
	consume(TokenType::RightBrace, riv_e228(peek().pos));

	return new IndexingExpression(left, index, brace);
}


Expression* Parser::desugarize_argument_simplification(Expression* const left)
{
	const Token op = previous();
	Expression* const right = expression();

	CallExpression* call_expression;

	if (!(call_expression = dynamic_cast<CallExpression*>(right)))
		throw riv_e229(op.pos);

	call_expression->arguments.insert(call_expression->arguments.cbegin(), left);

	return call_expression;
}


std::vector<Expression*> Parser::array()
{
	std::vector<Expression*> array;

	if (!check(TokenType::RightBrace))
		do {
			array.push_back(expression());
		} while (match({ TokenType::Comma }));

	consume(TokenType::RightBrace, riv_e227(peek().pos)); // expect "]" to close array

	return array;
}






// ************* Parsing Utilities *************

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
		case TokenType::Mut:
		case TokenType::Imut:
		case TokenType::If:
		case TokenType::Else:
		case TokenType::While:
		case TokenType::For:
		case TokenType::Loop:
		case TokenType::Break:
		case TokenType::Continue:
		case TokenType::Function:
		case TokenType::Return:
		case TokenType::Import:
		case TokenType::Package:
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


Token Parser::previous(const int amount) const noexcept
{
	if ((int)current_ < amount)
		return tokens_[current_];

	return tokens_[current_ - amount];
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