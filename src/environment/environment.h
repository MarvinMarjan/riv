#pragma once

#include <map>
#include <string>
#include <vector>



struct Token;

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


	// get identifiers listed in "export_list_"
	std::map<std::string, Type> get_exported_identifiers() noexcept;


	Environment* top() noexcept;
	Environment* enclosing() noexcept { return enclosing_; }


	void set_enclosing(Environment* const enclosing) noexcept { enclosing_ = enclosing; }


	const std::map<std::string, Type>&	data()			const noexcept { return data_; }
	std::vector<std::string>			export_list()	const noexcept { return export_list_; }


private:
	friend class Interpreter;

	std::map<std::string, Type> data_;
	std::vector<std::string> export_list_;

	Environment* enclosing_ = nullptr;
};