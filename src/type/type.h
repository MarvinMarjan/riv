#pragma once

#include <variant>
#include <vector>

#include <type/non_assignable.h>
#include <language/api/api.h>



enum class TypeIndex
{
	Null = -1,

	String,
	Number,
	Bool,
	Array,
	Function,
	NonAssignable,
	Symbol
};


class RivFunction;
class RivPackage;

enum class TokenType;


std::string type_index_to_string(TypeIndex type) noexcept;


class Type;


using ArrayType = std::vector<Type>;
using VariantType = std::variant<std::string, double, bool, ArrayType, RivFunction*, NonAssignable*, APISymbolFormat>;


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


	std::string to_string()      const noexcept { return type_obj_to_string(*this);    }
	std::string type_to_string() const noexcept { return type_index_to_string(type()); }


	void set_mutability(const Mutability mut) noexcept { mut_ = mut; }

	Mutability mutability() const noexcept { return mut_; }


	bool is_typeof(const TypeIndex type) const noexcept { return this->type() == type; }

	bool is_null()               const noexcept  { return is_null_;                                  }
	bool is_str()                const noexcept  { return is_typeof(TypeIndex::String);        }
	bool is_num()                const noexcept  { return is_typeof(TypeIndex::Number);        }
	bool is_bool()               const noexcept  { return is_typeof(TypeIndex::Bool);          }
	bool is_array()              const noexcept  { return is_typeof(TypeIndex::Array);         }
	bool is_func()               const noexcept  { return is_typeof(TypeIndex::Function);      }
	bool is_non_assignable()     const noexcept  { return is_typeof(TypeIndex::NonAssignable); }
	bool is_symbol()             const noexcept  { return is_typeof(TypeIndex::Symbol); }


	// const references

	const std::string    & as_str()            const noexcept  { return std::get<std::string>(*this);           }
	const double         & as_num()            const noexcept  { return std::get<double>(*this);                }
	const bool           & as_bool()           const noexcept  { return std::get<bool>(*this);                  }
	const ArrayType      & as_array()          const noexcept  { return std::get<ArrayType>(*this);             }
	const RivFunction    * as_func()           const noexcept  { return std::get<RivFunction*>(*this);          }
	const NonAssignable  * as_non_assignable() const noexcept  { return std::get<NonAssignable*>(*this);        }
	const APISymbolFormat& as_symbol()         const noexcept  { return std::get<APISymbolFormat>(*this); }


	// references

	std::string    &       as_str()                  noexcept  { return std::get<std::string>(*this);           }
	double         &       as_num()                  noexcept  { return std::get<double>(*this);                }
	bool           &       as_bool()                 noexcept  { return std::get<bool>(*this);                  }
	ArrayType      &       as_array()                noexcept  { return std::get<ArrayType>(*this);             }
	RivFunction    *       as_func()                 noexcept  { return std::get<RivFunction*>(*this);          }
	NonAssignable  *       as_non_assignable()       noexcept  { return std::get<NonAssignable*>(*this);        }
	APISymbolFormat&       as_symbol()               noexcept  { return std::get<APISymbolFormat>(*this); }



	// non-assignable types

	bool is_package() const noexcept { return as_package(); }

	const RivPackage* as_package() const noexcept;


	RivPackage*       as_package()       noexcept;



	static bool equals(const Type& left, const Type& right) noexcept;
	static bool truthy(const Type& value)                   noexcept;


	// gets the mutability based on a modifier (mut, imut)
	static Mutability get_mutability_from_modifier(TokenType specifier, Mutability default_value) noexcept;

	// checks if a token is a valid mutability modifier
	static bool is_valid_mutability_modifier(TokenType specifier) noexcept;

private:
	bool       is_null_ = false;
	Mutability mut_     = Mutable;
};