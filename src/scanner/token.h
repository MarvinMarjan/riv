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



struct Token;