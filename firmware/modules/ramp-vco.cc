#include "ramp-vco.hh"

namespace DemoBuiltIns
{

RampVCO::RampVCO()
	: sample_rate{48000}
	, phase{0} {
}

void RampVCO::update() {
	float knob = getState<PitchKnob>();
	float cv = getInput<PitchCV>().value_or(0) / 5.f; // scaling will need to be adjusted based on hardware
	auto freq = (knob + cv) * 5000 + 20;			  //map freq
	freq = std::clamp(freq, 20.f, 20000.f);
	uint32_t inc = sample_rate / freq;

	// wrap-around
	phase += inc;
}

void RampVCO::set_samplerate(float sr) {
}

} // namespace DemoBuiltIns
