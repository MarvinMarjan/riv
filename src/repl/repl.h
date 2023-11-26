#pragma once

#include <map>

#include <specter/input/istream.h>
#include <specter/output/color/painter/painter.h>



// language REPL implementer
class RivREPL : public sp::StdIstream
{

	// returns a vector containing all keys of a map
	template <typename _Key, typename _Value>
	static std::vector<_Key> get_keys_from_map(const std::map<_Key, _Value>& map);

public:
	RivREPL();


private:
	sp::Painter painter_;



	std::string format() noexcept override { return painter_.paint(m_data); }
};






template <typename _Key, typename _Value>
std::vector<_Key> RivREPL::get_keys_from_map(const std::map<_Key, _Value>& map)
{
	std::vector<_Key> keys;

	for (const auto& [key, value] : map)
		keys.push_back(key);

	return keys;
}