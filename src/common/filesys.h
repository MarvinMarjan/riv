#pragma once

#include <string>
#include <vector>



struct FileException
{
	const std::string path;
	const std::string msg;


	FileException(const std::string& path, const std::string& msg)
		: path(path), msg(msg) {}
};


// reads a file and returns its content as a whole string
std::string read_file(const std::string& path);

// reads a file and returns a vector containing every line of it
std::vector<std::string> read_file_as_vec(const std::string& path);



// checks if a file or path exists
bool path_exists(const std::string& path) noexcept;