#include <system/sysopt.h>

#include <system/cmdopt.h>



static SystemOptions s_sys_options;



CmdOptionList g_sys_cmd_option_list = {
	{"import", 'i', true, nullptr}
};



const SystemOptions& sys_options        () noexcept { return s_sys_options        ; }
const CmdOptionList& sys_cmd_option_list() noexcept { return g_sys_cmd_option_list; }