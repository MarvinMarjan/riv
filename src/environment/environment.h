#pragma once

#include <map>
#include <vector>

#include <scanner/token.h>



struct Exception;


class Environment
{
public:

	// stores useful identifier data
	struct IdentifierData
	{
		IdentifierData() = default;
		IdentifierData(const TokenPosition& pos, const Type& value, const std::string& filepath)
			: value(value), pos(pos), filepath(filepath) {}

		Type value;
		TokenPosition pos;
		std::string filepath;
	};


	Environment() = default;
	Environment(Environment* enclosing);


	void import(const std::map<std::string, IdentifierData>& other);


	void declare(const Token& name, const Type& value);
	void declare(const std::string& name, const IdentifierData& data);

	void assign(const Token& identifier, const Type& value);
	Type get(const Token& identifier) const;

	bool defined(const std::string& identifier) const noexcept;


	Environment* top() noexcept;
	Environment* enclosing() noexcept { return enclosing_; }


	void set_enclosing(Environment* const enclosing) noexcept { enclosing_ = enclosing; }


	const std::map<std::string, IdentifierData>& data() const noexcept { return data_; }


private:
	std::map<std::string, IdentifierData> data_;


	Environment* enclosing_ = nullptr;
};