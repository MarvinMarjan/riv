#include <cstddef>
#include <cstdio>

#include <language/api/api.h>



extern "C"
{
	void rlib_typeof(APICallData* data)
	{
		const APIType value = data->args[0];

		data->return_value = new_string(type_to_string(value));
	}

	size_t rlib_typeof_arity = 1;




	void rlib_to_string(APICallData* data)
	{
		const APIType value = data->args[0];

		data->return_value = new_string(to_string(value));
	}

	size_t rlib_to_string_arity = 1;
}