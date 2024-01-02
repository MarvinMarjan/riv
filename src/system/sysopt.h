#pragma once

#include <vector>



struct CmdOptionList;


struct SystemOptions
{
};


const SystemOptions& sys_options        () noexcept;
const CmdOptionList& sys_cmd_option_list() noexcept;