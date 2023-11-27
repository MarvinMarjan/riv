#include <system/sysstate.h>

#include <filesystem>

#include <common/string.h>
#include <common/filesys.h>



static SystemState s_sys_state;


void init_state_srcfile(const std::string& path) noexcept
{
	std::filesystem::path fpath = path;
	std::string content = read_file(path);

	s_sys_state = SystemState();

	s_sys_state.source_path = fpath.string();
	s_sys_state.source_name = fpath.filename().string();

	s_sys_state.strsource = content;
	s_sys_state.vecsource = split(content, '\n');

	s_sys_state.init_mode = InitMode::SourceFile;

	s_sys_state.has_error = false;
}


void init_state_repl(const std::string& content) noexcept
{
	s_sys_state = SystemState();

	s_sys_state.source_name = "REPL";

	s_sys_state.strsource = content;
	s_sys_state.vecsource = split(content, '\n');

	s_sys_state.init_mode = InitMode::REPL;

	s_sys_state.has_error = false;
}


const SystemState& sys_state() noexcept { return s_sys_state; }