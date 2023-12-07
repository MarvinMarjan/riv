#pragma once

#include <scanner/token.h>



struct Exception
{
	const std::string msg;
	const TokenPosition pos;

	const unsigned int code;

	Exception(const std::string& msg, const TokenPosition& pos = TokenPosition(), const unsigned int code = 0)
		: msg(msg), pos(pos), code(code) {}
};


// creates a exception message based on Exception object
std::string exception_to_string(const Exception& exception) noexcept;


// logs an error to the console
void log_error(const Exception& exception) noexcept;