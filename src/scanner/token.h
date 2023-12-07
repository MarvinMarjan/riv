#pragma once

#include <type/type.h>



enum class TokenType
{
	// operators

	Plus, Minus, Star, Slash, PlusEqual, MinusEqual, StarEqual, SlashEqual,
	Equal, Bang, Greater, Lesser, GreaterEqual, LesserEqual, EqualEqual, BangEqual,
	LeftParen, RightParen, LeftBrace, RightBrace, LeftCurlyBrace, RightCurlyBrace,
	SemiColon, Dot, Comma, 


	// literal

	Null, String, Number, Bool, Identifier,


	// keywords

	Print, Var, If, Else, While, For, Loop
};



class TokenPosition
{
public:
	size_t line, begin, end;

	TokenPosition() = default;
	TokenPosition(const size_t line, const size_t begin, const size_t end)
		: line(line), begin(begin), end(end), valid_(true) {}


	bool valid() const noexcept { return valid_; }


private:
	bool valid_ = false;
};


struct Token
{
	TokenType type;
	std::string lexeme;
	Type value;
	TokenPosition pos;

	Token() = default;
	Token(const TokenType type, const std::string& lexeme, const Type& value, const TokenPosition& pos)
		: type(type), lexeme(lexeme), value(value), pos(pos) {}

	Token(const TokenType type, const std::string& lexeme, const Type& value, const size_t line, const size_t begin, const size_t end)
		: Token(type, lexeme, value, { line, begin, end }) {}
};