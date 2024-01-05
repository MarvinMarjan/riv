#pragma once



extern "C"
{
	// an enumeration containing every type in Riv.
	enum APITypeEnum
	{
		Null = -1,

		String,
		Number,
		Boolean,
		Array
	};

	struct APIType;


	// type implementation of an array
	struct APITypeArray
	{
		APIType* array; // the array pointer
		size_t size;    // the size of the array, since it's dynamically allocated
	};

	// util for creating an APITypeArray struct
	inline APITypeArray new_type_array(APIType* const init = nullptr, const size_t size = 0) {
		return APITypeArray{ init, size };
	}


	void add_array_item(APITypeArray* array, APIType item ); // adds an item in an array
	void rmv_array_item(APITypeArray* array, size_t  index); // removes an item of an array at a specific index



	// union for representing the dynamic typing system.
	// only one of the values can be used at the same time
	union APITypeSet
	{
		bool         null_v ; // null type
		const char*  str_v  ; // string type
		double       num_v  ; // number type
		bool         bool_v ; // boolean type
		APITypeArray array_v; // array type
	};

	// util for creating an APITypeSet union
	inline APITypeSet new_type_set() {
		return APITypeSet{ true };
	}



	// implementation of a type
	struct APIType
	{
		APITypeSet  value;        // the value
		APITypeEnum current_type; // the value type
	};

	// util for creating an APIType struct
	inline APIType new_type() {
		return APIType{ new_type_set(), Null };
	}



	APIType new_null   ();                  // creates a new Null APIType
	APIType new_string (const char*  init); // creates a new String APIType
	APIType new_number (double       init); // creates a new Number APIType
	APIType new_boolean(bool         init); // creates a new Boolean APIType
	APIType new_array  (APITypeArray init); // creates a nes Array APIType

	void set_null        (APIType* obj);                       // sets to an APIType a Null type value
	void set_string_value(APIType* obj, const char*  string ); // sets to an APIType a String type value
	void set_number_value(APIType* obj, double       number ); // sets to an APIType a Number type value
	void set_bool_value  (APIType* obj, bool         boolean); // sets to an APIType a Boolean type value
	void set_array_value (APIType* obj, APITypeArray array  ); // sets to an APIType a Array type value


	// returns "true" if "obj" has the same type as "type"
	inline bool is_typeof(const APIType obj, const APITypeEnum type) {
		return obj.current_type == type;
	}


	inline bool is_null   (const APIType obj) { return is_typeof(obj, Null   ); } // checks if an APIType is of Null type
	inline bool is_string (const APIType obj) { return is_typeof(obj, String ); } // checks if an APIType is of String type
	inline bool is_number (const APIType obj) { return is_typeof(obj, Number ); } // checks if an APIType is of Number type
	inline bool is_boolean(const APIType obj) { return is_typeof(obj, Boolean); } // checks if an APIType is of Boolean type
	inline bool is_array  (const APIType obj) { return is_typeof(obj, Array  ); } // checks if an APIType is of Array type

	inline const char*  as_string (const APIType obj) { return obj.value.str_v  ; } // gets the String value of an APIType
	inline double       as_number (const APIType obj) { return obj.value.num_v  ; } // gets the Number value of an APIType
	inline bool         as_boolean(const APIType obj) { return obj.value.bool_v ; } // gets the Boolean value of an APIType
	inline APITypeArray as_array  (const APIType obj) { return obj.value.array_v; } // gets the Array value of an APIType


	const char* to_string(APIType obj);      // converts an APIType into a string representations
	const char* type_to_string(APIType obj); // returns a string with the type of APIType


	// a struct containing useful input/output data passed as argument to the
	// library functions.
	struct APICallData
	{
		APITypeArray args   ; // [input ] the arguments the function has received
		APIType return_value; // [output] the return value of the library function
	};

	// util for creating an APICallData struct
	inline APICallData new_call_data() {
		return APICallData{ new_type_array(), new_type() };
	}



	// a type that represents the signature a library function.
	// the same as "void rlib_function(APICallData*) {}"
	typedef void (*APISymbolFormat)(APICallData*);
}