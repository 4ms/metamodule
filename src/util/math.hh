#pragma once

template <uint32_t Max, typename T=uint32_t>
T wrap(T val) {
	while (val >= Max) val -= Max;
	return val;
}
