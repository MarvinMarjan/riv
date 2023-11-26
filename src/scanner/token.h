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

	String, Number, Bool, Identifier,


	// keywords

	Var
};



struct Token
{
	Token(const TokenType type, const std::string& lexeme, const Type& value, const size_t line, const size_t begin, const size_t end)
	 : type(type), lexeme(lexeme), value(value), line(line), begin(begin), end(end) {}

	TokenType type;
	std::string lexeme;
	Type value;
	size_t line, begin, end;
};