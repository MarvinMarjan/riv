#pragma once

#include <string>
#include <vector>



enum class InitMode;


struct SystemState
{
//	std::string app_folder;

	std::string source_path;                 // path of the ".riv" file
//	std::string absolute_source_path_parent; // absolute parent path of the ".riv" file
	std::string source_name;                 // ".riv" file name

	std::string              strsource; // source as a whole string
	std::vector<std::string> vecsource; // source as a list of lines

	InitMode init_mode;

	bool has_error;

	size_t recursion_limit = 1000;

	std::vector<std::string> import_paths = { "../../lib" };
};


void set_error_flag() noexcept;



void init_state_using_copy   (const SystemState& copy)    noexcept;
void init_state_using_srcfile(const std::string& path)    noexcept;
void init_state_using_repl   (const std::string& content) noexcept;

const SystemState& sys_state() noexcept;