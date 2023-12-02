#pragma once

#include <type/type.h>



enum class TokenType
{
	// operators

	Plus, Minus, Star, Slash,
	Equal, Bang, Greater, Lesser, GreaterEqual, LesserEqual, EqualEqual, BangEqual,
	LeftParen, RightParen, LeftBrace, RightBrace, LeftCurlyBrace, RightCurlyBrace,
	SemiColon, Dot, Comma, 


	// literal

	Null, String, Number, Bool, Identifier,


	// keywords

	Var
};



struct TokenPosition
{
	size_t line, begin, end;

	TokenPosition() = default;
	TokenPosition(const size_t line, const size_t begin, const size_t end)
		: line(line), begin(begin), end(end) {}
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