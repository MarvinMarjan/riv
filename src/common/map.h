#pragma once

#include <map>
#include <vector>



// returns a vector containing all keys of a map
template <typename KeyType, typename ValueType>
static std::vector<KeyType> get_keys_from_map(const std::map<KeyType, ValueType>& map);






template <typename KeyType, typename ValueType>
std::vector<KeyType> get_keys_from_map(const std::map<KeyType, ValueType>& map)
{
	std::vector<KeyType> keys;

	for (const auto& [key, value] : map)
		keys.push_back(key);

	return keys;
}