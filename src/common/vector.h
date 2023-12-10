#pragma once

#include <vector>
#include <algorithm>



template <typename _Type>
inline bool exists(const std::vector<_Type>& vec, const _Type& value) noexcept {
	return std::find(vec.cbegin(), vec.cend(), value) != vec.cend();
}