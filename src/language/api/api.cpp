#include <cstdio>
#include <cstring>
#include <cstdlib>

#include <language/api/api.h>



static int get_last_relevant_decimal_index(const char* text)
{
	const int size = (int)strlen(text);

	for (int i = size - 1; i >= 0; i--)
		if (text[i] != '0')
			return i;

	return -1;
}


static int get_decimal_dot_index(const char* text)
{
	const int size = (int)strlen(text);

	for (int i = size - 1; i >= 0; i--)
		if (text[i] == '.')
			return i;

	return -1;
}



void add_array_item(APITypeArray* const array, const APIType item)
{
	const size_t new_size_bytes = sizeof(APIType) * (array->size + 1);

	array->array = (APIType*)realloc(array->array, new_size_bytes);

	array->size++;

	array->array[array->size - 1] = item;
}


void rmv_array_item(APITypeArray* const array, const size_t index)
{
	const size_t new_size_bytes = sizeof(APIType) * (array->size - 1);

	APIType* new_array = (APIType*)malloc(new_size_bytes);

	for (size_t old_array_i = 0, new_array_i = 0; old_array_i < array->size; old_array_i++, new_array_i++)
	{
		if (old_array_i == index)
		{
			new_array_i--;
			continue;
		}

		new_array[new_array_i] = array->array[old_array_i];
	}

	free(array->array);

	array->size--;

	array->array = new_array;
}



APIType new_null()
{
	APIType value = new_type();
	set_null(&value);
	return value;
}


APIType new_string(const char* const init)
{
	APIType value = new_type();
	set_string_value(&value, init);
	return value;
}


APIType new_number(const double init)
{
	APIType value = new_type();
	set_number_value(&value, init);
	return value;
}


APIType new_boolean(const bool init)
{
	APIType value = new_type();
	set_bool_value(&value, init);
	return value;
}


APIType new_array(const APITypeArray init)
{
	APIType value = new_type();
	set_array_value(&value, init);
	return value;
}




void set_null(APIType* const obj)
{
	obj->value.null_v = true;
	obj->current_type = Null;
}


void set_string_value(APIType* const obj, const char* const string)
{
	obj->value.str_v = string;
	obj->current_type = String;
}


void set_number_value(APIType* const obj, const double number)
{
	obj->value.num_v = number;
	obj->current_type = Number;
}


void set_bool_value(APIType* const obj, const bool boolean)
{
	obj->value.bool_v = boolean;
	obj->current_type = Boolean;
}


void set_array_value(APIType* const obj, const APITypeArray array)
{
	obj->value.array_v = array;
	obj->current_type = Array;
}




const char* to_string(const APIType obj)
{
	switch (obj.current_type)
	{
	case Null:
		return "null";

	case String:
		return obj.value.str_v;

	case Number:
	{
		// get the size needed to store
		const int size = snprintf(nullptr, 0, "%f", obj.value.num_v);
		char* strnum = (char*)malloc(size);

		// stores the value on "strnum"
		sprintf(strnum, "%f", obj.value.num_v);

		// gets the last relevant decimal index
		const int index = get_last_relevant_decimal_index(strnum);

		int offset = 1;

		if (index == get_decimal_dot_index(strnum))
			offset = 0;

		// allocates the new string
		char* r_strnum = (char*)malloc(index + 2);

		// copies only the needed part of the string and discards the other part (the irrelevant part)
		strncpy(r_strnum, strnum, index + offset);
		free(strnum);

		r_strnum[index] = '\0';

		return r_strnum;
	}

	case Boolean:
		return obj.value.bool_v ? "true" : "false";
	}

	return "undefined";
}


const char* type_to_string(const APIType obj)
{
	switch (obj.current_type)
	{
	case Null:
		return "Null";

	case String:
		return "String";

	case Number:
		return "Number";

	case Boolean:
		return "Boolean";
	}

	return "undefined";
}