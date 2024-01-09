#include "plugin.hpp"

struct TestModule : Module {
	enum ParamIds { KNOB1_PARAM, NUM_PARAMS };
	enum InputIds { A1_INPUT, NUM_INPUTS };
	enum OutputIds { OUT1_OUTPUT, NUM_OUTPUTS };
	enum LightIds { NUM_LIGHTS };

	TestModule() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		// configParam(KNOB1_PARAM, -1.0, 1.0, 0.0, "First Knob");
	}

	void process(const ProcessArgs &args) override {
		outputs[OUT1_OUTPUT].setVoltage(inputs[A1_INPUT].getVoltage() + params[KNOB1_PARAM].getValue());
	}
};

struct TestWidget : ModuleWidget {
	TestWidget(TestModule *module) {
		setModule(module);
		// setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "not/a/real/path.svg")));

		// addChild(createWidget<ScrewSilver>(Vec(15, 0)));
		// addParam(createParam<Davies1900hRedKnob>(Vec(45, 37), module, TestModule::KNOB1_PARAM));
		// addInput(createInput<PJ301MPort>(Vec(7, 28), module, TestModule::A1_INPUT));
		// addOutput(createOutput<PJ301MPort>(Vec(7, 154), module, TestModule::OUT1_OUTPUT));
	}
};

Model *modelTest = createModel<TestModule, TestWidget>("TestModuleSlug");
