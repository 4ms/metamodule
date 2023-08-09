#include "plugin.hpp"
#include "rings/dsp/part.h"
#include "rings/dsp/strummer.h"
#include "rings/dsp/string_synth_part.h"


struct Rings : Module {
	enum ParamIds {
		POLYPHONY_PARAM,
		RESONATOR_PARAM,

		FREQUENCY_PARAM,
		STRUCTURE_PARAM,
		BRIGHTNESS_PARAM,
		DAMPING_PARAM,
		POSITION_PARAM,

		BRIGHTNESS_MOD_PARAM,
		FREQUENCY_MOD_PARAM,
		DAMPING_MOD_PARAM,
		STRUCTURE_MOD_PARAM,
		POSITION_MOD_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		BRIGHTNESS_MOD_INPUT,
		FREQUENCY_MOD_INPUT,
		DAMPING_MOD_INPUT,
		STRUCTURE_MOD_INPUT,
		POSITION_MOD_INPUT,

		STRUM_INPUT,
		PITCH_INPUT,
		IN_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		ODD_OUTPUT,
		EVEN_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		POLYPHONY_GREEN_LIGHT, POLYPHONY_RED_LIGHT,
		RESONATOR_GREEN_LIGHT, RESONATOR_RED_LIGHT,
		NUM_LIGHTS
	};

	dsp::SampleRateConverter<1> inputSrc;
	dsp::SampleRateConverter<2> outputSrc;
	dsp::DoubleRingBuffer<dsp::Frame<1>, 256> inputBuffer;
	dsp::DoubleRingBuffer<dsp::Frame<2>, 256> outputBuffer;

	uint16_t reverb_buffer[32768] = {};
	rings::Part part;
	rings::StringSynthPart string_synth;
	rings::Strummer strummer;
	bool strum = false;
	bool lastStrum = false;

	dsp::SchmittTrigger polyphonyTrigger;
	dsp::SchmittTrigger modelTrigger;
	int polyphonyMode = 0;
	rings::ResonatorModel resonatorModel = rings::RESONATOR_MODEL_MODAL;
	bool easterEgg = false;

	Rings() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configButton(POLYPHONY_PARAM, "Polyphony");
		configButton(RESONATOR_PARAM, "Resonator type");
		configParam(FREQUENCY_PARAM, 0.0, 60.0, 30.0, "Frequency");
		configParam(STRUCTURE_PARAM, 0.0, 1.0, 0.5, "Structure");
		configParam(BRIGHTNESS_PARAM, 0.0, 1.0, 0.5, "Brightness");
		configParam(DAMPING_PARAM, 0.0, 1.0, 0.5, "Damping");
		configParam(POSITION_PARAM, 0.0, 1.0, 0.5, "Position");
		configParam(BRIGHTNESS_MOD_PARAM, -1.0, 1.0, 0.0, "Brightness CV");
		configParam(FREQUENCY_MOD_PARAM, -1.0, 1.0, 0.0, "Frequency CV");
		configParam(DAMPING_MOD_PARAM, -1.0, 1.0, 0.0, "Damping CV");
		configParam(STRUCTURE_MOD_PARAM, -1.0, 1.0, 0.0, "Structure CV");
		configParam(POSITION_MOD_PARAM, -1.0, 1.0, 0.0, "Position CV");

		configInput(BRIGHTNESS_MOD_INPUT, "Brightness");
		configInput(FREQUENCY_MOD_INPUT, "Frequency");
		configInput(DAMPING_MOD_INPUT, "Damping");
		configInput(STRUCTURE_MOD_INPUT, "Structure");
		configInput(POSITION_MOD_INPUT, "Position");
		configInput(STRUM_INPUT, "Strum");
		configInput(PITCH_INPUT, "Pitch (1V/oct)");
		configInput(IN_INPUT, "Audio");

		configOutput(ODD_OUTPUT, "Odd");
		configOutput(EVEN_OUTPUT, "Even");

		configBypass(IN_INPUT, ODD_OUTPUT);
		configBypass(IN_INPUT, EVEN_OUTPUT);

