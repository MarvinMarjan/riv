#pragma once

#include <string>



// every type derived from this will not be able to behave like other literal types (strings, numbers, booleans, ...)
class NonAssignable
{
public:
	NonAssignable(const std::string& type_name) : type_name_(type_name) {}
	virtual ~NonAssignable() = default;

	std::string type_name() const noexcept { return type_name_; }


private:
	std::string type_name_;
};