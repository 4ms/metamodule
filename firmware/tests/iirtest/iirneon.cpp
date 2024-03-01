#include "iirneon.hh"
#include <gcem.hpp>

static constexpr float SAMPLERATE = 48000.f;
static constexpr float fConst3 = gcem::pow(0.00100000005f, (1.66666663f / SAMPLERATE));
static constexpr float fConst6 = (fConst3 * fConst3);
static constexpr float fConst7 = gcem::pow(0.00100000005f, (1.75438595f / SAMPLERATE));
static constexpr float fConst9 = (fConst7 * fConst7);
static constexpr float fConst10 = gcem::pow(0.00100000005f, (1.85185182f / SAMPLERATE));
static constexpr float fConst12 = (fConst10 * fConst10);
static constexpr float fConst13 = gcem::pow(0.00100000005f, (1.96078432f / SAMPLERATE));
static constexpr float fConst15 = (fConst13 * fConst13);

void main()
{
	float params[4] = {0.1f, 0.2f, 0.3f, 0.4f};
	float consts[4] = {fConst6, fConst9, fConst12, fConst15};
	float mixweights[4] = {1.f, 0.25f, 0.111111112f, 0.0625f};

	ParallelBPIIR iir{params, consts, mixweights};

	// run it twice
	float out = iir.calc_4iir(1.2f);
	out = iir.calc_4iir(1.3f);

	// force compiler to keep values:
	volatile int x = out;
}

extern "C" void _exit(int) {}
