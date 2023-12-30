#include <system/lib.h>

#include <cstring>
#include <dlfcn.h>



static std::string build_symbol_name_from_base(const std::string& basename, const bool is_arity_symbol = false)
{
	std::string symbol_name = "rlib_";

	symbol_name += basename;

	if (is_arity_symbol)
		symbol_name += "_arity";

	return symbol_name;
}




LibSymbol new_lib_symbol(void* const lib, const std::string& name, void* const symbol) noexcept
{
	return {
		.name = name,
		.symbol = symbol ? (APISymbolFormat)symbol : nullptr,
		.raw_symbol = symbol,
		.lib = lib
	};
}



Library load_library(const std::string& path)
{
	void* lib = dlopen(path.c_str(), RTLD_LAZY);

	return { .path = path, .handler = lib };
}



LibSymbol lib_load_riv_symbol(void* const handler, const std::string& name) noexcept
{
	if (!handler)
		return new_lib_symbol(handler, name, nullptr);

	const std::string symbol_name = build_symbol_name_from_base(name);

	void* const symbol = dlsym(handler, symbol_name.c_str());

	return new_lib_symbol(handler, name, symbol);
}


size_t lib_get_arity_from_symbol(void* const handler, const std::string& name) noexcept
{
	// invalid handler
	if (!handler)
		return SIZE_MAX;

	const std::string symbol_name = build_symbol_name_from_base(name, true);

	void* const symbol = dlsym(handler, symbol_name.c_str());

	return *((size_t*)symbol);
}