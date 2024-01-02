#pragma once

#include <string>
#include <vector>



struct CmdOption
{
	std::string name        ;
	char        ch_name     ;
	bool        has_argument;
	bool*       flag        ;

	std::string argument;
};


void process_options(int argc, const char** argv, std::vector<CmdOption>& options) noexcept;



class CmdOptionList : public std::vector<CmdOption>
{
public:
	using std::vector<CmdOption>::vector;

	      CmdOption& get_by_name(const std::string& name)       noexcept;
	const CmdOption& get_by_name(const std::string& name) const noexcept;
};