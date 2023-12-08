#include <environment/environment.h>

#include <system/exception.h>
#include <language/error_codes.h>



Environment::Environment(Environment* enclosing)
{
	enclosing_ = enclosing;
}



void Environment::declare(const std::string& name, const Type& value) noexcept
{
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

	throw riv_e301(identifier); // undefined identifier
}


Type Environment::get(const Token& identifier) const
{
	if (data_.contains(identifier.lexeme))
		return data_.at(identifier.lexeme);

	if (enclosing_)
		return enclosing_->get(identifier);

	throw riv_e301(identifier); // undefined identifier
}


#include <specter/output/ostream.h>


Environment* Environment::top() noexcept
{
	Environment* current = this;

	sp::println("top begin");
	
	while (current->enclosing_)
	{
		sp::println(current->enclosing_);
		current = current->enclosing_;
	}

	sp::println("top end");

	return current;
}