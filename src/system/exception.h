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



std::string exception_to_string(const Exception& exception) noexcept;


void log_error(const Exception& exception) noexcept;