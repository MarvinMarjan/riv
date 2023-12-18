#pragma once

#include <string>
#include <map>
#include <vector>



enum class TokenType;


const std::map<std::string, TokenType>&	lang_operators()		noexcept;	// return language operators
const std::map<std::string, TokenType>&	lang_keywords()			noexcept;	// return language keywords
const std::vector<TokenType>&			lang_modifiers()		noexcept;	// return language modifiers
const std::map<std::string, TokenType>&	lang_type_keywords()	noexcept;	// return language type keywords