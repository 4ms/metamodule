#pragma once
#include <stdint.h>

namespace MathTools
{

#ifndef M_PI
	#define M_PI 3.14159265358979323846264338327950288f
#endif

template<typename Tval, typename Tin, typename Tout>
static constexpr Tout
map_value(const Tval x, const Tin in_min, const Tin in_max, const Tout out_min, const Tout out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

template<typename T>
static constexpr T constrain(const T val, const T min, const T max)
{
	return val < min ? min : val > max ? max : val;
}

inline float interpolate(float in1, float in2, float x)
{
	return (in2 * x) + in1 * (1.0f - x);
}

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

constexpr unsigned int ipow(unsigned int a, unsigned int b)
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

} // namespace MathTools
