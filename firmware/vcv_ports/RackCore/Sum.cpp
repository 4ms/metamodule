#include "plugin.hpp"

namespace rack::core
{

struct Sum : Module {
	static constexpr unsigned MaxPoly = CoreProcessor::MaxPolyChannels;
	enum ParamIds { LEVEL_PARAM, NUM_PARAMS };
	enum InputIds { POLY_INPUT, NUM_INPUTS };
	enum OutputIds { MONO_OUTPUT, NUM_OUTPUTS };
	enum LightIds { ENUMS(VU_LIGHTS, 6), NUM_LIGHTS };
	enum DisplayIds { ChannelDisplay = 0 };

	dsp::VuMeter2 vuMeter;
	dsp::ClockDivider vuDivider;
	dsp::ClockDivider lightDivider;
	int lastChannels = 0;

	Sum() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam(LEVEL_PARAM, 0.f, 1.f, 1.f, "Level", "%", 0.f, 100.f);
		configInput(POLY_INPUT, "Polyphonic");
		configOutput(MONO_OUTPUT, "Monophonic");

		vuMeter.lambda = 1 / 0.1f;
		vuDivider.setDivision(16);
		lightDivider.setDivision(512);
	}

	void process(const ProcessArgs &args) override {
		float sum = inputs[POLY_INPUT].getVoltageSum();
		sum *= params[LEVEL_PARAM].getValue();
		outputs[MONO_OUTPUT].setVoltage(sum);

		if (vuDivider.process()) {
			vuMeter.process(args.sampleTime * vuDivider.getDivision(), sum / 10.f);
		}

		// Set channel lights infrequently
		if (lightDivider.process()) {
			lastChannels = inputs[POLY_INPUT].getChannels();

			lights[VU_LIGHTS + 0].setBrightness(vuMeter.getBrightness(0, 0));
			lights[VU_LIGHTS + 1].setBrightness(vuMeter.getBrightness(-3, 0));
			lights[VU_LIGHTS + 2].setBrightness(vuMeter.getBrightness(-6, -3));
			lights[VU_LIGHTS + 3].setBrightness(vuMeter.getBrightness(-12, -6));
			lights[VU_LIGHTS + 4].setBrightness(vuMeter.getBrightness(-24, -12));
			lights[VU_LIGHTS + 5].setBrightness(vuMeter.getBrightness(-36, -24));
		}
	}

	size_t get_display_text(int display_id, std::span<char> text) override {
		int chars_written = snprintf(text.data(), text.size(), "%d", lastChannels);
		return (chars_written < 0) ? 0 : chars_written;
	}
};

struct SumWidget : ModuleWidget {
	SumWidget(Sum *module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/Sum.svg"),
							 asset::plugin(pluginInstance, "res/Sum-dark.svg")));

		addChild(createWidget<ThemedScrew>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ThemedScrew>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ThemedScrew>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ThemedScrew>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(7.62, 64.284)), module, Sum::LEVEL_PARAM));

		addInput(createInputCentered<ThemedPJ301MPort>(mm2px(Vec(7.62, 96.798)), module, Sum::POLY_INPUT));

		addOutput(createOutputCentered<ThemedPJ301MPort>(mm2px(Vec(7.62, 113.066)), module, Sum::MONO_OUTPUT));

		addChild(
			createLightCentered<SmallSimpleLight<RedLight>>(mm2px(Vec(10.808, 18.081)), module, Sum::VU_LIGHTS + 0));
		addChild(
			createLightCentered<SmallSimpleLight<YellowLight>>(mm2px(Vec(10.808, 23.378)), module, Sum::VU_LIGHTS + 1));
		addChild(
			createLightCentered<SmallSimpleLight<GreenLight>>(mm2px(Vec(10.808, 28.676)), module, Sum::VU_LIGHTS + 2));
		addChild(
			createLightCentered<SmallSimpleLight<GreenLight>>(mm2px(Vec(10.808, 33.973)), module, Sum::VU_LIGHTS + 3));
		addChild(
			createLightCentered<SmallSimpleLight<GreenLight>>(mm2px(Vec(10.808, 39.271)), module, Sum::VU_LIGHTS + 4));
		addChild(
			createLightCentered<SmallSimpleLight<GreenLight>>(mm2px(Vec(10.808, 44.568)), module, Sum::VU_LIGHTS + 5));

		auto *channelDisplay = createWidget<MetaModule::VCVTextDisplay>(mm2px(Vec(3.521, 77.191)));
		channelDisplay->box.size = mm2px(Vec(8.197, 8.197));
		channelDisplay->font = "Segment7Standard24";
		channelDisplay->color = Colors565::Yellow;
		channelDisplay->firstLightId = Sum::ChannelDisplay;
		addChild(channelDisplay);
	}
};

Model *modelSum = createModel<Sum, SumWidget>("Sum");

} // namespace rack::core
