#include <type/type.h>

#include <common/string.h>



// searches the '.' index in a double value string representation
static size_t get_doublestr_decimal_dot_index(const std::string& strdouble) noexcept
{
	size_t decimal_begin = 0;

	for (size_t i = 0; i < strdouble.size(); i++)
		if (strdouble[i] == '.')
		{
			decimal_begin = i;
			break;
		}

	return decimal_begin;
}


// erase irrelevant zeros
static void erase_doublestr_decimal(std::string& strdouble, const size_t decimal_begin, const size_t last_relevant_decimal) noexcept
{
	// is last relevant decimal index the same as the '.' index?
	if (last_relevant_decimal == decimal_begin)
		strdouble.erase(last_relevant_decimal); // erase everything starting from '.'
	else
		strdouble.erase(last_relevant_decimal + 1); // erase everything after the last relevant decimal index
}


// remove irrelevant zeros from a double converted to string.
// if "3.14000" is passed, the return will be "3.14"
static std::string trim_irrelevant_doublestr_zeros(const std::string& strdouble) noexcept
{
	std::string trimmed = strdouble;

	// index of '.'
	size_t decimal_begin = get_doublestr_decimal_dot_index(strdouble);
	
	// last decimal number different from zero
	size_t last_relevant_decimal = decimal_begin;

	erase_doublestr_decimal(trimmed, decimal_begin, last_relevant_decimal);

	return trimmed;
}



Type::Type()
{
	is_null_ = true;
}


std::string type_to_string(const Type& type) noexcept
{
	switch (type.type())
	{
	case TypeIndex::Null: 	return "null";
	
	case TypeIndex::String: return type.as_str();
	case TypeIndex::Number: return trim_irrelevant_doublestr_zeros(std::to_string(type.as_num()));
	case TypeIndex::Bool:	return bool_to_string(type.as_bool());
	}


	return "undefined";
}