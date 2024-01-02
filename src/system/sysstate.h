#pragma once

#include <string>
#include <vector>
#include <filesystem>



enum class InitMode;


// stores a lot of state and useful data
struct SystemState
{
	const char** argv;
	int          argc;

	std::filesystem::path app_path; // path to the executable

	std::filesystem::path source_path; // path of the ".riv" file
	std::string           source_name; // ".riv" file name

	std::string              source_string; // source as a whole string
	std::vector<std::string> source_lines;  // source as a list of lines

	std::vector<std::string> import_paths = { "../../lib" };

	InitMode init_mode;
	bool     has_error;

	static constexpr size_t recursion_limit = 1000;
};


void set_error_flag() noexcept;



void init_state_using_copy   (const SystemState& copy)                                 noexcept;
void init_state_using_srcfile(const std::string& path   , int argc, const char** argv) noexcept;
void init_state_using_repl   (const std::string& content, int argc, const char** argv) noexcept;

const SystemState& sys_state() noexcept;