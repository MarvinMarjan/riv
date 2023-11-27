#include <scanner/scanner.h>

#include <specter/string.h>
#include <specter/output/ostream.h>

#include <system/exception.h>
#include <common/string.h>
#include <lang.h>



Scanner::Scanner(const std::string& source)
{
	source_ = source;
	line_ = 0;
	begin_ = end_ = 0;
}



std::vector<Token> Scanner::scan()
{
	// clears previous tokens
	tokens_.clear();
	
	// scan all tokens inside source
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


	case '\'':
	case '\"':
		string(ch);
		break;

	default:
		if (sp::is_number(ch))
			number();
		
		else if (sp::is_alpha(ch))
			identifier();

		else
			log_error(Exception("Invalid token.", position()));
	}
}




void Scanner::string(const char encloser)
{
	add_token(TokenType::String, advance_string(encloser));
}


std::string Scanner::advance_string(const char encloser)
{
	std::string str_value = "";
	char current;

	// while not reached at the end of the string
	while (!at_end() && (current = peek()) != encloser)
	{
		// is it a escape character?
		if (current == '\\')
		{
			str_value += string_escape(peek_next()); // adds the escape character
			advance(); // advance the escape character
		}

		else
			str_value += current;

		// next character
		advance();
	}

	// advance the closing '"'
	advance();

	return str_value;
}


char Scanner::string_escape(const char escape)
{
	switch (escape)
	{
	case 'n':
		return '\n';

	case 't':
		return '\t';

	case '\"':
		return '\"';

	case '\'':
		return '\'';

	case '\\':
		return '\\';
	}

	return '\0';
}


void Scanner::number() noexcept
{
	// advance the whole number
	advance_number();

	// number value
	const std::string double_value = current_substring();

	add_token(TokenType::Number, std::stod(double_value));
}


void Scanner::advance_number() noexcept
{
	char current;
	bool has_decimal = false;

	while (sp::is_number((current = peek())) || current == '.')
	{
		if (current == '.' && !has_decimal)
			has_decimal = true;

		// cannot have two '.' in a number
		else if (current == '.' && has_decimal)
			break;

		advance();
	}
}


void Scanner::identifier()
{
	while (sp::is_alphanum(peek()))
		advance();

	const std::string identifier = current_substring();

	// is it a boolean value?
	if (is_boolstr(identifier))
	{
		add_token(TokenType::Bool, string_to_bool(identifier));
		return;
	}

	// is it a keyword?
	if (lang_keywords().contains(identifier))
	{
		add_token(lang_keywords().at(identifier));
		return;
	}

	// general identifier
	add_token(TokenType::Identifier);
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