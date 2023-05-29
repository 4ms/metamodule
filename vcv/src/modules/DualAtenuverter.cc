#include "CoreModules/befaco/DualAttenCore.hh"
#include "modules/Befaco/widgets.hh"
#include "plugin.hh"

using namespace rack;

struct DualAtenuverter : DualAtenuverterCore {
	enum ParamIds { ATEN1_PARAM, OFFSET1_PARAM, ATEN2_PARAM, OFFSET2_PARAM, NUM_PARAMS };
	enum InputIds { IN1_INPUT, IN2_INPUT, NUM_INPUTS };
	enum OutputIds { OUT1_OUTPUT, OUT2_OUTPUT, NUM_OUTPUTS };
	enum LightIds { ENUMS(OUT1_LIGHT, 3), ENUMS(OUT2_LIGHT, 3), NUM_LIGHTS };

	DualAtenuverter()
	{
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam(ATEN1_PARAM, -1.0, 1.0, 0.0, "Ch 1 gain");
		configParam(OFFSET1_PARAM, -10.0, 10.0, 0.0, "Ch 1 offset", " V");
		configParam(ATEN2_PARAM, -1.0, 1.0, 0.0, "Ch 2 gain");
		configParam(OFFSET2_PARAM, -10.0, 10.0, 0.0, "Ch 2 offset", " V");
		configBypass(IN1_INPUT, OUT1_OUTPUT);
		configBypass(IN2_INPUT, OUT2_OUTPUT);
	}
};

struct DualAtenuverterWidget : ModuleWidget {
	DualAtenuverterWidget(DualAtenuverter *module)
	{
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/panels/DualAtenuverter.svg")));

		addChild(createWidget<Knurlie>(Vec(15, 0)));
		addChild(createWidget<Knurlie>(Vec(15, 365)));

		addParam(createParam<Davies1900hWhiteKnob>(Vec(20, 33), module, DualAtenuverter::ATEN1_PARAM));
		addParam(createParam<Davies1900hRedKnob>(Vec(20, 91), module, DualAtenuverter::OFFSET1_PARAM));
		addParam(createParam<Davies1900hWhiteKnob>(Vec(20, 201), module, DualAtenuverter::ATEN2_PARAM));
		addParam(createParam<Davies1900hRedKnob>(Vec(20, 260), module, DualAtenuverter::OFFSET2_PARAM));

		addInput(createInput<BefacoInputPort>(Vec(7, 152), module, DualAtenuverter::IN1_INPUT));
		addOutput(createOutput<BefacoOutputPort>(Vec(43, 152), module, DualAtenuverter::OUT1_OUTPUT));

		addInput(createInput<BefacoInputPort>(Vec(7, 319), module, DualAtenuverter::IN2_INPUT));
		addOutput(createOutput<BefacoOutputPort>(Vec(43, 319), module, DualAtenuverter::OUT2_OUTPUT));

		addChild(createLight<MediumLight<RedGreenBlueLight>>(Vec(33, 143), module, DualAtenuverter::OUT1_LIGHT));
		addChild(createLight<MediumLight<RedGreenBlueLight>>(Vec(33, 311), module, DualAtenuverter::OUT2_LIGHT));
	}
};

Model *modelDualAtenuverter = createModel<DualAtenuverter, DualAtenuverterWidget>("DualAtenuverter");
