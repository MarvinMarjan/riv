#include <environment/environment.h>

#include <system/exception.h>
#include <language/error_codes.h>
#include <scanner/token.h>



void Environment::declare(const std::string& name, const Type& value) noexcept
{
	data_.insert({ name, value });
}


void Environment::assign(const Token& identifier, const Type& value) noexcept
{
	if (!data_.contains(identifier.lexeme))
		throw riv_e301(identifier); // undefined identifier

	data_.at(identifier.lexeme) = value;
}


Type Environment::get(const Token& identifier) const
{
	if (!data_.contains(identifier.lexeme))
		throw riv_e301(identifier); // undefined identifier

	return data_.at(identifier.lexeme);
}