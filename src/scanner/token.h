#pragma once

#include <string>



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
	Token(const TokenType type, const std::string& lexeme, const size_t line, const size_t begin, const size_t end)
	 : type(type), lexeme(lexeme), line(line), begin(begin), end(end) {}

	TokenType type;
	std::string lexeme;
	size_t line, begin, end;
};