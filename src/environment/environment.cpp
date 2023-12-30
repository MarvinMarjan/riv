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


void Environment::import(const Library& library)
{
	libraries_.push_back(library);
}




void Environment::declare(const Token& name, const Type& value) {
	declare(name.lexeme, IdentifierData(name.pos, value, sys_state().source_path));
}


void Environment::declare(const std::string& name, const IdentifierData& data)
{
	// is it already defined in this scope? (can't have variable redeclaration in the same scope)
	if (defined_here(name))
	{
		const IdentifierData decldata = data_[name];
	 	throw riv_e305(name, data.pos, decldata.pos, std::filesystem::path(decldata.filepath).filename().string());
	}

	data_.insert({ name, data });
}



void Environment::assign(const Token& identifier, const Type& value)
{
	Type* val = nullptr;

	// is it defined?
	if ((val = defined(identifier.lexeme)))
	{
		// is it immutable?
		if (val->mutability() == Type::Immutable)
			throw riv_e310(identifier.pos); // cannot modify the value of an immutable variable

		*val = value;
		return;
	}

	throw riv_e301(identifier.pos); // undefined identifier
}



Type Environment::get(const Token& identifier)
{
	Type* value = nullptr;

	// is it defined?
	if ((value = defined(identifier.lexeme)))
		return *value;

	throw riv_e301(identifier.pos); // undefined identifier
}


Type Environment::get(const std::string& identifier) noexcept
{
	Type* value = nullptr;

	// is it defined?
	if ((value = defined(identifier)))
		return *value;

	return {};
}




bool Environment::is_symbol_in_libraries(const std::string& identifier) noexcept
{
	return is_symbol_in_libraries(identifier, false);
}




Type* Environment::defined(const std::string& identifier) noexcept
{
	// is it defined in the current scope?
	if (data_.contains(identifier))
		return &data_[identifier].value;

	// is it defined in the enclosing scope?
	if (enclosing_)
		return enclosing_->defined(identifier);

	// is it defined in the libraries loaded?
	// (if it is, add it to "data_" to avoid symbol dynamic loading every time it's referenced)
	if (is_symbol_in_libraries(identifier, true))
		return &data_[identifier].value;

	return nullptr;
}


Type* Environment::defined_here(const std::string& identifier) noexcept
{
	if (data_.contains(identifier))
		return &data_[identifier].value;

	// is global?
	if (!enclosing_ && is_symbol_in_libraries(identifier, true))
		return &data_[identifier].value;

	return nullptr;
}




Environment* Environment::top() noexcept
{
	Environment* current = this;

	while (current->enclosing_)
		current = current->enclosing_;

	return current;
}




bool Environment::is_symbol_in_libraries(const std::string& identifier, const bool add_to_data) noexcept
{
	LibSymbol symbol {};

	for (const Library& library : libraries_)
		if ((symbol = lib_load_riv_symbol(library.handler, identifier)).raw_symbol)
		{
			if (add_to_data)
				data_.insert({ identifier, IdentifierData({}, symbol, library.path) });

			return true;
		}

	return false;
}