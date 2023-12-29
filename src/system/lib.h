#pragma once

#include <language/api/api.h>



class Type;
struct APICallData;


struct LibSymbol
{
	const char* name;
	APISymbolFormat symbol;
	void* raw_symbol;
};

LibSymbol new_lib_symbol(const char* name, void* symbol) noexcept;



struct Library
{
	const char* path;
	void* handler;
};

Library load_library(const char* path);



LibSymbol lib_load_riv_symbol(void* handler, const char* name) noexcept;