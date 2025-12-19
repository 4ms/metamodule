#include "simple_vco.hh"

namespace DemoBuiltIns
{

SimpleVCO::SimpleVCO()
	: sample_rate{48000}
	, phase{0} {
}

void SimpleVCO::update() {
	float knob = getState<PitchKnob>();

	float cv = getInput<PitchCV>().value_or(0) / 5.f; // scaling will need to be adjusted based on hardware

	// Adjust this range as desired...
	auto freq = std::clamp((knob + cv) * 1000 + 20, 1.f, 10000.f);

	float inc = freq / sample_rate;

	phase += inc;
	if (phase > 1)
		phase = 0;

	setOutput<RampOut>(std::sin(2.f * M_PI * phase) * 5.f - 2.5f);
}

void SimpleVCO::set_samplerate(float sr) {
	sample_rate = sr;
}

} // namespace DemoBuiltIns
