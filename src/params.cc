#include "math.hh"
#include "ui.hh"

void Params::update()
{
	freq[0] = controls.freq1_cv.get() / 4095.0f;
	freq[1] = controls.freq2_cv.get() / 4095.0f;

	res[0] = controls.res1_cv.get() / 4095.0f;
	res[1] = controls.res2_cv.get() / 4095.0f;

	//if (controls.pads.just_touched(0)) {
	if (controls.rotary_button[0].is_just_released()) {
		mode[0] = wrap<kNumFX>(mode[0] + 1);
	}
	// if (controls.pads.just_touched(1)) {
	if (controls.rotary_button[1].is_just_released()) {
		mode[1] = wrap<kNumFX>(mode[1] + 1);
	}
}

