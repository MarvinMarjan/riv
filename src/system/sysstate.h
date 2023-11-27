#pragma once

#include <vector>

#include <system/init.h>



struct SystemState
{
	std::string source_path;
	std::string source_name;

	std::string strsource;
	std::vector<std::string> vecsource;

	InitMode init_mode;

	bool has_error;
};


void init_state_srcfile(const std::string& path) noexcept;
void init_state_repl(const std::string& content) noexcept;

const SystemState& sys_state() noexcept;