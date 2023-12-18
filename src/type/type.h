#pragma once

#include <variant>

#include <type/non_assignable.h>



enum class TypeIndex
{
	Null = -1,

	String,
	Number,
	Bool,
	Function,
	NonAssignable
};


class RivFunction;
class RivPackage;

enum class TokenType;


std::string type_index_to_string(TypeIndex type) noexcept;


using VariantType = std::variant<std::string, double, bool, RivFunction*, NonAssignable*>;


class Type;


// returns a representation of a Type
std::string type_obj_to_string(const Type& type) noexcept;


// language types
class Type : public VariantType
{
public:
	enum Mutability
	{
		Mutable,
		Immutable
	};

	using VariantType::variant;
	
	Type();

	// returns an enum that represents the current active type
	TypeIndex type() const noexcept { return ((is_null()) ? TypeIndex::Null : (TypeIndex)index()); }


	std::string to_string()			const noexcept { return type_obj_to_string(*this); }
	std::string type_to_string()	const noexcept { return type_index_to_string(type()); }


	void set_mutability(const Mutability mut) noexcept { mut_ = mut; }

	Mutability mutability() const noexcept { return mut_; }


	bool is_typeof(const TypeIndex type) const noexcept { return this->type() == type; }

	bool is_null()				const noexcept { return is_null_; }
	bool is_str()				const noexcept { return is_typeof(TypeIndex::String); }
	bool is_num()				const noexcept { return is_typeof(TypeIndex::Number); }
	bool is_bool()				const noexcept { return is_typeof(TypeIndex::Bool); }
	bool is_func()				const noexcept { return is_typeof(TypeIndex::Function); }
	bool is_non_assignable()	const noexcept { return is_typeof(TypeIndex::NonAssignable); }

	std::string		as_str()			const noexcept { return std::get<std::string>(*this); }
	double			as_num()			const noexcept { return std::get<double>(*this); }
	bool			as_bool()			const noexcept { return std::get<bool>(*this); }
	RivFunction* 	as_func()			const noexcept { return std::get<RivFunction*>(*this); }
	NonAssignable* 	as_non_assignable()	const noexcept { return std::get<NonAssignable*>(*this); }


	// non-assignable types

	bool is_package() const noexcept { return as_package(); }

	RivPackage* as_package() const noexcept;


	static Mutability	get_mutability_from_modifier(TokenType specifier) noexcept;
	static bool			is_valid_mutability_modifier(TokenType specifier) noexcept;


private:
	bool is_null_ = false;
	Mutability mut_ = Mutable;
};