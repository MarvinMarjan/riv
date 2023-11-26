#include <common/string.h>



std::vector<std::string> split(const std::string& str, const char splitter) noexcept
{
	std::vector<std::string> split;
	std::string word = "";

	// iterate through each character
	for (const char ch : str)
	{
		// is current char a splitter?
		if (ch == splitter)
		{
			split.push_back(word);	// add current word
			word.clear();			// clear the word
			continue;
		}

		word += ch;
	}

	// adds the last word
	if (!word.empty())
		split.push_back(word);

	return split;
}