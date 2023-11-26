#include <common/filesys.h>

#include <fstream>
#include <filesystem>

#include <common/string.h>



std::string read_file(const std::string& path)
{
	// if path does not exists, throws an exception.
	if (!path_exists(path))
		throw FileException(path, "File does not exists.");

	std::fstream file(path);

	// path may exists, but can it be opened as a file?
	if (!file.is_open())
		throw FileException(path, "Could not open file.");

	std::string content = "";
	std::string buffer;

	// reads every line of the file
	while (std::getline(file, buffer))
		content += buffer + '\n';

	// last endline ('\n')
	content.erase(content.cend() - 1);

	return content;
}



std::vector<std::string> read_file_as_vec(const std::string& path)
{
	// just read and split the content
	std::string content = read_file(path);
	return split(content, '\n');
}



bool path_exists(const std::string& path) noexcept {
	return std::filesystem::exists(path);
}