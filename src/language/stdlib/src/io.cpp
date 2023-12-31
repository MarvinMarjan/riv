#include <cstdio>

#include <language/api/api.h>



extern "C"
{
	void rlib_println(APICallData* data)
	{
		printf("%s\n", to_string(data->args[0]));
	}

	size_t rlib_println_arity = 1;
}