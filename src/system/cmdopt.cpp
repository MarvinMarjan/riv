#include <system/cmdopt.h>



static bool check_options(std::vector<CmdOption>& valid_options, std::vector<CmdOption>& analyzed_options,
							   const std::string& option_name, const size_t index,
							   const char** const argv, const int argc, const bool full_name) noexcept
{
	for (CmdOption& option : valid_options)
	{
		if ((full_name ? option.name : option.abbrev) != option_name)
			continue;

		if (option.has_argument && index + 1 < (size_t)argc)
			option.argument = argv[index + 1];

		if (option.flag)
			*option.flag = true;

		analyzed_options.push_back(option);

		return true;
	}

	return false;
}



std::vector<CmdOption> get_cmd_options(int argc, const char** argv, std::vector<CmdOption>& valid_options) noexcept
{
	std::vector<CmdOption> analyzed_options;

	for (size_t i = 0; i < (size_t)argc; i++)
	{
		const std::string string_option = argv[i];

		if (string_option.size() < 2)
			continue;

		if (string_option[0] != '-')
			continue;

		const bool condition = string_option[1] == '-';

		const size_t substr_index = condition ? 2 : 1;
		const bool& full_name = condition;

		const std::string option_name = string_option.substr(substr_index);

		check_options(valid_options, analyzed_options, option_name, i, argv, argc, full_name);
	}

	return analyzed_options;
}