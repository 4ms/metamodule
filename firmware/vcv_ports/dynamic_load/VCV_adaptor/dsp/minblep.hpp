#pragma once
#include "VCV_adaptor/dsp/minblep_4_32.h"
#include "VCV_adaptor/math.hpp"

namespace rack::dsp
{

/** Computes the minimum-phase bandlimited step (MinBLEP)
z: number of zero-crossings
o: oversample factor
output: must be length `2 * z * o`.
https://www.cs.cmu.edu/~eli/papers/icmc01-hardsync.pdf
*/

// void minBlepImpulse(int z, int o, float *output);

template<int Z, int O, typename T = float>
struct MinBlepGenerator {
	T buf[2 * Z] = {};
	int pos = 0;
	float impulse[2 * Z * O + 1]{};

	MinBlepGenerator() {
		// This call will fail:
		// TODO: compile-time create a LUT using Z and O
		minBlepImpulse(Z, O, impulse);
		impulse[2 * Z * O] = 1.f;
	}

	/** Places a discontinuity with magnitude `x` at -1 < p <= 0 relative to the current frame */
	void insertDiscontinuity(float p, T x) {
		if (!(-1 < p && p <= 0))
			return;
		for (int j = 0; j < 2 * Z; j++) {
			float minBlepIndex = ((float)j - p) * O;
			int index = (pos + j) % (2 * Z);
			buf[index] += x * (-1.f + math::interpolateLinear(impulse, minBlepIndex));
		}
	}

	T process() {
		T v = buf[pos];
		buf[pos] = T(0);
		pos = (pos + 1) % (2 * Z);
		return v;
	}
};

// This is actually a MinBlepGenerator<4, 32, float> (Z = 4, not 16)
// We use the Z=4 version as a fake for the Z=16 version because
// otherwise processing load reaches 100% with the EvenVCO.
template<>
struct MinBlepGenerator<16, 32, float> {
	static constexpr int Z = 4;
	static constexpr int O = 32;
	using T = float;

	T buf[2 * Z] = {};
	int pos = 0;

	/** Places a discontinuity with magnitude `x` at -1 < p <= 0 relative to the current frame */
	void insertDiscontinuity(float p, T x) {
		if (!(-1 < p && p <= 0))
			return;
		for (int j = 0; j < 2 * Z; j++) {
			float minBlepIndex = ((float)j - p) * O;
			int index = (pos + j) & (2 * Z - 1);
			buf[index] += x * (-1.f + math::interpolateLinear(MinBlep_4_32.data(), minBlepIndex));
		}
	}

	T process() {
		T v = buf[pos];
		buf[pos] = T(0);
		pos = (pos + 1) % (2 * Z);
		return v;
	}
};

} // namespace rack::dsp
