#include "plugin.hpp"
#include "warps/dsp/modulator.h"


struct Warps : Module {
	enum ParamIds {
		ALGORITHM_PARAM,
		TIMBRE_PARAM,
		STATE_PARAM,
		LEVEL1_PARAM,
		LEVEL2_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		LEVEL1_INPUT,
		LEVEL2_INPUT,
		ALGORITHM_INPUT,
		TIMBRE_INPUT,
		CARRIER_INPUT,
		MODULATOR_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		MODULATOR_OUTPUT,
		AUX_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		CARRIER_GREEN_LIGHT, CARRIER_RED_LIGHT,
		ALGORITHM_LIGHT,
		NUM_LIGHTS = ALGORITHM_LIGHT + 3
	};


	int frame = 0;
	warps::Modulator modulator;
	warps::ShortFrame inputFrames[60] = {};
	warps::ShortFrame outputFrames[60] = {};
	dsp::SchmittTrigger stateTrigger;

	Warps() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam(ALGORITHM_PARAM, 0.0, 8.0, 0.0, "Algorithm");
		configParam(TIMBRE_PARAM, 0.0, 1.0, 0.5, "Timbre", "%", 0, 100);
		configButton(STATE_PARAM, "Internal oscillator mode");
		configParam(LEVEL1_PARAM, 0.0, 1.0, 1.0, "External oscillator amplitude / internal oscillator frequency", "%", 0, 100);
		configParam(LEVEL2_PARAM, 0.0, 1.0, 1.0, "Modulator amplitude", "%", 0, 100);

		configInput(LEVEL1_INPUT, "Level 1");
		configInput(LEVEL2_INPUT, "Level 2");
		configInput(ALGORITHM_INPUT, "Algorithm");
		configInput(TIMBRE_INPUT, "Timbre");
		configInput(CARRIER_INPUT, "Carrier");
		configInput(MODULATOR_INPUT, "Modulator");

		configOutput(MODULATOR_OUTPUT, "Modulator");
		configOutput(AUX_OUTPUT, "Auxiliary");

		configBypass(MODULATOR_INPUT, MODULATOR_OUTPUT);

		memset(&modulator, 0, sizeof(modulator));
		modulator.Init(96000.0f);
	}

	void process(const ProcessArgs& args) override {
		// State trigger
		warps::Parameters* p = modulator.mutable_parameters();
		if (stateTrigger.process(params[STATE_PARAM].getValue())) {
			p->carrier_shape = (p->carrier_shape + 1) % 4;
		}
		lights[CARRIER_GREEN_LIGHT].value = (p->carrier_shape == 1 || p->carrier_shape == 2) ? 1.0 : 0.0;
		lights[CARRIER_RED_LIGHT].value = (p->carrier_shape == 2 || p->carrier_shape == 3) ? 1.0 : 0.0;

		// Buffer loop
		if (++frame >= 60) {
			frame = 0;

			p->channel_drive[0] = clamp(params[LEVEL1_PARAM].getValue() + inputs[LEVEL1_INPUT].getVoltage() / 5.0f, 0.0f, 1.0f);
			p->channel_drive[1] = clamp(params[LEVEL2_PARAM].getValue() + inputs[LEVEL2_INPUT].getVoltage() / 5.0f, 0.0f, 1.0f);
			p->modulation_algorithm = clamp(params[ALGORITHM_PARAM].getValue() / 8.0f + inputs[ALGORITHM_INPUT].getVoltage() / 5.0f, 0.0f, 1.0f);

			{
				// TODO
				// Use the correct light color
				NVGcolor algorithmColor = nvgHSL(p->modulation_algorithm, 1.0, 0.5);
				lights[ALGORITHM_LIGHT + 0].setBrightness(algorithmColor.r);
				lights[ALGORITHM_LIGHT + 1].setBrightness(algorithmColor.g);
				lights[ALGORITHM_LIGHT + 2].setBrightness(algorithmColor.b);
			}

			p->modulation_parameter = clamp(params[TIMBRE_PARAM].getValue() + inputs[TIMBRE_INPUT].getVoltage() / 5.0f, 0.0f, 1.0f);

			p->frequency_shift_pot = params[ALGORITHM_PARAM].getValue() / 8.0;
			p->frequency_shift_cv = clamp(inputs[ALGORITHM_INPUT].getVoltage() / 5.0f, -1.0f, 1.0f);
			p->phase_shift = p->modulation_algorithm;
			p->note = 60.0 * params[LEVEL1_PARAM].getValue() + 12.0 * inputs[LEVEL1_INPUT].getNormalVoltage(2.0) + 12.0;
			p->note += log2f(96000.0f * args.sampleTime) * 12.0f;

			modulator.Process(inputFrames, outputFrames, 60);
		}

		inputFrames[frame].l = clamp((int)(inputs[CARRIER_INPUT].getVoltage() / 16.0 * 0x8000), -0x8000, 0x7fff);
		inputFrames[frame].r = clamp((int)(inputs[MODULATOR_INPUT].getVoltage() / 16.0 * 0x8000), -0x8000, 0x7fff);
		outputs[MODULATOR_OUTPUT].setVoltage((float)outputFrames[frame].l / 0x8000 * 5.0);
		outputs[AUX_OUTPUT].setVoltage((float)outputFrames[frame].r / 0x8000 * 5.0);
	}

	json_t* dataToJson() override {
		json_t* rootJ = json_object();
		warps::Parameters* p = modulator.mutable_parameters();
		json_object_set_new(rootJ, "shape", json_integer(p->carrier_shape));
		return rootJ;
	}

	void dataFromJson(json_t* rootJ) override {
		json_t* shapeJ = json_object_get(rootJ, "shape");
		warps::Parameters* p = modulator.mutable_parameters();
		if (shapeJ) {
			p->carrier_shape = json_integer_value(shapeJ);
		}
	}

	void onReset() override {
		warps::Parameters* p = modulator.mutable_parameters();
		p->carrier_shape = 0;
	}

	void onRandomize() override {
		warps::Parameters* p = modulator.mutable_parameters();
		p->carrier_shape = random::u32() % 4;
	}
};


