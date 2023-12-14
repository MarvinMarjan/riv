#include <system/sysstate.h>

#include <filesystem>

#include <system/init.h>
#include <common/string.h>
#include <common/filesys.h>

#include <specter/output/ostream.h>



static SystemState s_sys_state;



void set_error_flag() noexcept {
	s_sys_state.has_error = true;
}



void init_state_using_copy(const SystemState& copy) noexcept {
	s_sys_state = copy;
}


void init_state_using_srcfile(const std::string& path) noexcept
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


void init_state_using_repl(const std::string& content) noexcept
{
	s_sys_state = SystemState();

	s_sys_state.source_name = "REPL";

	s_sys_state.strsource = content;
	s_sys_state.vecsource = split(content, '\n');

	s_sys_state.init_mode = InitMode::REPL;

	s_sys_state.has_error = false;
}


const SystemState& sys_state() noexcept { return s_sys_state; }