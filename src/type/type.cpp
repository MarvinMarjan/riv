#include <type/type.h>

#include <common/string.h>
#include <type/function.h>
#include <type/package.h>
#include "specter/output/ostream.h"



// searches the '.' index in a double value string representation
static size_t get_double_string_decimal_dot_index(const std::string& double_string) noexcept
{
	return double_string.find_first_of('.');
}


// searches for the last relevant decimal index (the last number that isn't a zero)
static size_t get_last_relevant_decimal_index(const std::string& double_string) noexcept
{
	return double_string.find_last_not_of('0');
}


// erase irrelevant zeros
static void erase_double_string_decimal(std::string& double_string, const size_t last_relevant_decimal_index, const size_t dot_index) noexcept
{
	const size_t offset = last_relevant_decimal_index == dot_index ? 0 : 1;

	// erase everything after the last relevant decimal index
	double_string.erase(last_relevant_decimal_index + offset);
}


// remove irrelevant zeros from a double converted to string.
// if "3.14000" is passed, the return will be "3.14"
static std::string remove_double_string_irrelevant_zeros(const std::string& double_string) noexcept
{
	std::string trimmed = double_string;

	// index of '.'
	const size_t dot_index = get_double_string_decimal_dot_index(double_string);

	// last decimal number different from zero
	const size_t last_relevant_decimal_index = get_last_relevant_decimal_index(double_string);

	erase_double_string_decimal(trimmed, last_relevant_decimal_index, dot_index);

	return trimmed;
}


std::string type_index_to_string(const TypeIndex value) noexcept
{
	switch (value)
	{
	case TypeIndex::Null:     return "Null";
	case TypeIndex::String:   return "String";
	case TypeIndex::Number:   return "Number";
	case TypeIndex::Bool:     return "Bool";
	case TypeIndex::Array:    return "Array";
	case TypeIndex::Symbol:
	case TypeIndex::Function: return "Function";

	default: return "undefined";
	}
}


std::string type_obj_to_string(const Type& value) noexcept
{
	switch (value.type())
	{
	case TypeIndex::Null:     return "null";

	case TypeIndex::String:   return value.as_str();
	case TypeIndex::Number:   return remove_double_string_irrelevant_zeros(std::to_string(value.as_num()));
	case TypeIndex::Bool:     return bool_to_string(value.as_bool());
	case TypeIndex::Array:    return "Array" + surround(std::to_string(value.as_array().size()), "(", ")");
	case TypeIndex::Symbol:
	case TypeIndex::Function: return "Function " + qt(value.as_func()->declaration.name.lexeme) + "";
	}


	return "undefined";
}


APIType type_obj_to_api_type(const Type& value) noexcept
{
	switch (value.type())
	{
	case TypeIndex::Null:   return new_null   ();
	case TypeIndex::String: return new_string (value.as_str().c_str());
	case TypeIndex::Number: return new_number (value.as_num());
	case TypeIndex::Bool:   return new_boolean(value.as_bool());
	}

	return new_string("undefined");
}


APIType* type_objs_to_api_type_array(const std::vector<Type>& values)
{
	APIType* array = new APIType[values.size()];

	for (size_t i = 0; i < values.size(); i++)
		array[i] = type_obj_to_api_type(values[i]);

	return array;
}



Type api_type_to_type_obj(const APIType& value) noexcept
{
	switch (value.current_type)
	{
	case APITypeEnum::Null:    return {};
	case APITypeEnum::String:  return as_string(value);
	case APITypeEnum::Number:  return as_number(value);
	case APITypeEnum::Boolean: return as_boolean(value);
	}

	return "undefined";
}



Type::Type()
{
	is_null_ = true;
}


const RivPackage* Type::as_package() const noexcept
{
	return dynamic_cast<const RivPackage*>(as_non_assignable());
}



RivPackage* Type::as_package() noexcept
{
	return dynamic_cast<RivPackage*>(as_non_assignable());
}




bool Type::equals(const Type& left, const Type& right) noexcept
{
	if (left.is_null() && right.is_null())
		return true;

	if (left.is_null())
		return false;

	return left == right;
}


bool Type::truthy(const Type& value) noexcept
{
	if (value.is_null())
		return false;

	if (value.is_num())
		return (bool)value.as_num();

	if (value.is_bool())
		return value.as_bool();

	return true;
}



Type::Mutability Type::get_mutability_from_modifier(const TokenType specifier, const Mutability default_value) noexcept
{
	switch (specifier)
	{
	case TokenType::Mut:  return Mutable;
	case TokenType::Imut: return Immutable;

	// returns the default value if it's not any valid mutability modifier
	default: return default_value;
	}
}


bool Type::is_valid_mutability_modifier(TokenType specifier) noexcept
{
	switch (specifier)
	{
	case TokenType::Mut:
	case TokenType::Imut: return true;

	default: return false;
	}
}