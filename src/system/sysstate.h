#pragma once

#include <string>
#include <vector>



enum class InitMode;


struct SystemState
{
	std::string source_path;
	std::string source_name;

	std::string strsource;
	std::vector<std::string> vecsource;

	InitMode init_mode;

	bool has_error;
};


void set_error_flag() noexcept;



void init_state_using_srcfile(const std::string& path) noexcept;
void init_state_using_repl(const std::string& content) noexcept;

const SystemState& sys_state() noexcept;