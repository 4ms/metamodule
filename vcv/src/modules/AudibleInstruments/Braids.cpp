#include "AudibleInstruments/BraidsCore.hh"
#include "plugin.hh"

using namespace rack;

struct Braids : BraidsCore {

	Braids() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS);
		configParam(SHAPE_PARAM, 0.0, 1.0, 0.0, "Model", "", 0.0, braids::MACRO_OSC_SHAPE_LAST_ACCESSIBLE_FROM_META);
		configParam(FINE_PARAM, -1.0, 1.0, 0.0, "Fine frequency", " semitones");
		configParam(COARSE_PARAM, -5.0, 3.0, -1.0, "Coarse frequency", " semitones", 0.f, 12.f, 12.f);
		configParam(FM_PARAM, -1.0, 1.0, 0.0, "FM");
		configParam(TIMBRE_PARAM, 0.0, 1.0, 0.5, "Timbre", "%", 0.f, 100.f);
		configParam(MODULATION_PARAM, -1.0, 1.0, 0.0, "Modulation");
		configParam(COLOR_PARAM, 0.0, 1.0, 0.5, "Color", "%", 0.f, 100.f);
		configInput(TRIG_INPUT, "Trigger");
		configInput(PITCH_INPUT, "Pitch (1V/oct)");
		configInput(FM_INPUT, "FM");
		configInput(TIMBRE_INPUT, "Timbre");
		configInput(COLOR_INPUT, "Color");
		configOutput(OUT_OUTPUT, "Audio");
	}

	json_t *dataToJson() override {
		json_t *rootJ = json_object();
		json_t *settingsJ = json_array();
		uint8_t *settingsArray = &settings.shape;
		for (int i = 0; i < 20; i++) {
			json_t *settingJ = json_integer(settingsArray[i]);
			json_array_insert_new(settingsJ, i, settingJ);
		}
		json_object_set_new(rootJ, "settings", settingsJ);

		json_t *lowCpuJ = json_boolean(lowCpu);
		json_object_set_new(rootJ, "lowCpu", lowCpuJ);

		return rootJ;
	}

	void dataFromJson(json_t *rootJ) override {
		json_t *settingsJ = json_object_get(rootJ, "settings");
		if (settingsJ) {
			uint8_t *settingsArray = &settings.shape;
			for (int i = 0; i < 20; i++) {
				json_t *settingJ = json_array_get(settingsJ, i);
				if (settingJ)
					settingsArray[i] = json_integer_value(settingJ);
			}
		}

		json_t *lowCpuJ = json_object_get(rootJ, "lowCpu");
		if (lowCpuJ) {
			lowCpu = json_boolean_value(lowCpuJ);
		}
	}

	int getShapeParam() {
		return std::round(params[SHAPE_PARAM].getValue() * braids::MACRO_OSC_SHAPE_LAST_ACCESSIBLE_FROM_META);
	}
	void setShapeParam(int shape) {
		params[SHAPE_PARAM].setValue(shape / (float)braids::MACRO_OSC_SHAPE_LAST_ACCESSIBLE_FROM_META);
	}
};

struct ShapeInfo {
	std::string code;
	std::string label;
};

static const std::vector<ShapeInfo> SHAPE_INFOS = {
	{"CSAW", "Quirky sawtooth"},
	{"/\\-_", "Triangle to saw"},
	{"//-_", "Sawtooth wave with dephasing"},
	{"FOLD", "Wavefolded sine/triangle"},
	{"uuuu", "Buzz"},
	{"SUB-", "Square sub"},
	{"SUB/", "Saw sub"},
	{"SYN-", "Square sync"},
	{"SYN/", "Saw sync"},
	{"//x3", "Triple saw"},
	{"-_x3", "Triple square"},
	{"/\\x3", "Triple triangle"},
	{"SIx3", "Triple sine"},
	{"RING", "Triple ring mod"},
	{"////", "Saw swarm"},
	{"//uu", "Saw comb"},
	{"TOY*", "Circuit-bent toy"},
	{"ZLPF", "Low-pass filtered waveform"},
	{"ZPKF", "Peak filtered waveform"},
	{"ZBPF", "Band-pass filtered waveform"},
	{"ZHPF", "High-pass filtered waveform"},
	{"VOSM", "VOSIM formant"},
	{"VOWL", "Speech synthesis"},
	{"VFOF", "FOF speech synthesis"},
	{"HARM", "12 sine harmonics"},
	{"FM  ", "2-operator phase-modulation"},
	{"FBFM", "2-operator phase-modulation with feedback"},
	{"WTFM", "2-operator phase-modulation with chaotic feedback"},
	{"PLUK", "Plucked string"},
	{"BOWD", "Bowed string"},
	{"BLOW", "Blown reed"},
	{"FLUT", "Flute"},
	{"BELL", "Bell"},
	{"DRUM", "Drum"},
	{"KICK", "Kick drum circuit simulation"},
	{"CYMB", "Cymbal"},
	{"SNAR", "Snare"},
	{"WTBL", "Wavetable"},
	{"WMAP", "2D wavetable"},
	{"WLIN", "1D wavetable"},
	{"WTx4", "4-voice paraphonic 1D wavetable"},
	{"NOIS", "Filtered noise"},
	{"TWNQ", "Twin peaks noise"},
	{"CLKN", "Clocked noise"},
	{"CLOU", "Granular cloud"},
	{"PRTC", "Particle noise"},
	{"QPSK", "Digital modulation"},
};

