#include "../comm/comm_module.hh"
#include "CoreModules/meta-module-hub/MetaModule_info.hh"
#include "CoreModules/meta-module-hub/panel_medium_defs.hh"
#include "CoreModules/moduleFactory.hh"
#include "elements/4ms_widgets.hh"
#include "hub_module_widget.hh"
#include "local_path.hh"
#include "mapping/Mapping.h"
#include "mapping/patch_writer.hh"

using namespace rack;

// Note: in v2, first the module is constructed, then dataFromJson is called, then the Widget is constructed
struct HubMediumMappings {
	constexpr static unsigned NumMidiSrcs = 2;
	constexpr static unsigned NumMappings = PanelDef::NumKnobs + NumMidiSrcs;
	static inline std::array<MappableObj::Type, NumMappings> mapping_srcs{
		MappableObj::Type::Knob,
		MappableObj::Type::Knob,
		MappableObj::Type::Knob,
		MappableObj::Type::Knob,
		MappableObj::Type::Knob,
		MappableObj::Type::Knob,
		MappableObj::Type::Knob,
		MappableObj::Type::Knob,
		MappableObj::Type::Knob,
		MappableObj::Type::Knob,
		MappableObj::Type::Knob,
		MappableObj::Type::Knob,
		MappableObj::Type::MidiNote,
		MappableObj::Type::MidiGate,
	};
};

struct HubMedium : MetaModuleHubBase {

	enum ParamIds { ENUMS(KNOBS, PanelDef::NumPot), MIDI_MONO_NOTE, MIDI_MONO_GATE, WRITE_PATCH, NUM_PARAMS };
	enum InputIds { NUM_INPUTS = PanelDef::NumUserFacingOutJacks };
	enum OutputIds { NUM_OUTPUTS = PanelDef::NumUserFacingInJacks };
	enum LightIds { NUM_LIGHTS = 0 };

	HubMedium()
		: MetaModuleHubBase{HubMediumMappings::mapping_srcs} {
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
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

		for (auto jack : MetaModuleInfo::InJacks)
			configInput((int)jack.id, std::string{jack.short_name});

		for (auto jack : MetaModuleInfo::OutJacks)
			configOutput((int)jack.id, std::string{jack.short_name});

		selfID.slug = "PanelMedium";
	}

	void process(const ProcessArgs &args) override {
		processPatchButton(params[WRITE_PATCH].getValue());
		processMaps();
		processCreatePatchFile();
	}
};

struct HubMediumWidget : MetaModuleHubWidget {
	LedDisplayTextField *patchName;
	LedDisplayTextField *patchDesc;

	Vec fixDPI(Vec v) {
		return v.mult(75.f / 72.f);
	}
	Vec fixDPIKnob(Vec v) {
		return v.mult(75.f / 72.f).plus({0.6f, 0.2f});
	}

	HubMediumWidget(HubMedium *module) {
		setModule(module);
		hubModule = module;

		if (hubModule != nullptr) {
			hubModule->updateDisplay = [this] { this->statusText->text = this->hubModule->labelText; };
			hubModule->updatePatchName = [this] {
				this->hubModule->patchNameText = this->patchName->text;
				this->hubModule->patchDescText = this->patchDesc->text;
			};
		}

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/modules/metamodule_p10-artwork.svg")));
		addChild(createWidget<ScrewBlack>(rack::math::Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewBlack>(rack::math::Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewBlack>(rack::math::Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewBlack>(
			rack::math::Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		patchName = createWidget<MetaModuleTextBox>(rack::mm2px(rack::math::Vec(36.1, 10.5)));
		if (hubModule != nullptr && hubModule->patchNameText.length() > 0)
			patchName->text = this->hubModule->patchNameText;
		else
			patchName->text = "Enter Patch Name";
		patchName->color = rack::color::BLACK;
		patchName->box.size = {rack::mm2px(rack::math::Vec(57.7f, 10.0f))};
		patchName->cursor = 0;
		addChild(patchName);

		statusText = createWidget<Label>(rack::mm2px(rack::math::Vec(34.1, 17.8)));
		statusText->color = rack::color::WHITE;
		statusText->text = "";
		statusText->fontSize = 10;
		addChild(statusText);

		patchDesc = createWidget<MetaModuleTextBox>(rack::mm2px(rack::math::Vec(36, 22.98)));
		if (hubModule != nullptr && hubModule->patchDescText.length() > 0)
			patchDesc->text = this->hubModule->patchDescText;
		else
			patchDesc->text = "Patch Description";
		patchDesc->color = rack::color::BLACK;
		patchDesc->box.size = {rack::mm2px(rack::math::Vec(57.7f, 31.3f))};
		patchDesc->cursor = 0;
		addChild(patchDesc);

		for (auto knob : MetaModuleInfo::Knobs) {
			auto ctr_pos = rack::mm2px({knob.x_mm, knob.y_mm});
			if (knob.knob_style == KnobDef::Small)
				addLabeledKnobPx<Small9mmKnob>(knob.short_name, knob.id, ctr_pos, 14.f);
			if (knob.knob_style == KnobDef::Medium)
				addLabeledKnobPx<Davies1900hBlackKnob4ms>(knob.short_name, knob.id, ctr_pos, 21.f);
		}

		for (auto jack : MetaModuleInfo::InJacks)
			addInput(createInputCentered<PJ301MPort>(rack::mm2px({jack.x_mm, jack.y_mm}), module, jack.id));

		for (auto jack : MetaModuleInfo::OutJacks)
			addOutput(createOutputCentered<PJ301MPort>(rack::mm2px({jack.x_mm, jack.y_mm}), module, jack.id));

		auto &savebut = MetaModuleInfo::Switches[MetaModuleInfo::SwitchSave];
		addParam(rack::createParamCentered<BefacoPush>(
			rack::mm2px({savebut.x_mm, savebut.y_mm}), module, HubMedium::WRITE_PATCH));

		auto &midinote = MetaModuleInfo::Switches[MetaModuleInfo::SwitchNote];
		addMidiValueMapSrc("MidiNote",
						   HubMedium::MIDI_MONO_NOTE,
						   rack::mm2px({midinote.x_mm, midinote.y_mm}),
						   MappableObj::Type::MidiNote);

		auto &midigate = MetaModuleInfo::Switches[MetaModuleInfo::SwitchGate];
		addMidiValueMapSrc("MidiGate",
						   HubMedium::MIDI_MONO_GATE,
						   rack::mm2px({midigate.x_mm, midigate.y_mm}),
						   MappableObj::Type::MidiGate);

		// auto &midicc = MetaModuleInfo::Switches[MetaModuleInfo::SwitchCc];
		// addMidiValueMapPt("MidiCC",
		// 				  HubMedium::MIDI_CC,
		// 				  rack::mm2px({midigate.x_mm, midigate.y_mm}),
		// 				  LabelButtonID::Types::MidiCC);
	}
};

rack::Model *modelHubMedium = rack::createModel<HubMedium, HubMediumWidget>("PanelMedium");