		strummer.Init(0.01, 44100.0 / 24);
		part.Init(reverb_buffer);
		string_synth.Init(reverb_buffer);
	}

	void process(const ProcessArgs& args) override {
		// TODO
		// "Normalized to a pulse/burst generator that reacts to note changes on the V/OCT input."
		// Get input
		if (!inputBuffer.full()) {
			dsp::Frame<1> f;
			f.samples[0] = inputs[IN_INPUT].getVoltage() / 5.0;
			inputBuffer.push(f);
		}

		if (!strum) {
			strum = inputs[STRUM_INPUT].getVoltage() >= 1.0;
		}

		// Polyphony / model
		if (polyphonyTrigger.process(params[POLYPHONY_PARAM].getValue())) {
			polyphonyMode = (polyphonyMode + 1) % 3;
		}
		lights[POLYPHONY_GREEN_LIGHT].value = (polyphonyMode == 0 || polyphonyMode == 1) ? 1.0 : 0.0;
		lights[POLYPHONY_RED_LIGHT].value = (polyphonyMode == 1 || polyphonyMode == 2) ? 1.0 : 0.0;

		if (modelTrigger.process(params[RESONATOR_PARAM].getValue())) {
			resonatorModel = (rings::ResonatorModel)((resonatorModel + 1) % 3);
		}
		int modelColor = resonatorModel % 3;
		lights[RESONATOR_GREEN_LIGHT].value = (modelColor == 0 || modelColor == 1) ? 1.0 : 0.0;
		lights[RESONATOR_RED_LIGHT].value = (modelColor == 1 || modelColor == 2) ? 1.0 : 0.0;

		// Render frames
		if (outputBuffer.empty()) {
			float in[24] = {};
			// Convert input buffer
			{
				inputSrc.setRates(args.sampleRate, 48000);
				int inLen = inputBuffer.size();
				int outLen = 24;
				inputSrc.process(inputBuffer.startData(), &inLen, (dsp::Frame<1>*) in, &outLen);
				inputBuffer.startIncr(inLen);
			}

			// Polyphony
			int polyphony = 1 << polyphonyMode;
			if (part.polyphony() != polyphony)
				part.set_polyphony(polyphony);
			// Model
			if (easterEgg)
				string_synth.set_fx((rings::FxType) resonatorModel);
			else
				part.set_model(resonatorModel);

			// Patch
			rings::Patch patch;
			float structure = params[STRUCTURE_PARAM].getValue() + 3.3 * dsp::quadraticBipolar(params[STRUCTURE_MOD_PARAM].getValue()) * inputs[STRUCTURE_MOD_INPUT].getVoltage() / 5.0;
			patch.structure = clamp(structure, 0.0f, 0.9995f);
			patch.brightness = clamp(params[BRIGHTNESS_PARAM].getValue() + 3.3 * dsp::quadraticBipolar(params[BRIGHTNESS_MOD_PARAM].getValue()) * inputs[BRIGHTNESS_MOD_INPUT].getVoltage() / 5.0, 0.0f, 1.0f);
			patch.damping = clamp(params[DAMPING_PARAM].getValue() + 3.3 * dsp::quadraticBipolar(params[DAMPING_MOD_PARAM].getValue()) * inputs[DAMPING_MOD_INPUT].getVoltage() / 5.0, 0.0f, 0.9995f);
			patch.position = clamp(params[POSITION_PARAM].getValue() + 3.3 * dsp::quadraticBipolar(params[POSITION_MOD_PARAM].getValue()) * inputs[POSITION_MOD_INPUT].getVoltage() / 5.0, 0.0f, 0.9995f);

			// Performance
			rings::PerformanceState performance_state;
			performance_state.note = 12.0 * inputs[PITCH_INPUT].getNormalVoltage(1 / 12.0);
			float transpose = params[FREQUENCY_PARAM].getValue();
			// Quantize transpose if pitch input is connected
			if (inputs[PITCH_INPUT].isConnected()) {
				transpose = roundf(transpose);
			}
			performance_state.tonic = 12.0 + clamp(transpose, 0.0f, 60.0f);
			performance_state.fm = clamp(48.0 * 3.3 * dsp::quarticBipolar(params[FREQUENCY_MOD_PARAM].getValue()) * inputs[FREQUENCY_MOD_INPUT].getNormalVoltage(1.0) / 5.0, -48.0f, 48.0f);

			performance_state.internal_exciter = !inputs[IN_INPUT].isConnected();
			performance_state.internal_strum = !inputs[STRUM_INPUT].isConnected();
			performance_state.internal_note = !inputs[PITCH_INPUT].isConnected();

			// TODO
			// "Normalized to a step detector on the V/OCT input and a transient detector on the IN input."
			performance_state.strum = strum && !lastStrum;
			lastStrum = strum;
			strum = false;

			performance_state.chord = clamp((int) roundf(structure * (rings::kNumChords - 1)), 0, rings::kNumChords - 1);

			// Process audio
			float out[24];
			float aux[24];
			if (easterEgg) {
				strummer.Process(NULL, 24, &performance_state);
				string_synth.Process(performance_state, patch, in, out, aux, 24);
			}
			else {
				strummer.Process(in, 24, &performance_state);
				part.Process(performance_state, patch, in, out, aux, 24);
			}

			// Convert output buffer
			{
				dsp::Frame<2> outputFrames[24];
				for (int i = 0; i < 24; i++) {
					outputFrames[i].samples[0] = out[i];
					outputFrames[i].samples[1] = aux[i];
				}

				outputSrc.setRates(48000, args.sampleRate);
				int inLen = 24;
				int outLen = outputBuffer.capacity();
				outputSrc.process(outputFrames, &inLen, outputBuffer.endData(), &outLen);
				outputBuffer.endIncr(outLen);
			}
		}

		// Set output
		if (!outputBuffer.empty()) {
			dsp::Frame<2> outputFrame = outputBuffer.shift();
			// "Note that you need to insert a jack into each output to split the signals: when only one jack is inserted, both signals are mixed together."
			if (outputs[ODD_OUTPUT].isConnected() && outputs[EVEN_OUTPUT].isConnected()) {
				outputs[ODD_OUTPUT].setVoltage(clamp(outputFrame.samples[0], -1.0, 1.0) * 5.0);
				outputs[EVEN_OUTPUT].setVoltage(clamp(outputFrame.samples[1], -1.0, 1.0) * 5.0);
			}
			else {
				float v = clamp(outputFrame.samples[0] + outputFrame.samples[1], -1.0, 1.0) * 5.0;
				outputs[ODD_OUTPUT].setVoltage(v);
				outputs[EVEN_OUTPUT].setVoltage(v);
			}
		}
	}

	json_t* dataToJson() override {
		json_t* rootJ = json_object();

		json_object_set_new(rootJ, "polyphony", json_integer(polyphonyMode));
		json_object_set_new(rootJ, "model", json_integer((int) resonatorModel));
		json_object_set_new(rootJ, "easterEgg", json_boolean(easterEgg));

		return rootJ;
	}

	void dataFromJson(json_t* rootJ) override {
		json_t* polyphonyJ = json_object_get(rootJ, "polyphony");
		if (polyphonyJ) {
			polyphonyMode = json_integer_value(polyphonyJ);
		}

		json_t* modelJ = json_object_get(rootJ, "model");
		if (modelJ) {
			resonatorModel = (rings::ResonatorModel) json_integer_value(modelJ);
		}

		json_t* easterEggJ = json_object_get(rootJ, "easterEgg");
		if (easterEggJ) {
			easterEgg = json_boolean_value(easterEggJ);
		}
	}

	void onReset() override {
		polyphonyMode = 0;
		resonatorModel = rings::RESONATOR_MODEL_MODAL;
	}

	void onRandomize() override {
		polyphonyMode = random::u32() % 3;
		resonatorModel = (rings::ResonatorModel)(random::u32() % 3);
	}
};


