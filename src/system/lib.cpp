#include <system/lib.h>

#include <cstring>
#include <dlfcn.h>



LibSymbol new_lib_symbol(const char* name, void* const symbol) noexcept
{
	return {
		.name = name,
		.symbol = symbol ? (APISymbolFormat)symbol : nullptr,
		.raw_symbol = symbol
	};
}



Library load_library(const char* const path)
{
	void* lib = dlopen(path, RTLD_LAZY);

	return { .path = path, .handler = lib };
}



LibSymbol lib_load_riv_symbol(void* const handler, const char* name) noexcept
{
	if (!handler)
		return new_lib_symbol(name, nullptr);

	char* const prefixed_symbol = "rlib_";
	strcat(prefixed_symbol, name);

	void* const symbol = dlsym(handler, prefixed_symbol);

	return new_lib_symbol(name, symbol);
}