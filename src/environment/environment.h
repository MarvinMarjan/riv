#pragma once

#include <map>

#include <type/type.h>



struct Token;


class Environment
{
public:
	Environment() = default;
	Environment(Environment* enclosing);


	void declare(const std::string& name, const Type& value) noexcept;
	void assign(const Token& identifier, const Type& value) noexcept;
	Type get(const Token& identifier) const;


private:
	std::map<std::string, Type> data_;

	Environment* enclosing_ = nullptr;
};