struct BraidsDisplay : rack::TransparentWidget {
	Braids *module;

	void draw(const DrawArgs &args) override {
		// Background
		NVGcolor backgroundColor = nvgRGB(0x38, 0x38, 0x38);
		NVGcolor borderColor = nvgRGB(0x10, 0x10, 0x10);
		nvgBeginPath(args.vg);
		nvgRoundedRect(args.vg, 0.0, 0.0, box.size.x, box.size.y, 5.0);
		nvgFillColor(args.vg, backgroundColor);
		nvgFill(args.vg);
		nvgStrokeWidth(args.vg, 1.0);
		nvgStrokeColor(args.vg, borderColor);
		nvgStroke(args.vg);

		Widget::draw(args);
	}

	void drawLayer(const DrawArgs &args, int layer) override {
		if (layer == 1) {
			// Text
			int shape = module ? module->settings.shape : 0;
			std::shared_ptr<Font> font =
				APP->window->loadFont(asset::plugin(pluginInstance, "res/hdad-segment14-1.002/Segment14.ttf"));
			if (font) {
				nvgFontSize(args.vg, 38);
				nvgFontFaceId(args.vg, font->handle);
				nvgTextLetterSpacing(args.vg, 2.5);

				Vec textPos = Vec(9, 48);
				NVGcolor textColor = nvgRGB(0xaf, 0xd2, 0x2c);
				nvgFillColor(args.vg, nvgTransRGBA(textColor, 16));
				// Background of all segments
				nvgText(args.vg, textPos.x, textPos.y, "~~~~", NULL);
				nvgFillColor(args.vg, textColor);
				nvgText(args.vg, textPos.x, textPos.y, SHAPE_INFOS[shape].code.c_str(), NULL);
			}
		}
		Widget::drawLayer(args, layer);
	}
};

struct BraidsWidget : ModuleWidget {
	BraidsWidget(Braids *module) {
		setModule(module);
		setPanel(Svg::load(asset::plugin(pluginInstance, "res/modules/AudibleInstruments/Braids.svg")));

		addChild(createWidget<ScrewSilver>(Vec(15, 0)));
		addChild(createWidget<ScrewSilver>(Vec(210, 0)));
		addChild(createWidget<ScrewSilver>(Vec(15, 365)));
		addChild(createWidget<ScrewSilver>(Vec(210, 365)));

		addParam(createParam<Rogan2SGray>(Vec(176, 59), module, SHAPE_PARAM));

		addParam(createParam<Rogan2PSWhite>(Vec(19, 138), module, FINE_PARAM));
		addParam(createParam<Rogan2PSWhite>(Vec(97, 138), module, COARSE_PARAM));
		addParam(createParam<Rogan2PSWhite>(Vec(176, 138), module, FM_PARAM));

		addParam(createParam<Rogan2PSGreen>(Vec(19, 217), module, TIMBRE_PARAM));
		addParam(createParam<Rogan2PSGreen>(Vec(97, 217), module, MODULATION_PARAM));
		addParam(createParam<Rogan2PSRed>(Vec(176, 217), module, COLOR_PARAM));

		addInput(createInput<PJ301MPort>(Vec(10, 316), module, TRIG_INPUT));
		addInput(createInput<PJ301MPort>(Vec(47, 316), module, PITCH_INPUT));
		addInput(createInput<PJ301MPort>(Vec(84, 316), module, FM_INPUT));
		addInput(createInput<PJ301MPort>(Vec(122, 316), module, TIMBRE_INPUT));
		addInput(createInput<PJ301MPort>(Vec(160, 316), module, COLOR_INPUT));
		addOutput(createOutput<PJ301MPort>(Vec(205, 316), module, OUT_OUTPUT));

		BraidsDisplay *display = new BraidsDisplay();
		display->box.pos = Vec(14, 53);
		display->box.size = Vec(148, 56);
		display->module = module;
		addChild(display);
	}

	void appendContextMenu(Menu *menu) override {
		Braids *module = dynamic_cast<Braids *>(this->module);

		menu->addChild(new MenuSeparator);

		std::vector<std::string> shapeLabels;
		for (const ShapeInfo &s : SHAPE_INFOS) {
			shapeLabels.push_back(s.code + ": " + s.label);
		}
		menu->addChild(createIndexSubmenuItem(
			"Model", shapeLabels, [=]() { return module->getShapeParam(); }, [=](int i) { module->setShapeParam(i); }));

		menu->addChild(createBoolPtrMenuItem("META: FM CV selects model", "", &module->settings.meta_modulation));

		menu->addChild(createBoolMenuItem(
			"DRFT: Pitch drift",
			"",
			[=]() { return module->settings.vco_drift; },
			[=](bool val) { module->settings.vco_drift = val ? 4 : 0; }));

		menu->addChild(createBoolMenuItem(
			"SIGN: Waveform imperfections",
			"",
			[=]() { return module->settings.signature; },
			[=](bool val) { module->settings.signature = val ? 4 : 0; }));

		menu->addChild(createBoolPtrMenuItem("Low CPU (disable resampling)", "", &module->lowCpu));
	}
};

Model *modelBraids = createModel<Braids, BraidsWidget>("Braids");
