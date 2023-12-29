#pragma once

#include <map>
#include <vector>
#include <string>

#include <scanner/token.h>
#include <system/lib.h>



struct Exception;
struct APICallData;


class Environment
{
public:
	struct IdentifierData
	{
		IdentifierData() = default;
		IdentifierData(const TokenPosition& pos, const Type& value, const std::string& filepath)
				: value(value), pos(pos), filepath(filepath) {}

		Type          value;
		TokenPosition pos;
		std::string   filepath;
	};



	         Environment() = default;
	explicit Environment(Environment* enclosing);


	void import(const std::map<std::string, IdentifierData>& other);
	void import(const Library& library);


	void declare(const Token& name, const Type& value);
	void declare(const std::string& name, const IdentifierData& data);

	void assign(const Token& identifier, const Type& value);

	Type get(const Token& identifier);
	Type get(const std::string& identifier) noexcept;


	// returns true if "identifier" is defined in the libraries of "libraries_"
	bool is_symbol_in_libraries(const std::string& identifier) noexcept;


	// check if "identifier" is defined. if it is, then a pointer to it is returned.
	// "nullptr" is returned otherwise
	Type* defined     (const std::string& identifier) noexcept;

	// same as "Environment::defined", but the search is limited to the current scope.
	// (enclosing scopes are not searched)
	Type* defined_here(const std::string& identifier) noexcept;


	Environment* top() noexcept;
	Environment* enclosing() noexcept { return enclosing_; }


	void set_enclosing(Environment* const enclosing) noexcept { enclosing_ = enclosing; }


	const std::map<std::string, IdentifierData>& data() const noexcept { return data_; }


private:
	friend class Interpreter;


	// searches for "identifier" in all libraries loaded. if it was found, add it
	// to "data_". if it was not found, do nothing. the return value tells when the symbol
	// was found or not (true or false).
	bool is_symbol_in_libraries(const std::string& identifier, bool add_to_data) noexcept;


	std::map<std::string, IdentifierData> data_;
	std::vector<Library> libraries_; // loaded shared libraries


	Environment* enclosing_ = nullptr;
};