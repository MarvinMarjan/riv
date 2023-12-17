#pragma once

#include <map>

#include <specter/input/istream.h>
#include <specter/output/color/painter/painter.h>



// language REPL implementer
class RivREPL : public sp::StdIstream
{

	// returns a vector containing all keys of a map
	template <typename KeyType, typename ValueType>
	static std::vector<KeyType> get_keys_from_map(const std::map<KeyType, ValueType>& map);

public:
	RivREPL();


private:
	sp::Painter painter_;



	std::string format() noexcept override { return painter_.paint(m_data); }
};






template <typename KeyType, typename ValueType>
std::vector<KeyType> RivREPL::get_keys_from_map(const std::map<KeyType, ValueType>& map)
{
	std::vector<KeyType> keys;

	for (const auto& [key, value] : map)
		keys.push_back(key);

	return keys;
}