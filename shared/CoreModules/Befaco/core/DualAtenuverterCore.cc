#include "DualAtenuverterCore.hh"

namespace MetaModule
{

void DualAtenuverterCore::process(const ProcessArgs &args) {
	using namespace rack::math;
	// using simd::float_4;

	float_4 out1[4] = {};
	float_4 out2[4] = {};

	int channels1 = inputs[IN1_INPUT].getChannels();
	channels1 = channels1 > 0 ? channels1 : 1;
	int channels2 = inputs[IN2_INPUT].getChannels();
	channels2 = channels2 > 0 ? channels2 : 1;

	float att1 = params[ATEN1_PARAM].getValue();
	float att2 = params[ATEN2_PARAM].getValue();

	float offset1 = params[OFFSET1_PARAM].getValue();
	float offset2 = params[OFFSET2_PARAM].getValue();

	for (int c = 0; c < channels1; c += 4) {
		out1[c / 4] = clamp(inputs[IN1_INPUT].getVoltageSimd<float_4>(c) * att1 + offset1, -10.f, 10.f);
	}
	for (int c = 0; c < channels2; c += 4) {
		out2[c / 4] = clamp(inputs[IN2_INPUT].getVoltageSimd<float_4>(c) * att2 + offset2, -10.f, 10.f);
	}

	outputs[OUT1_OUTPUT].setChannels(channels1);
	outputs[OUT2_OUTPUT].setChannels(channels2);

	for (int c = 0; c < channels1; c += 4) {
		outputs[OUT1_OUTPUT].setVoltageSimd(out1[c / 4], c);
	}
	for (int c = 0; c < channels2; c += 4) {
		outputs[OUT2_OUTPUT].setVoltageSimd(out2[c / 4], c);
	}

	float light1 = outputs[OUT1_OUTPUT].getVoltageSum() / channels1;
	float light2 = outputs[OUT2_OUTPUT].getVoltageSum() / channels2;

	if (channels1 == 1) {
		lights[OUT1_LIGHT + 0].setSmoothBrightness(light1 / 5.f, args.sampleTime);
		lights[OUT1_LIGHT + 1].setSmoothBrightness(-light1 / 5.f, args.sampleTime);
		lights[OUT1_LIGHT + 2].setBrightness(0.0f);
	} else {
		lights[OUT1_LIGHT + 0].setBrightness(0.0f);
		lights[OUT1_LIGHT + 1].setBrightness(0.0f);
		lights[OUT1_LIGHT + 2].setBrightness(10.0f);
	}

	if (channels2 == 1) {
		lights[OUT2_LIGHT + 0].setSmoothBrightness(light2 / 5.f, args.sampleTime);
		lights[OUT2_LIGHT + 1].setSmoothBrightness(-light2 / 5.f, args.sampleTime);
		lights[OUT2_LIGHT + 2].setBrightness(0.0f);
	} else {
		lights[OUT2_LIGHT + 0].setBrightness(0.0f);
		lights[OUT2_LIGHT + 1].setBrightness(0.0f);
		lights[OUT2_LIGHT + 2].setBrightness(10.0f);
	}
}

} // namespace MetaModule
