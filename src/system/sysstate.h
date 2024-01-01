#pragma once

#include <string>
#include <vector>
#include <filesystem>



enum class InitMode;


struct SystemState
{
	const char** argv;
	int          argc;

	std::filesystem::path app_path; // path to the executable

	std::filesystem::path source_path; // path of the ".riv" file
	std::string           source_name; // ".riv" file name

	std::string              strsource; // source as a whole string
	std::vector<std::string> vecsource; // source as a list of lines

	InitMode init_mode;

	bool has_error;

	size_t recursion_limit = 1000;

	std::vector<std::string> import_paths = { "../../lib" };
};


void set_error_flag() noexcept;



void init_state_using_copy   (const SystemState& copy)    noexcept;
void init_state_using_srcfile(const std::string& path   , int argc, const char** argv) noexcept;
void init_state_using_repl   (const std::string& content, int argc, const char** argv) noexcept;

const SystemState& sys_state() noexcept;