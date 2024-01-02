#pragma once

#include <sstream>

#include <type/type.h>



// index of all tokens in riv
enum class TokenType
{
	// operators

	Plus, Minus, Star, Slash, PlusEqual, MinusEqual, StarEqual, SlashEqual,
	Equal, Bang, Greater, Lesser, GreaterEqual, LesserEqual, EqualEqual, BangEqual,
	LeftParen, RightParen, LeftBrace, RightBrace, LeftCurlyBrace, RightCurlyBrace,
	SemiColon, Dot, Comma, Colon, ColonColon, QuestionMark,


	// literal

	Null, String, Number, Bool, Identifier,


	// keywords

	Print, Var, Mut, Imut, If, Else, While, For, Loop, Break, Continue,
	Function, Return, Import, Package
};



class TokenPosition
{
public:
	TokenPosition() = default;
	TokenPosition(size_t line, size_t begin, size_t end);


	bool valid() const noexcept { return valid_; }


	size_t line  = 0;
	size_t begin = 0;
	size_t end   = 0;

private:

	// is this position valid?
	bool valid_ = false;
};


std::string token_position_to_string(const TokenPosition& pos) noexcept;



struct Token
{
	Token() = default;
	Token(TokenType type, const std::string& lexeme, const Type& value, const TokenPosition& pos);
	Token(TokenType type, const std::string& lexeme, const Type& value, size_t line, size_t begin, size_t end);

	TokenType     type;
	std::string   lexeme;
	Type          value;
	TokenPosition pos;
};