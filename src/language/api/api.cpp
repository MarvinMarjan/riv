#include <cstdio>
#include <cstring>
#include <cstdint>
#include <cstdlib>

#include <language/api/api.h>



int get_last_relevant_decimal_index(const char* text)
{
	const int size = (int)strlen(text);

	for (int i = size - 1; i >= 0; i--)
		if (text[i] != '0' && text[i] != '.')
			return i;

	return -1;
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




const char* to_string(const APIType obj)
{
	switch (obj.current_type)
	{
	case Null:
		return "null";

	case String:
		return obj.value.str_v;

	case Number: {
		// get the size needed to store
		const int size = snprintf(nullptr, 0, "%f", obj.value.num_v);
		char* strnum = new char[size];

		// stores the value on "strnum"
		sprintf(strnum, "%f", obj.value.num_v);

		// gets the last relevant decimal index
		const int index = get_last_relevant_decimal_index(strnum);

		// allocates the new string
		char* r_strnum = (char*)malloc(index + 2);

		// copies only the needed part of the string and discards the other part (the irrelevant part)
		strncpy(r_strnum, strnum, index + 1);
		free(strnum);

		r_strnum[index + 1] = '\0';

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