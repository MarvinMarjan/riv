#include <scanner/scanner.h>



Scanner::Scanner(const std::string& source)
{
	source_ = source;
	line_ = 0;
	begin_ = end_ = 0;
}



std::vector<Token> Scanner::scan()
{
	tokens_.clear();
	
	while (!at_end())
	{
		begin_ = current_;
		scan_token();
	}

	return tokens_;
}



void Scanner::scan_token()
{
	const char ch = advance();

	switch (ch)
	{
	case ' ':
	case '\t':
		break;

	case '\n':
		line_++;
		break;

	case '+': add_token(TokenType::Plus); break;
	case '-': add_token(TokenType::Minus); break;
	case '*': add_token(TokenType::Star); break;
	case '/': add_token(TokenType::Slash); break;

	case '>': match('=') ? add_token(TokenType::GreaterEqual)	: add_token(TokenType::Greater); break;
	case '<': match('=') ? add_token(TokenType::LesserEqual)	: add_token(TokenType::Lesser); break;
	case '=': match('=') ? add_token(TokenType::EqualEqual)		: add_token(TokenType::Equal); break;
	case '!': match('=') ? add_token(TokenType::BangEqual)		: add_token(TokenType::Bang); break;

	case '(': add_token(TokenType::LeftParen); break;
	case ')': add_token(TokenType::RightParen); break;
	case '[': add_token(TokenType::LeftBrace); break;
	case ']': add_token(TokenType::RightBrace); break;
	case '{': add_token(TokenType::LeftCurlyBrace); break;
	case '}': add_token(TokenType::RightCurlyBrace); break;

	case ';': add_token(TokenType::SemiColon); break;
	case '.': add_token(TokenType::Dot); break;
	case ',': add_token(TokenType::Comma); break;

	
	}
}



bool Scanner::at_end() const noexcept
{
	return current_ >= source_.size();
}


char Scanner::advance() noexcept
{
	if (at_end())
		return '\0';

	return source_[current_++];
}


char Scanner::peek() const noexcept
{
	return source_[current_];
}


char Scanner::peek_next() const noexcept
{
	if (current_ + 1 >= source_.size())
		return '\0';

	return source_[current_ + 1];
}



bool Scanner::match(const char next) noexcept
{
	if (at_end()) return false;
    if (peek() != next) return false;

    current_++;
    return true;
}