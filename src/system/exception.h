#pragma once

#include <scanner/token.h>



struct Exception
{
	Exception(const std::string& msg, const TokenPosition& pos = TokenPosition(), unsigned int code = 0);
	
	const std::string msg;
	const TokenPosition pos;

	const unsigned int code;
};


// creates an exception message based on Exception object
std::string exception_to_string(const Exception& exception) noexcept;


// logs an error to the console
void log_error(const Exception& exception) noexcept;