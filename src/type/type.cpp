#include <type/type.h>

#include <common/string.h>



Type::Type()
{
	is_null_ = true;
}


static std::string trim_irrelevant_str_double_zeros(const std::string& strdouble) noexcept
{
	std::string trimmed = strdouble;

	size_t decimal_begin = 0;
	size_t last_relevant_decimal = 0;

	while (decimal_begin < trimmed.size() && trimmed[decimal_begin] != '.')
		decimal_begin++;

	last_relevant_decimal = decimal_begin;

	for (size_t i = decimal_begin; i < trimmed.size(); i++)
		if (trimmed[i] != '0')
			last_relevant_decimal = i;

	if (last_relevant_decimal == decimal_begin)
		trimmed.erase(last_relevant_decimal);

	else
		trimmed.erase(last_relevant_decimal + 1);

	return trimmed;
}


std::string type_to_string(const Type& type) noexcept
{
	switch (type.type_index())
	{
	case TypeIndex::Null: 	return "null";
	
	case TypeIndex::String: return type.as_str();
	case TypeIndex::Number: return trim_irrelevant_str_double_zeros(std::to_string(type.as_num()));
	case TypeIndex::Bool:	return bool_to_string(type.as_bool());
	}


	return "undefined";
}