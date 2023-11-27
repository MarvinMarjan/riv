#pragma once

#include <string>
#include <variant>



enum class TypeIndex
{
	Null = -1,

	String,
	Number,
	Bool
};



using VariantType = std::variant<std::string, double, bool>;


class Type;


// returns a representation of a Type
std::string type_to_string(const Type& type) noexcept;


// language types
class Type : public VariantType
{
public:
	using VariantType::variant;
	
	Type();


	// returns an enum that represents the current active type
	TypeIndex type() const noexcept { return is_null() ? TypeIndex::Null : (TypeIndex)index(); }


	std::string to_string() const noexcept { return type_to_string(*this); }


	bool is_null() const noexcept { return is_null_; }

	std::string	as_str()	const noexcept { return std::get<std::string>(*this); }
	double		as_num()	const noexcept { return std::get<double>(*this); }
	bool		as_bool()	const noexcept { return std::get<bool>(*this); }

private:
	bool is_null_;
};