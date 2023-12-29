#include <type/type.h>

#include <common/string.h>
#include <type/function.h>
#include <type/package.h>



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


static size_t get_last_relevant_decimal_index(const std::string& strdouble, const size_t decimal_begin) noexcept
{
	size_t last_relevant_decimal = decimal_begin;

	// search for the last relevant decimal index
	for (size_t i = last_relevant_decimal; i < strdouble.size(); i++)
		if (strdouble[i] != '0')
			last_relevant_decimal = i;

	return last_relevant_decimal;
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
	size_t last_relevant_decimal = get_last_relevant_decimal_index(strdouble, decimal_begin);

	erase_doublestr_decimal(trimmed, decimal_begin, last_relevant_decimal);

	return trimmed;
}


std::string type_index_to_string(const TypeIndex type) noexcept
{
	switch (type)
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


std::string type_obj_to_string(const Type& type) noexcept
{
	switch (type.type())
	{
	case TypeIndex::Null:     return "null";

	case TypeIndex::String:   return type.as_str();
	case TypeIndex::Number:   return trim_irrelevant_doublestr_zeros(std::to_string(type.as_num()));
	case TypeIndex::Bool:     return bool_to_string(type.as_bool());
	case TypeIndex::Array:    return "Array" + surround(std::to_string(type.as_array().size()), "(", ")");
	case TypeIndex::Symbol:
	case TypeIndex::Function: return "Function " + qt(type.as_func()->declaration.name.lexeme) + "";
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
		return (bool) value.as_num();

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