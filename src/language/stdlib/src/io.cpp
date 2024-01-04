#include <cstdio>
#include <cstring>

#include <language/api/api.h>



extern "C"
{
	void rlib_println(APICallData* data)
	{
		const APIType text = data->args.array[0];

		printf("%s\n", to_string(text));
	}

	size_t rlib_println_arity = 1;




	void rlib_print(APICallData* data)
	{
		const APIType text = data->args.array[0];

		printf("%s", to_string(text));
	}

	size_t rlib_print_arity = 1;




	void rlib_input(APICallData* data)
	{
		char* input;
		size_t size = 0;

		getline(&input, &size, stdin);

		// remove the '\n' character read by "getline"
		input[strlen(input) - 1] = '\0';

		data->return_value = new_string(input);
	}

	size_t rlib_input_arity = 0;
}