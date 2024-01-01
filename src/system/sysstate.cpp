#include <system/sysstate.h>

#include <filesystem>

#include <system/init.h>
#include <common/string.h>
#include <common/filesys.h>



static SystemState s_sys_state;



void set_error_flag() noexcept
{
	s_sys_state.has_error = true;
}



void init_state_using_copy(const SystemState& copy) noexcept
{
	s_sys_state = copy;
}


void init_state_using_srcfile(const std::string& path, const int argc, const char** const argv) noexcept
{
	const std::filesystem::path fs_path = path;
	const std::string           content = read_file(path);

	s_sys_state = SystemState();

	s_sys_state.argv = argv;
	s_sys_state.argc = argc;

	// make canonical paths to make sure it will work

	s_sys_state.app_path = std::filesystem::canonical(argv[0]);

	s_sys_state.source_path = std::filesystem::canonical(fs_path);
	s_sys_state.source_name = fs_path.filename().string();

	s_sys_state.strsource = content;
	s_sys_state.vecsource = split(content, '\n');

	s_sys_state.init_mode = InitMode::SourceFile;

	s_sys_state.has_error = false;
}


void init_state_using_repl(const std::string& content, const int argc, const char** const argv) noexcept
{
	s_sys_state = SystemState();

	s_sys_state.argv = argv;
	s_sys_state.argc = argc;

	s_sys_state.app_path = std::filesystem::canonical(argv[0]);

	s_sys_state.source_name = "REPL";

	s_sys_state.strsource = content;
	s_sys_state.vecsource = split(content, '\n');

	s_sys_state.init_mode = InitMode::REPL;

	s_sys_state.has_error = false;
}


const SystemState& sys_state() noexcept { return s_sys_state; }