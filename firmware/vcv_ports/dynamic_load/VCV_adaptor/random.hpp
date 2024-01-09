#pragma once
#include "VCV_adaptor/common.hpp"
#include "VCV_adaptor/math.hpp"
#include <random>
#include <vector>

namespace rack::random
{

/** xoroshiro128+. Very fast, not-cryptographic random number generator.
From https://prng.di.unimi.it/
Example:

	std::random_device rd;
	random::Xoroshiro128Plus rng(rd(), rd());
	uint64_t r = rng();

	std::uniform_real_distribution<float> uniform(0.f, 1.f);
	float r = uniform(rng);

	std::normal_distribution<> normal(0.0, 1.0);
	double r = normal(rng);
*/
struct Xoroshiro128Plus {
	uint64_t state[2] = {};

	void seed(uint64_t s0, uint64_t s1); 
	bool isSeeded();

	static uint64_t rotl(uint64_t x, int k);
	uint64_t operator()(); 
	constexpr uint64_t min() const {
		return 0;
	}
	constexpr uint64_t max() const {
		return UINT64_MAX;
	}
};

// Simple global API

void init();

/** Returns the generator.
Named "local" because the generator was thread-local in previous versions.
*/
Xoroshiro128Plus &local();

template<typename T>
T get() {
	// Call operator()() and cast by default
	return local()();
}

template<>
inline uint32_t get() {
	// Take top 32 bits which has better randomness properties.
	return get<uint64_t>() >> 32;
}

template<>
inline uint16_t get() {
	return get<uint64_t>() >> 48;
}

template<>
inline uint8_t get() {
	return get<uint64_t>() >> 56;
}

template<>
inline bool get() {
	return get<uint64_t>() >> 63;
}

template<>
inline float get() {
	// The multiplier is 2f7fffff in hex. This gives maximum precision of uint32_t -> float conversion and its image is [0, 1).
	return get<uint32_t>() * 2.32830629e-10f;
}

template<>
inline double get() {
	return get<uint64_t>() * 5.421010862427522e-20;
}

/** Returns a uniform random uint64_t from 0 to UINT64_MAX */
inline uint64_t u64() {
	return get<uint64_t>();
}
/** Returns a uniform random uint32_t from 0 to UINT32_MAX */
inline uint32_t u32() {
	return get<uint32_t>();
}
/** Returns a uniform random float in the interval [0.0, 1.0) */
inline float uniform() {
	return get<float>();
}

/** Returns a normal random number with mean 0 and standard deviation 1 */
//TODO: replace with something less processor-intensive (no std::sqrt, std::log)
float normal(); 

/** Fills an array with random bytes. */
void buffer(uint8_t *out, size_t len);

/** Creates a vector of random bytes. */
std::vector<uint8_t> vector(size_t len);

} // namespace rack::random
