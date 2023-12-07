#pragma once

#include <string>
#include <map>



enum class TokenType;


const std::map<std::string, TokenType>& lang_operators()		noexcept;	// return language operators
const std::map<std::string, TokenType>& lang_keywords()			noexcept;	// return language keywords
const std::map<std::string, TokenType>& lang_type_keywords()	noexcept;	// return language type keywords