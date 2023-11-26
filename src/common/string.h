#pragma once

#include <string>
#include <vector>



// splits a string at every splitter character into a vector
std::vector<std::string> split(const std::string& str, const char splitter = ' ') noexcept;


inline std::string bool_to_string(const bool value) noexcept {
	return value ? "true" : "false";
}