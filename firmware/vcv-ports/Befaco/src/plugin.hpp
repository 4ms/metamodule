#pragma once
#include <rack.hpp>


using namespace rack;


extern Plugin* pluginInstance;

extern Model* modelEvenVCO;
extern Model* modelRampage;
extern Model* modelABC;
extern Model* modelSpringReverb;
extern Model* modelMixer;
extern Model* modelSlewLimiter;
extern Model* modelDualAtenuverter;
extern Model* modelPercall;
extern Model* modelHexmixVCA;
extern Model* modelChoppingKinky;
extern Model* modelKickall;
extern Model* modelSamplingModulator;
extern Model* modelMorphader;
extern Model* modelADSR;
extern Model* modelSTMix;
extern Model* modelMuxlicer;
extern Model* modelMex;
extern Model* modelNoisePlethora;
extern Model* modelChannelStrip;
extern Model* modelPonyVCO;
extern Model* modelMotionMTR;

#include "widgets.hpp"

inline int unsigned_modulo(int a, int b) {
	return ((a % b) + b) % b;
}

template <typename T>
T sin2pi_pade_05_5_4(T x) {
	x -= 0.5f;
	return (T(-6.283185307) * x + T(33.19863968) * simd::pow(x, 3) - T(32.44191367) * simd::pow(x, 5))
	       / (1 + T(1.296008659) * simd::pow(x, 2) + T(0.7028072946) * simd::pow(x, 4));
}

template <typename T>
T tanh_pade(T x) {
	T x2 = x * x;
	T q = 12.f + x2;
	return 12.f * x * q / (36.f * x2 + q * q);
}

template <typename T>
T exponentialBipolar80Pade_5_4(T x) {
	return (T(0.109568) * x + T(0.281588) * simd::pow(x, 3) + T(0.133841) * simd::pow(x, 5))
	       / (T(1.) - T(0.630374) * simd::pow(x, 2) + T(0.166271) * simd::pow(x, 4));
}

struct ADEnvelope {
	enum Stage {
		STAGE_OFF,
		STAGE_ATTACK,
		STAGE_DECAY
	};

	Stage stage = STAGE_OFF;
	float env = 0.f;
	float attackTime = 0.1, decayTime = 0.1;
	float attackShape = 1.0, decayShape = 1.0;

	ADEnvelope() { };

	void process(const float& sampleTime) {

		if (stage == STAGE_OFF) {
			env = envLinear = 0.0f;
		}
		else if (stage == STAGE_ATTACK) {
			envLinear += sampleTime / attackTime;
			env = std::pow(envLinear, attackShape);
		}
		else if (stage == STAGE_DECAY) {
			envLinear -= sampleTime / decayTime;
			env = std::pow(envLinear, decayShape);
		}

		if (envLinear >= 1.0f) {
			stage = STAGE_DECAY;
			env = envLinear = 1.0f;
		}
		else if (envLinear <= 0.0f) {
			stage = STAGE_OFF;
			env = envLinear = 0.0f;
		}
	}

	void trigger() {
		stage = ADEnvelope::STAGE_ATTACK;
		// non-linear envelopes won't retrigger at the correct starting point if
		// attackShape != decayShape, so we advance the linear envelope
		envLinear = std::pow(env, 1.0f / attackShape);
	}

private:
	float envLinear = 0.f;
};

// Creates a Butterworth 2*Nth order highpass filter for blocking DC
template<int N>
struct DCBlockerT {

	DCBlockerT() {
		setFrequency(0.1f);
	}

	// set frequency (in normalised units, 0 < fc < 1)
	void setFrequency(float fc) {
		fc_ = fc;
		recalculateCoefficients();
	}

	float process(float x) {
		for (int idx = 0; idx < N; idx++) {
			x = blockDCFilter[idx].process(x);
		}
		return x;
	}

private:

	// https://www.earlevel.com/main/2016/09/29/cascading-filters/
	void recalculateCoefficients() {

		float poleInc = M_PI / order;
		float firstAngle = poleInc / 2;

		for (int idx = 0; idx < N; idx++) {
			float Q = 1.0f / (2.0f * std::cos(firstAngle + idx * poleInc));
			blockDCFilter[idx].setParameters(dsp::BiquadFilter::HIGHPASS, fc_, Q, 1.0f);
		}
	}

	float fc_;
	static const int order = 2 * N;

	dsp::BiquadFilter blockDCFilter[N];
};

typedef DCBlockerT<2> DCBlocker;

/** When triggered, holds a high value for a specified time before going low again */
struct PulseGenerator_4 {
	simd::float_4 remaining = 0.f;

	/** Immediately disables the pulse */
	void reset() {
		remaining = 0.f;
	}

	/** Advances the state by `deltaTime`. Returns whether the pulse is in the HIGH state. */
	simd::float_4 process(float deltaTime) {

		simd::float_4 mask = (remaining > 0.f);

		remaining -= ifelse(mask, deltaTime, 0.f);
		return ifelse(mask, simd::float_4::mask(), 0.f);
	}

	/** Begins a trigger with the given `duration`. */
	void trigger(simd::float_4 mask, float duration = 1e-3f) {
		// Keep the previous pulse if the existing pulse will be held longer than the currently requested one.
		remaining = ifelse(mask & (duration > remaining), duration, remaining);
	}
};

// Zavalishin 2018, "The Art of VA Filter Design", http://www.native-instruments.com/fileadmin/ni_media/downloads/pdf/VAFilterDesign_2.0.0a.pdf
// Section 6.7, adopted from BogAudio Saturator https://github.com/bogaudio/BogaudioModules/blob/master/src/dsp/signal.cpp
template <class T>
struct Saturator {

	// saturate input at around ~[-1, +1] V with soft clipping
	static T process(T sample) {
		return simd::ifelse(sample < 0.f, -saturation(-sample), saturation(sample));
	}
private:

	static T saturation(T sample) {

		const float limit = 1.05f;
		const float y1 = 0.98765f; // (2*x - 1)/x**2 where x is 0.9.
		// correction so that saturation(0) = 0
		const float offset = 0.0062522; // -0.5f + sqrtf(0.5f * 0.5f) / y1;

		T x = sample / limit;
		T x1 = (x + 1.0f) * 0.5f;

		return limit * (offset + x1 - simd::sqrt(x1 * x1 - y1 * x) * (1.0f / y1));
	}
};
