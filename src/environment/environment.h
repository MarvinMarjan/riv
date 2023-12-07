#pragma once

#include <map>
#include <string>



struct Token;

class Type;


class Environment
{
public:
	Environment() = default;
	Environment(Environment* enclosing);


	void declare(const std::string& name, const Type& value) noexcept;
	void assign(const Token& identifier, const Type& value);
	Type get(const Token& identifier) const;


private:
	std::map<std::string, Type> data_;

	Environment* enclosing_ = nullptr;
};