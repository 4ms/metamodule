#pragma once
#include <stdint.h>

template<int N>
struct Log2 {
	static constexpr int val = Log2<N / 2>::val + 1;
};

template<>
struct Log2<1> {
	static constexpr int val = 0;
};

constexpr bool is_power_of_2(int v)
{
	return v && ((v & (v - 1)) == 0);
}

constexpr int ipow(int a, int b)
{
	return b == 0 ? 1 : a * ipow(a, b - 1);
}

template<typename T>
constexpr unsigned int bipolar_type_range(T val)
{
	return ipow(2, (sizeof(val) * 8) - 1) - 1;
}

template<uint32_t Max, typename T = uint32_t>
T wrap(T val)
{
	while (val >= Max)
		val -= Max;
	return val;
}
