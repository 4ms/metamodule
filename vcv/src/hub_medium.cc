#include "CoreModules/meta-module-hub/panel_medium_defs.hh"
#include "CoreModules/moduleFactory.hh"
#include "comm_data.hh"
#include "comm_module.hh"
#include "comm_widget.hh"
#include "hub_base.hh"
#include "hub_jack.hh"
#include "local_path.hh"
#include "patch_writer.hh"
#include "plugin.hh"

// Note: in v2, first the module is constructed, then dataFromJson is called, then the Widget is constructed
struct HubMediumMappings {
	constexpr static unsigned NumMidiSrcs = 2;
	constexpr static unsigned NumMappings = PanelDef::NumKnobs + NumMidiSrcs;
	constexpr static std::array<LabelButtonID::Types, NumMappings> mapping_srcs{
		LabelButtonID::Types::Knob,
		LabelButtonID::Types::Knob,
		LabelButtonID::Types::Knob,
		LabelButtonID::Types::Knob,
		LabelButtonID::Types::Knob,
		LabelButtonID::Types::Knob,
		LabelButtonID::Types::Knob,
		LabelButtonID::Types::Knob,
		LabelButtonID::Types::Knob,
		LabelButtonID::Types::Knob,
		LabelButtonID::Types::Knob,
		LabelButtonID::Types::Knob,
		LabelButtonID::Types::MidiNote,
		LabelButtonID::Types::MidiGate,
	};
};

struct HubMedium : MetaModuleHubBase<HubMediumMappings> {

	enum ParamIds { ENUMS(KNOBS, PanelDef::NumPot), MIDI_MONO_NOTE, MIDI_MONO_GATE, WRITE_PATCH, NUM_PARAMS };
	enum InputIds { NUM_INPUTS = PanelDef::NumInJacks };
	enum OutputIds { NUM_OUTPUTS = PanelDef::NumOutJacks };
	enum LightIds { NUM_LIGHTS = 0 };

	HubMedium()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		// configParam(int paramId, float minValue, float maxValue, float defaultValue, std::string label = "",
		// std::string unit = "", float displayBase = 0.f, float displayMultiplier = 1.f, float displayOffset = 0.f);
		configParam(0, 0.f, 1.f, 0.f, "Knob A");
		configParam(1, 0.f, 1.f, 0.f, "Knob B");
		configParam(2, 0.f, 1.f, 0.f, "Knob C");
		configParam(3, 0.f, 1.f, 0.f, "Knob D");
		configParam(4, 0.f, 1.f, 0.f, "Knob E");
		configParam(5, 0.f, 1.f, 0.f, "Knob F");
		configParam(6, 0.f, 1.f, 0.f, "Knob U");
		configParam(7, 0.f, 1.f, 0.f, "Knob V");
		configParam(8, 0.f, 1.f, 0.f, "Knob W");
		configParam(9, 0.f, 1.f, 0.f, "Knob X");
		configParam(10, 0.f, 1.f, 0.f, "Knob Y");
		configParam(11, 0.f, 1.f, 0.f, "Knob Z");

		configParam(MIDI_MONO_NOTE, 0.f, 1.f, 0.f, "MidiNote");
		configParam(MIDI_MONO_GATE, 0.f, 1.f, 0.f, "MidiGate");

		configParam(WRITE_PATCH, 0.f, 1.f, 0.f, "Export patch file");
		selfID.slug = "PanelMedium";
	}

	~HubMedium() = default;

	void process(const ProcessArgs &args) override
	{
		processPatchButton(params[WRITE_PATCH].getValue());
		processKnobMaps();
		processCreatePatchFile();
	}
};

struct HubMediumWidget : MetaModuleHubBaseWidget<HubMediumMappings> {
	LedDisplayTextField *patchName;
	LedDisplayTextField *patchDesc;

	Vec fixDPI(Vec v) { return v.mult(75.f / 72.f); }
	Vec fixDPIKnob(Vec v) { return v.mult(75.f / 72.f).plus({0.6f, 0.2f}); }

