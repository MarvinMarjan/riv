#pragma once

extern "C"
{
	enum APITypeEnum
	{
		Null = -1,

		String,
		Number,
		Boolean,
		Array
	};

	struct APIType;


	struct APITypeArray
	{
		APIType* array;
		size_t size;
	};

	inline APITypeArray new_type_array(APIType* const init = nullptr, const size_t size = 0) {
		return APITypeArray{ init, size };
	}


	void add_array_item(APITypeArray* array, APIType item );
	void rmv_array_item(APITypeArray* array, size_t  index);



	union APITypeSet
	{
		bool         null_v ;
		const char*  str_v  ;
		double       num_v  ;
		bool         bool_v ;
		APITypeArray array_v;
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



	APIType new_null   ();
	APIType new_string (const char*  init);
	APIType new_number (double       init);
	APIType new_boolean(bool         init);
	APIType new_array  (APITypeArray init);

	void set_null        (APIType* obj);
	void set_string_value(APIType* obj, const char*  string );
	void set_number_value(APIType* obj, double       number );
	void set_bool_value  (APIType* obj, bool         boolean);
	void set_array_value (APIType* obj, APITypeArray array  );


	inline bool is_typeof(const APIType obj, const APITypeEnum type) {
		return obj.current_type == type;
	}


	inline bool is_null   (const APIType obj) { return is_typeof(obj, Null   ); }
	inline bool is_string (const APIType obj) { return is_typeof(obj, String ); }
	inline bool is_number (const APIType obj) { return is_typeof(obj, Number ); }
	inline bool is_boolean(const APIType obj) { return is_typeof(obj, Boolean); }
	inline bool is_array  (const APIType obj) { return is_typeof(obj, Array  ); }

	inline const char*  as_string (const APIType obj) { return obj.value.str_v  ; }
	inline double       as_number (const APIType obj) { return obj.value.num_v  ; }
	inline bool         as_boolean(const APIType obj) { return obj.value.bool_v ; }
	inline APITypeArray as_array  (const APIType obj) { return obj.value.array_v; }


	const char* to_string(APIType obj);
	const char* type_to_string(APIType obj);



	struct APICallData
	{
		APITypeArray args; // array of arguments
		APIType return_value;
	};

	inline APICallData new_call_data() {
		return APICallData{ new_type_array(), new_type() };
	}



	typedef void (*APISymbolFormat)(APICallData*);
}