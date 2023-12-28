extern "C"
{
	enum TypeEnum
	{
		Null,
		String,
		Number,
		Boolean
	};

	union TypeSet
	{
		bool        null_v;
		const char* str_v;
		double      num_v;
		bool        bool_v;
	};

	inline TypeSet new_type_set() {
		return TypeSet{ true };
	}



	struct APIType
	{
		TypeSet  value;
		TypeEnum current_type;
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


	inline bool is_typeof(const APIType obj, const TypeEnum aPIType)
	{
		return obj.current_type == aPIType;
	}


	inline bool is_null   (const APIType obj) { return is_typeof(obj, Null   ); }
	inline bool is_string (const APIType obj) { return is_typeof(obj, String ); }
	inline bool is_number (const APIType obj) { return is_typeof(obj, Number ); }
	inline bool is_boolean(const APIType obj) { return is_typeof(obj, Boolean); }

	inline const char* as_string(const APIType obj)  { return obj.value.str_v ; }
	inline double      as_number(const APIType obj)  { return obj.value.num_v ; }
	inline bool        as_boolean(const APIType obj) { return obj.value.bool_v; }


	const char* to_string(APIType obj);



	struct CallData
	{
		APIType* args;
		APIType return_value;
	};

	inline CallData new_call_data() { return CallData{ nullptr, new_type() }; }
}