	HubMediumWidget(HubMedium *module)
	{
		setModule(module);
		hubModule = module;

		if (hubModule != nullptr) {
			hubModule->updateDisplay = [this] { this->valueLabel->text = this->hubModule->labelText; };
			hubModule->updatePatchName = [this] {
				this->hubModule->patchNameText = this->patchName->text;
				this->hubModule->patchDescText = this->patchDesc->text;
			};
		}

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/meta-module-medium-p8.svg")));
		addChild(createWidget<ScrewBlack>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewBlack>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewBlack>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewBlack>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		valueLabel = createWidget<Label>(mm2px(Vec(0, 4)));
		valueLabel->color = rack::color::BLACK;
		valueLabel->text = "";
		valueLabel->fontSize = 10;
		addChild(valueLabel);

		patchName = createWidget<MetaModuleTextBox>(mm2px(Vec(37, 12.7)));
		if (hubModule != nullptr && hubModule->patchNameText.length() > 0)
			patchName->text = this->hubModule->patchNameText;
		else
			patchName->text = "Enter Patch Name";
		patchName->color = rack::color::BLACK;
		patchName->box.size = {mm2px(Vec(57.7f, 10.0f))};
		patchName->cursor = 0;
		addChild(patchName);

		patchDesc = createWidget<MetaModuleTextBox>(mm2px(Vec(37, 24.7)));
		if (hubModule != nullptr && hubModule->patchDescText.length() > 0)
			patchDesc->text = this->hubModule->patchDescText;
		else
			patchDesc->text = "Patch Description";
		patchDesc->color = rack::color::BLACK;
		patchDesc->box.size = {mm2px(Vec(57.7f, 31.3f))};
		patchDesc->cursor = 0;
		addChild(patchDesc);

		addParam(createParamCentered<BefacoPush>(fixDPIKnob({298.90, 49.35}), module, HubMedium::WRITE_PATCH));

		addLabeledKnobPx<RoundBlackKnob>("", 0, fixDPIKnob({33.35, 213.10}));		 // A
		addLabeledKnobPx<RoundBlackKnob>("", 1, fixDPIKnob({92.87, 201.66}));		 // B
		addLabeledKnobPx<RoundBlackKnob>("", 2, fixDPIKnob({153.76, 213.10}));		 // C
		addLabeledKnobPx<RoundBlackKnob>("", 3, fixDPIKnob({218.70, 213.10}));		 // D
		addLabeledKnobPx<RoundBlackKnob>("", 4, fixDPIKnob({279.38, 201.66}));		 // E
		addLabeledKnobPx<RoundBlackKnob>("", 5, fixDPIKnob({340.00, 213.10}));		 // F
		addLabeledKnobPx<RoundSmallBlackKnob>("", 6, fixDPIKnob({27.06, 73.20}));	 // u
		addLabeledKnobPx<RoundSmallBlackKnob>("", 7, fixDPIKnob({61.47, 115.71}));	 // v
		addLabeledKnobPx<RoundSmallBlackKnob>("", 8, fixDPIKnob({27.06, 157.79}));	 // w
		addLabeledKnobPx<RoundSmallBlackKnob>("", 9, fixDPIKnob({345.74, 91.39}));	 // x
		addLabeledKnobPx<RoundSmallBlackKnob>("", 10, fixDPIKnob({302.49, 123.24})); // y
		addLabeledKnobPx<RoundSmallBlackKnob>("", 11, fixDPIKnob({345.77, 157.00})); // z

		addMidiValueMapPt("MidiNote", HubMedium::MIDI_MONO_NOTE, fixDPIKnob({60, 40}), LabelButtonID::Types::MidiNote);
		addMidiValueMapPt("MidiGate", HubMedium::MIDI_MONO_GATE, fixDPIKnob({60, 70}), LabelButtonID::Types::MidiGate);

		addLabeledJackPx<PJ301MPort>("", 0, fixDPI({36.34, 324.15}), JackDir::Input);
		addLabeledJackPx<PJ301MPort>("", 1, fixDPI({79.86, 324.15}), JackDir::Input);
		addLabeledJackPx<PJ301MPort>("", 2, fixDPI({122.6, 324.18}), JackDir::Input);
		addLabeledJackPx<PJ301MPort>("", 3, fixDPI({166.12, 324.18}), JackDir::Input);
		addLabeledJackPx<PJ301MPort>("", 4, fixDPI({109.61, 282.75}), JackDir::Input);
		addLabeledJackPx<PJ301MPort>("", 5, fixDPI({153.13, 282.75}), JackDir::Input);
		addLabeledJackPx<PJ301MPort>("", 6, fixDPI({22.9, 274.7}), JackDir::Input);
		addLabeledJackPx<PJ301MPort>("", 7, fixDPI({66.42, 274.7}), JackDir::Input);

		addLabeledJackPx<PJ301MPort>("", 0, fixDPI({209.28, 324.18}), JackDir::Output);
		addLabeledJackPx<PJ301MPort>("", 1, fixDPI({252.8, 324.18}), JackDir::Output);
		addLabeledJackPx<PJ301MPort>("", 2, fixDPI({295.21, 324.2}), JackDir::Output);
		addLabeledJackPx<PJ301MPort>("", 3, fixDPI({338.73, 324.2}), JackDir::Output);
		addLabeledJackPx<PJ301MPort>("", 4, fixDPI({222.16, 282.79}), JackDir::Output);
		addLabeledJackPx<PJ301MPort>("", 5, fixDPI({265.68, 282.79}), JackDir::Output);
		addLabeledJackPx<PJ301MPort>("", 6, fixDPI({308.9, 282.15}), JackDir::Output);
		addLabeledJackPx<PJ301MPort>("", 7, fixDPI({352.42, 282.15}), JackDir::Output);
	}
};

Model *modelHubMedium = createModel<HubMedium, HubMediumWidget>("PanelMedium");