struct WarpsWidget : ModuleWidget {
	WarpsWidget(Warps* module) {
		setModule(module);
		setPanel(Svg::load(asset::plugin(pluginInstance, "res/Warps.svg")));

		addChild(createWidget<ScrewSilver>(Vec(15, 0)));
		addChild(createWidget<ScrewSilver>(Vec(120, 0)));
		addChild(createWidget<ScrewSilver>(Vec(15, 365)));
		addChild(createWidget<ScrewSilver>(Vec(120, 365)));

		addParam(createParamCentered<Rogan6PSWhite>(Vec(73.556641, 96.560532), module, Warps::ALGORITHM_PARAM));
		addParam(createParam<Rogan1PSWhite>(Vec(94, 173), module, Warps::TIMBRE_PARAM));
		addParam(createParam<TL1105>(Vec(16, 182), module, Warps::STATE_PARAM));
		addParam(createParam<Trimpot>(Vec(14, 213), module, Warps::LEVEL1_PARAM));
		addParam(createParam<Trimpot>(Vec(53, 213), module, Warps::LEVEL2_PARAM));

		addInput(createInput<PJ301MPort>(Vec(8, 273), module, Warps::LEVEL1_INPUT));
		addInput(createInput<PJ301MPort>(Vec(44, 273), module, Warps::LEVEL2_INPUT));
		addInput(createInput<PJ301MPort>(Vec(80, 273), module, Warps::ALGORITHM_INPUT));
		addInput(createInput<PJ301MPort>(Vec(116, 273), module, Warps::TIMBRE_INPUT));

		addInput(createInput<PJ301MPort>(Vec(8, 316), module, Warps::CARRIER_INPUT));
		addInput(createInput<PJ301MPort>(Vec(44, 316), module, Warps::MODULATOR_INPUT));
		addOutput(createOutput<PJ301MPort>(Vec(80, 316), module, Warps::MODULATOR_OUTPUT));
		addOutput(createOutput<PJ301MPort>(Vec(116, 316), module, Warps::AUX_OUTPUT));

		addChild(createLight<SmallLight<GreenRedLight>>(Vec(21, 167), module, Warps::CARRIER_GREEN_LIGHT));
		addChild(createLightCentered<Rogan6PSLight<RedGreenBlueLight>>(Vec(73.556641, 96.560532), module, Warps::ALGORITHM_LIGHT));
	}
};


Model* modelWarps = createModel<Warps, WarpsWidget>("Warps");
