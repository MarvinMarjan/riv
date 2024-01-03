#pragma once

#include <string>
#include <vector>



struct CmdOption
{
	std::string name        ;
	std::string abbrev      ;
	bool        has_argument;
	bool*       flag        ;

	std::string argument;
};


// gets all valid_options passed by the command line. "valid_options" is a list of valid valid_options to get
std::vector<CmdOption> get_cmd_options(int argc, const char** argv, std::vector<CmdOption>& valid_options) noexcept;