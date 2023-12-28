#include <language/api/api.h>

#include <cstdio>



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
	char* str;

	switch (obj.current_type)
	{
	case Null:
		return "null";

	case String:
		return obj.value.str_v;

	case Number:
		sprintf(str, "%f", obj.value.num_v);
		return str;

	case Boolean:
		return obj.value.bool_v ? "true" : "false";
	}

	return "undefined";
}