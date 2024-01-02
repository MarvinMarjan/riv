#include <scanner/token.h>


TokenPosition::TokenPosition(const size_t line, const size_t begin, const size_t end)
	: line(line), begin(begin), end(end), valid_(true) {}


std::string token_position_to_string(const TokenPosition& pos) noexcept
{
	std::stringstream stream;

	stream << "line " << pos.line + 1 << ", ";
	stream << "col " << pos.begin << ":" << pos.end;

	return stream.str();
}



Token::Token(const TokenType type, const std::string& lexeme, const Type& value, const TokenPosition& pos)
	: type(type), lexeme(lexeme), value(value), pos(pos) {}

Token::Token(const TokenType type, const std::string& lexeme, const Type& value, const size_t line, const size_t begin, const size_t end)
	: Token(type, lexeme, value, { line, begin, end }) {}