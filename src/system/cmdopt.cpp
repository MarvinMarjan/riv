#include <system/cmdopt.h>



static void check_options(std::vector<CmdOption>& options, const std::string& option_name, const size_t index,
						  const char** const argv, const int argc, const bool full_name) noexcept
{
	for (CmdOption& option : options)
	{
		if (((full_name) ? option.name : std::string(1, option.ch_name)) != option_name)
			continue;

		if (option.has_argument && index + 1 < argc)
			option.argument = argv[index + 1];

		if (option.flag)
			*option.flag = true;
	}
}



void process_options(const int argc, const char** const argv, std::vector<CmdOption>& options) noexcept
{
	for (size_t i = 0; i < argc; i++)
	{
		const std::string string_option = argv[i];

		if (string_option.size() < 2)
			continue;

		if (string_option[0] != '-')
			continue;

		const bool condition = string_option[1] == '-';

		const size_t substr_index = condition ? 2 : 1;
		const bool&   full_name    = condition;

		const std::string option_name = string_option.substr(substr_index);

		check_options(options, option_name, i, argv, argc, full_name);
	}
}



CmdOption& CmdOptionList::get_by_name(const std::string& name) noexcept
{
	for (CmdOption& option : *this)
		if (option.name == name)
			return option;

	return back();
}


const CmdOption& CmdOptionList::get_by_name(const std::string& name) const noexcept
{
	for (const CmdOption& option : *this)
		if (option.name == name)
			return option;

	return back();
}