#pragma once

#include <cstdint>
#include <cstddef>

#include <string>

#include <language/api/api.h>



class Type;
struct APICallData;


struct LibSymbol
{
	std::string name;
	APISymbolFormat symbol;
	void* raw_symbol;
	void* lib;
};

LibSymbol new_lib_symbol(void* lib, const std::string& name, void* symbol) noexcept;



struct Library
{
	std::string path;
	void* handler;
};

Library load_library(const std::string& path);



LibSymbol lib_load_riv_symbol      (void* handler, const std::string& name) noexcept;
size_t    lib_get_arity_from_symbol(void* handler, const std::string& name) noexcept;