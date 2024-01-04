#include <cstdlib>
#include <cstring>

#include <language/api/api.h>



extern "C"
{
	void rlib_append(APICallData* data)
	{
		APITypeArray  array = as_array(data->args.array[0]);
		const APIType item  = data->args.array[1];

		add_array_item(&array, item);

		data->return_value = new_array(array);
	}

	int rlib_append_arity = 2;




	void rlib_remove(APICallData* data)
	{
		APITypeArray array = as_array(data->args.array[0]);
		const size_t index = (size_t)as_number(data->args.array[1]);

		rmv_array_item(&array, index);

		data->return_value = new_array(array);
	}

	int rlib_remove_arity = 2;




	void rlib_size(APICallData* data)
	{
		const APIType value = data->args.array[0];

		if (is_array(value))
			data->return_value = new_number((double)as_array(value).size);

		else if (is_string(value))
			data->return_value = new_number((double)strlen(as_string(value)));
	}

	int rlib_size_arity = 1;
}