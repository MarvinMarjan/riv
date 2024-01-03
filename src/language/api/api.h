#pragma once

extern "C"
{
	enum APITypeEnum
	{
		Null,
		String,
		Number,
		Boolean
	};

	union APITypeSet
	{
		bool        null_v;
		const char* str_v;
		double      num_v;
		bool        bool_v;
	};

	inline APITypeSet new_type_set() {
		return APITypeSet{ true };
	}



	struct APIType
	{
		APITypeSet  value;
		APITypeEnum current_type;
	};

	inline APIType new_type() {
		return APIType{ new_type_set(), Null };
	}



	APIType new_null();
	APIType new_string(const char* init);
	APIType new_number(double init);
	APIType new_boolean(bool init);

	void set_null(APIType* obj);
	void set_string_value(APIType* obj, const char* string);
	void set_number_value(APIType* obj, double number);
	void set_bool_value  (APIType* obj, bool boolean);


	inline bool is_typeof(const APIType obj, const APITypeEnum type)
	{
		return obj.current_type == type;
	}


	inline bool is_null   (const APIType obj) { return is_typeof(obj, Null   ); }
	inline bool is_string (const APIType obj) { return is_typeof(obj, String ); }
	inline bool is_number (const APIType obj) { return is_typeof(obj, Number ); }
	inline bool is_boolean(const APIType obj) { return is_typeof(obj, Boolean); }

	inline const char* as_string(const APIType obj)  { return obj.value.str_v ; }
	inline double      as_number(const APIType obj)  { return obj.value.num_v ; }
	inline bool        as_boolean(const APIType obj) { return obj.value.bool_v; }


	const char* to_string(APIType obj);
	const char* type_to_string(APIType obj);



	struct APICallData
	{
		APIType* args; // array of arguments
		APIType return_value;
	};

	inline APICallData new_call_data() {
		return APICallData{ nullptr, new_type() };
	}



	typedef void (*APISymbolFormat)(APICallData*);
}