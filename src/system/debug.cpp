#include <system/debug.h>

#include <specter/output/ostream.h>

#include <environment/environment.h>
#include <common/string.h>



static void print_environment_data(const Environment& environment, const std::string& prefix = "")
{
	for (const auto& [name, data] : environment.data())
		sp::println(prefix, name, surround(data.value.type_to_string(), " (", ") "), " = ", data.value.to_string());
}


void print_environment(const Environment& environment)
{
	std::string tab;

	Environment env = environment;
	Environment* current = &env;

	std::vector<Environment*> envs;

	while (current)
	{
		envs.push_back(current);
		current = current->enclosing();
	}

	for (int i = (int)envs.size() - 1; i >= 0; i--)
	{
		print_environment_data(*envs[i], tab);
		tab += "    ";
	}
}