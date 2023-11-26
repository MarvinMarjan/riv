#include <lang.h>



// all language operators
static std::map<std::string, TokenType> l_operators =
{
	{"+", TokenType::Plus},
	{"-", TokenType::Minus},
	{"*", TokenType::Star},
	{"/", TokenType::Slash},
	{">", TokenType::Greater},
	{"<", TokenType::Lesser},
	{"=", TokenType::Equal},
	{"(", TokenType::LeftParen},
	{")", TokenType::RightParen},
	{"[", TokenType::LeftBrace},
	{"]", TokenType::RightBrace},
	{"{", TokenType::LeftCurlyBrace},
	{"}", TokenType::RightCurlyBrace},
	{";", TokenType::SemiColon},
	{".", TokenType::Dot},
	{",", TokenType::Comma},
	{"!", TokenType::Bang}
};


// all language keywords
static std::map<std::string, TokenType> l_keywords =
{
	{"var", TokenType::Var}
};



const std::map<std::string, TokenType>& lang_operators()	noexcept { return l_operators; }
const std::map<std::string, TokenType>& lang_keywords()		noexcept { return l_keywords; }