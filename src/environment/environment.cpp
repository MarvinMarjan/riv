#include <environment/environment.h>

#include <filesystem>

#include <system/sysstate.h>
#include <system/init.h>
#include <system/exception.h>
#include <language/error_codes.h>



Environment::Environment(Environment* enclosing)
{
	enclosing_ = enclosing;
}




void Environment::import(const std::map<std::string, IdentifierData>& other)
{
	for (const auto& [name, data] : other)
		declare(name, data);
}




void Environment::declare(const Token& name, const Type& value) {
	declare(name.lexeme, IdentifierData(name.pos, value, sys_state().source_path));
}


void Environment::declare(const std::string& name, const IdentifierData& data)
{
	if (data_.contains(name))
	{
		const IdentifierData decldata = data_[name];
	 	throw riv_e305(name, data.pos, decldata.pos, std::filesystem::path(decldata.filepath).filename().string());
	}

	data_.insert({ name, data });
}




void Environment::assign(const Token& identifier, const Type& value)
{
	if (data_.contains(identifier.lexeme))
	{
		if (data_[identifier.lexeme].value.mutability() != Type::Mutable)
			throw riv_e310(identifier.pos); // cannot modify the value of an immutable variable

		data_[identifier.lexeme].value = value;
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
		return data_.at(identifier.lexeme).value;

	if (enclosing_)
		return enclosing_->get(identifier);

	throw riv_e301(identifier.pos); // undefined identifier
}


Type Environment::get(const std::string &identifier) const noexcept
{
	if (data_.contains(identifier))
		return data_.at(identifier).value;

	if (enclosing_)
		return enclosing_->get(identifier);

	return {};
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