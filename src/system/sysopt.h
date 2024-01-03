#pragma once

#include <vector>
#include <string>



struct CmdOption;


struct SystemOptions
{
	std::vector<std::string> import_paths;
	size_t                   recursion_limit = 1000;
};


// process all options passed by the command line
void process_options(const std::vector<CmdOption>& options);


const SystemOptions         & sys_options        () noexcept;
const std::vector<CmdOption>& sys_cmd_option_list() noexcept;