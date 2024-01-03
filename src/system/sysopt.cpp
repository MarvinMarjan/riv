#include <system/sysopt.h>

#include <system/cmdopt.h>



static SystemOptions s_sys_options;



std::vector<CmdOption> g_sys_cmd_option_list = {
	{"import", "i", true, nullptr},
	{"recursion-limit", "rl", true, nullptr}
};



void process_options(const std::vector<CmdOption>& options)
{
	for (const CmdOption& option : options)
	{
		if (option.name == "import")
			s_sys_options.import_paths.push_back(option.argument);

		if (option.name == "recursion-limit")
		{
			const int limit = std::stoi(option.argument);

			if (limit >= 0)
				s_sys_options.recursion_limit = limit;
		}
	}
}



const SystemOptions         & sys_options        () noexcept { return s_sys_options        ; }
const std::vector<CmdOption>& sys_cmd_option_list() noexcept { return g_sys_cmd_option_list; }