#pragma once
#include <cmath>
#include <cstdint>
#include <cstdlib>

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

template<typename T>
static constexpr T max(const T val1, const T val2)
{
	if (val1 > val2) {
		return val1;
	} else {
		return val2;
	}
}

template<typename T>
static constexpr T min(const T val1, const T val2)
{
	if (val1 < val2) {
		return val1;
	} else {
		return val2;
	}
}

inline float interpolate(float in1, float in2, float phase)
{
	return (in2 * phase) + in1 * (1.0f - phase);
}

template<class T>
T randomNumber(T minNum, T maxNum)
{
	return map_value(std::rand(), 0, RAND_MAX, minNum, maxNum);
}

template<unsigned int N>
struct Log2 {
	static constexpr int val = Log2<N / 2>::val + 1;
};

template<>
struct Log2<1> {
	static constexpr int val = 0;
};

constexpr unsigned int Log2Int(const unsigned int x)
{
	for (int i = 0; i < 32; i++)
		if (x == (1UL << i))
			return i;
	return 0;
}

constexpr bool is_power_of_2(unsigned int v)
{
	return v && ((v & (v - 1)) == 0);
}

constexpr unsigned int ipow(unsigned int a, unsigned int b)
{
	return b == 0 ? 1 : a * ipow(a, b - 1);
}

// Todo: this needs a better name
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

constexpr float f_abs(float x)
{
	return (x >= 0.f) ? x : -x;
}

// [0..1] --> [-1..1]
// 0.00 => 0
// 0.25 => -1
// 0.50 => 0
// 0.75 => 1
// 1.00 => 0
constexpr float faster_sine(float x)
{
	x = (x * 2.f) - 1.f;
	return 4.f * (x - x * f_abs(x));
}

} // namespace MathTools
