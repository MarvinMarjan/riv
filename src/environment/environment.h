#pragma once

#include <map>
#include <string>
#include <vector>



struct Token;
struct Exception;

class Type;


class Environment
{
public:
	Environment() = default;
	Environment(Environment* enclosing);


	void add_from(const std::map<std::string, Type>& other) noexcept;


	void declare(const std::string& name, const Type& value) noexcept;
	void assign(const Token& identifier, const Type& value);
	Type get(const Token& identifier) const;

	bool defined(const std::string& identifier) const noexcept;


	Environment* top() noexcept;
	Environment* enclosing() noexcept { return enclosing_; }


	void set_enclosing(Environment* const enclosing)	noexcept { enclosing_ = enclosing; }


	const std::map<std::string, Type>&	data()			const noexcept { return data_; }


private:
	friend class Interpreter;


	std::map<std::string, Type> data_;


	Environment* enclosing_ = nullptr;
};