#pragma once

#include <map>

#include <scanner/token.h>



const std::map<std::string, TokenType>& lang_operators()		noexcept;	// return language operators
const std::map<std::string, TokenType>& lang_keywords()			noexcept;	// return language keywords
const std::map<std::string, TokenType>& lang_type_keywords()	noexcept;	// return language keywords