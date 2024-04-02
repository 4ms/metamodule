#pragma once
#include "util/math_tables.hh"
#include <algorithm>
#include <array>
#include <cstdint>
#include <cstdlib>
#include <numeric>
#include <optional>

namespace MathTools
{

#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288f
#endif
static constexpr float M_PIF = M_PI;

template<typename Tval, typename Tin, typename Tout>
static constexpr Tout
map_value(const Tval x, const Tin in_min, const Tin in_max, const Tout out_min, const Tout out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

template<typename T>
static constexpr T constrain(const T val, const T min, const T max) {
	return val < min ? min : val > max ? max : val;
}

template<typename T>
static constexpr T max(const T val1, const T val2) {
	if (val1 > val2) {
		return val1;
	} else {
		return val2;
	}
}

template<typename T>
static constexpr T min(const T val1, const T val2) {
	if (val1 < val2) {
		return val1;
	} else {
		return val2;
	}
}

template<typename T>
constexpr std::optional<T> between(T x, T low, T high) {
	return (x >= low && x <= high) ? std::optional<T>{x - low} : std::nullopt;
}

constexpr inline float interpolate(float in1, float in2, float phase) {
	return in1 * (1.0f - phase) + (in2 * phase);
}

// Optimized interpolate, may perform faster than interpolate
constexpr inline float interpolate3(float in1, float in2, float phase) {
	return in1 + phase * (in2 - in1);
}

static_assert(interpolate(1.f, 2.f, 0.25f) == interpolate3(1.f, 2.f, 0.25f));

template<uint32_t PhaseMax>
inline int32_t interpolate(int32_t in1, int32_t in2, int32_t phase) {
	return ((in2 * phase) + in1 * (PhaseMax - phase)) / PhaseMax;
}

template<class T>
T randomNumber(T minNum, T maxNum) {
	return map_value<int, long, T>(std::rand(), 0, RAND_MAX, minNum, maxNum);
}

template<unsigned int N>
struct Log2 {
	enum { val = Log2<N / 2>::val + 1 };
};

template<>
struct Log2<1> {
	enum { val = 0 };
};

constexpr bool is_power_of_2(unsigned int v) {
	return v && ((v & (v - 1)) == 0);
}

// Todo: log2_ceiling()

constexpr unsigned int log2_floor(const unsigned int x) {
	int i = 32;
	while (i--) {
		if (x & (1UL << i))
			return i;
	}
	return 0;
}

constexpr unsigned int ipow(unsigned int a, unsigned int b) {
	return b == 0 ? 1 : a * ipow(a, b - 1);
}

// Todo: this needs a better name
template<typename T>
constexpr unsigned int bipolar_type_range(T val) {
	return ipow(2, (sizeof(val) * 8) - 1) - 1;
}

template<uint32_t Max, typename T = uint32_t>
T wrap(T val) {
	while (val >= Max)
		val -= Max;
	return val;
}

constexpr float f_abs(float x) {
	return (x >= 0.f) ? x : -x;
}

template<typename T>
constexpr T abs_diff(T x, T y) {
	return (x >= y) ? x - y : y - x;
}

template<typename T>
constexpr T diff(T a, T b) {
	return (a > b) ? (a - b) : (b - a);
}

// Returns the signed difference between val and center,
constexpr inline int32_t plateau(int32_t val, uint32_t width, int32_t center) {
	int32_t high = center + width / 2;
	int32_t low = center - width / 2;
	if (val > high)
		return val - high;
	else if (val < low)
		return val - low;
	else
		return 0;
}

template<unsigned width, int center = 0>
constexpr inline auto plateau(int val) {
	return plateau(val, width, center);
}

template<unsigned width, typename T = int>
constexpr inline T plateau(T val, T center = T{0}) {
	return plateau(val, width, center);
}

static_assert(plateau<60>(-32) == -2, "");
static_assert(plateau<60>(-31) == -1, "");
static_assert(plateau<60>(-30) == 0, "");
static_assert(plateau<60>(-1) == 0, "");
static_assert(plateau<60>(0) == 0, "");
static_assert(plateau<60>(1) == 0, "");
static_assert(plateau<60>(30) == 0, "");
static_assert(plateau<60>(31) == 1, "");
static_assert(plateau<60>(32) == 2, "");

consteval auto array_adj_diff(auto arr) {
	// Get simple difference between elements, with first element copied
	decltype(arr) darr;
	std::adjacent_difference(arr.begin(), arr.end(), darr.begin());

	// Create a new array of size - 1
	std::array<typename decltype(arr)::value_type, arr.size() - 1> darrm1;

	// Drop the first element
	std::copy(std::next(darr.begin()), darr.end(), darrm1.begin());
	return darrm1;
}

// [0..1] --> [-1..1]
// 0.00 => 0
// 0.25 => -1
// 0.50 => 0
// 0.75 => 1
// 1.00 => 0
constexpr float faster_sine(float x) {
	x = (x * 2.f) - 1.f;
	return 4.f * (x - x * f_abs(x));
}

constexpr uint16_t swap_bytes16(uint16_t halfword) {
	return ((halfword & 0xFF) << 8) | (halfword >> 8);
}

constexpr uint32_t swap_bytes32(uint32_t word) {
	return ((word & 0x000000FF) << 24) | ((word & 0x0000FF00) << 8) | ((word & 0x00FF0000) >> 8) | (word >> 24);
}
constexpr uint32_t swap_bytes_and_combine(uint16_t halfword1, uint16_t halfword2) {
	return ((halfword1 & 0xFF) << 24) | ((halfword1 & 0xFF00) << 8) | ((halfword2 & 0x00FF) << 8) | (halfword2 >> 8);
}

constexpr float setPitchMultiple(float val) {
	float pitchMultiple = 1;
	if (val >= 0)
		pitchMultiple = exp5Table.interp(constrain(val, 0.0f, 1.0f));
	else {
		float invertPitch = val * -1.0f;
		pitchMultiple = 1.0f / exp5Table.interp(constrain(invertPitch, 0.0f, 1.0f));
	}

	return pitchMultiple;
}

static inline constexpr float audioFreqToNorm(float input) // normalized filter frequency conversion
{
	float output = 0;
	input = constrain(input, 20.0f, 20000.0f);
	float temp1 = logTable.interp(map_value(input, 20.0f, 20000.0f, 0.0f, 1.0f));
	output = (temp1 - 2.99573f) / (6.90776f);
	return output;
}

// Returns 2^x
static inline constexpr float pow2(float x) {
	x = x / 5.0f;
	float res = 1.f;
	for (;;) {
		if (x < 1.f) {
			// Note: exp5Table.interp(x) = 2^(x*5), where 0 <= x <= 1
			res *= exp5Table.interp(x);
			break;
		} else {
			res *= 32.f;
			x -= 1.f;
		}
	}
	return res;
}

//sin(x), for any x
static inline float sin(float x) {
	return sinTable.interp_wrap(x / (2.f * M_PIF));
}

//x=0..1 => sin(0..2pi)
static inline float sin01(float x) {
	return sinTable.interp_wrap(x);
}

static inline float cos(float x) {
	return sinTable.interp_wrap((x / (2.f * M_PIF)) + 0.25f);
}

static inline float cos_close(float x) {
	return sinTable.closest_wrap((x / (2.f * M_PIF)) + 0.25f);
}

static inline float tan(float x) {
	return tanTable.interp_wrap(x / M_PIF);
}

static inline float tan_close(float x) {
	return tanTable.closest_wrap(x / M_PIF);
}

// Apply a hysteresis threshold on a gate signal. Assumes 0.0f = off, 1.0f = on
// Converts a real-world analog signal (0.f to 1.0f) to a clean gate (0 or 1, but not in between)
// and debounces chatter when crossing the threshold -- without introducing delay like debouncers typically do.
// Slightly slower than hysteresis_feedback(), but with more intuitive parameters.
// The input must exceed the turn_on threshold to make the output 1
// and must go below turn_off threshold to make the output 0
// Returns updated output, which should be passed as old_val the next time the function is called
static inline constexpr float
hysteresis_gate(float turn_off_thresh, float turn_on_thresh, float last_output, float new_input) {
	float feedback_amt = (turn_on_thresh - turn_off_thresh) * 0.5f;
	float feedback = feedback_amt * last_output;
	float test_signal = new_input + feedback;
	float threshold = (turn_on_thresh + turn_off_thresh) * 0.5f;
	return test_signal > threshold ? 1.f : 0.f;
}

// Apply a hysteresis threshold on a gate signal. Assumes 0.0f = off, 1.0f = on
// Converts a real-world analog signal (0.f to 1.0f) to a clean gate (0 or 1, but not in between)
// and debounces chatter when crossing the threshold -- without introducing delay like debouncers typically do.
// Slightly faster version of hysteresis_gate(), where the two params are half the sum/difference of the on/off
// thresholds
// @param: feedback_coef: feedback amount (typically a small value, 0.1 for example)
// @param: thresh: threshold for turning on or off, after applying feedback. Typically 0.5f;
// @param: last_output: the last output value (0.f or 1.f)
// @param: new_input: the input value (0.f to 1.0f)
// The input must exceed the turn_on threshold to make the output 1
// and must go below turn_off threshold to make the output 0
// Returns updated output, which should be passed as old_val the next time the function is called
static inline constexpr float
hysteresis_feedback(float feedback_coef, float thresh, float last_output, float new_input) {
	return (new_input + last_output * feedback_coef) > thresh ? 1.f : 0.f;
}

}; // namespace MathTools
