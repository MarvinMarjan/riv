#include <environment/environment.h>

#include <interpreter/interpreter.h>
#include <system/sysstate.h>
#include <system/init.h>
#include <system/exception.h>
#include <language/error_codes.h>
#include <common/vector.h>

#include <specter/output/ostream.h>



Environment::Environment(Environment* enclosing)
{
	enclosing_ = enclosing;
}




void Environment::import(const std::map<std::string, Type>& other) noexcept
{
	for (const auto& [name, value] : other)
		if (!defined(name))
			declare(name, value);
}




void Environment::declare(const std::string& name, const Type& value) noexcept
{
	// if (data_.contains(name))
	// 	throw riv_e305();

	data_.insert({ name, value });
}


void Environment::assign(const Token& identifier, const Type& value)
{
	if (data_.contains(identifier.lexeme))
	{
		data_.at(identifier.lexeme) = value;
		return;
	}

	if (enclosing_)
	{
		enclosing_->assign(identifier, value);
		return;
	}

	throw riv_e301(identifier.pos); // undefined identifier
}


Type Environment::get(const Token& identifier) const
{
	if (data_.contains(identifier.lexeme))
		return data_.at(identifier.lexeme);

	if (enclosing_)
		return enclosing_->get(identifier);

	throw riv_e301(identifier.pos); // undefined identifier
}



bool Environment::defined(const std::string& identifier) const noexcept
{
	if (data_.contains(identifier))
		return true;

	if (enclosing_)
		return enclosing_->defined(identifier);

	return false;
}



Environment* Environment::top() noexcept
{
	Environment* current = this;

	while (current->enclosing_)
		current = current->enclosing_;

	return current;
}