struct RingsWidget : ModuleWidget {
	RingsWidget(Rings* module) {
		setModule(module);
		setPanel(Svg::load(asset::plugin(pluginInstance, "res/Rings.svg")));

		addChild(createWidget<ScrewSilver>(Vec(15, 0)));
		addChild(createWidget<ScrewSilver>(Vec(180, 0)));
		addChild(createWidget<ScrewSilver>(Vec(15, 365)));
		addChild(createWidget<ScrewSilver>(Vec(180, 365)));

		addParam(createParam<TL1105>(Vec(14, 40), module, Rings::POLYPHONY_PARAM));
		addParam(createParam<TL1105>(Vec(179, 40), module, Rings::RESONATOR_PARAM));

		addParam(createParam<Rogan3PSWhite>(Vec(29, 72), module, Rings::FREQUENCY_PARAM));
		addParam(createParam<Rogan3PSWhite>(Vec(126, 72), module, Rings::STRUCTURE_PARAM));

		addParam(createParam<Rogan1PSWhite>(Vec(13, 158), module, Rings::BRIGHTNESS_PARAM));
		addParam(createParam<Rogan1PSWhite>(Vec(83, 158), module, Rings::DAMPING_PARAM));
		addParam(createParam<Rogan1PSWhite>(Vec(154, 158), module, Rings::POSITION_PARAM));

		addParam(createParam<Trimpot>(Vec(19, 229), module, Rings::BRIGHTNESS_MOD_PARAM));
		addParam(createParam<Trimpot>(Vec(57, 229), module, Rings::FREQUENCY_MOD_PARAM));
		addParam(createParam<Trimpot>(Vec(96, 229), module, Rings::DAMPING_MOD_PARAM));
		addParam(createParam<Trimpot>(Vec(134, 229), module, Rings::STRUCTURE_MOD_PARAM));
		addParam(createParam<Trimpot>(Vec(173, 229), module, Rings::POSITION_MOD_PARAM));

		addInput(createInput<PJ301MPort>(Vec(15, 273), module, Rings::BRIGHTNESS_MOD_INPUT));
		addInput(createInput<PJ301MPort>(Vec(54, 273), module, Rings::FREQUENCY_MOD_INPUT));
		addInput(createInput<PJ301MPort>(Vec(92, 273), module, Rings::DAMPING_MOD_INPUT));
		addInput(createInput<PJ301MPort>(Vec(131, 273), module, Rings::STRUCTURE_MOD_INPUT));
		addInput(createInput<PJ301MPort>(Vec(169, 273), module, Rings::POSITION_MOD_INPUT));

		addInput(createInput<PJ301MPort>(Vec(15, 316), module, Rings::STRUM_INPUT));
		addInput(createInput<PJ301MPort>(Vec(54, 316), module, Rings::PITCH_INPUT));
		addInput(createInput<PJ301MPort>(Vec(92, 316), module, Rings::IN_INPUT));
		addOutput(createOutput<PJ301MPort>(Vec(131, 316), module, Rings::ODD_OUTPUT));
		addOutput(createOutput<PJ301MPort>(Vec(169, 316), module, Rings::EVEN_OUTPUT));

		addChild(createLight<MediumLight<GreenRedLight>>(Vec(37, 43), module, Rings::POLYPHONY_GREEN_LIGHT));
		addChild(createLight<MediumLight<GreenRedLight>>(Vec(162, 43), module, Rings::RESONATOR_GREEN_LIGHT));
	}

	void appendContextMenu(Menu* menu) override {
		Rings* module = dynamic_cast<Rings*>(this->module);
		assert(module);

		menu->addChild(new MenuSeparator);

		menu->addChild(createMenuLabel("Resonator"));

		static const std::vector<std::string> modelLabels = {
			"Modal resonator",
			"Sympathetic strings",
			"Modulated/inharmonic string",
			"FM voice",
			"Quantized sympathetic strings",
			"Reverb string",
		};
		for (int i = 0; i < 6; i++) {
			menu->addChild(createCheckMenuItem(modelLabels[i], "",
				[=]() {return module->resonatorModel == i;},
				[=]() {module->resonatorModel = (rings::ResonatorModel) i;}
			));
		}

		menu->addChild(new MenuSeparator);

		menu->addChild(createBoolMenuItem("Disastrous Peace", "",
			[=]() {return module->easterEgg;},
			[=](bool val) {module->easterEgg = val;}
		));
	}
};


Model* modelRings = createModel<Rings, RingsWidget>("Rings");
