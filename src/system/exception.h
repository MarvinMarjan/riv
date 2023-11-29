#pragma once

#include <specter/output/ostream.h>
#include <scanner/token.h>



struct Exception
{
	const std::string msg;
	const TokenPosition pos;

	Exception(const std::string& msg, const TokenPosition& pos)
		: msg(msg), pos(pos) {}
};


// creates a exception message based on Exception object
std::string exception_to_string(const Exception& exception) noexcept;


// logs an error to the console
void log_error(const Exception& exception) noexcept;