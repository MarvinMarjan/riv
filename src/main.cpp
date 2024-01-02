#include <system/init.h>
#include <system/exception.h>
#include <system/cmdopt.h>
#include <system/sysopt.h>



extern CmdOptionList g_sys_cmd_option_list;


int main(const int argc, const char** argv)
{
	// mode in which system will be initialized
	InitMode mode = get_init_mode(argc, argv);

	process_options(argc, argv, g_sys_cmd_option_list);

	try
	{
		// interactive mode
		if (mode == InitMode::REPL)
			repl_init(argc, argv);

		// source file mode
		else if (mode == InitMode::SourceFile)
			src_file_init(argc, argv);
	}

	catch (const Exception& e)
	{
		log_error(e);
	}
}