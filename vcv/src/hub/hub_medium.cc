#include "CoreModules/elements/element_counter.hh"
#include "CoreModules/hub/HubMedium_info.hh"
#include "CoreModules/moduleFactory.hh"
#include "comm/comm_module.hh"
#include "hub/hub_elements.hh"
#include "hub_module_widget.hh"
#include "mapping/Mapping.h"
#include "mapping/patch_writer.hh"
#include "widgets/4ms/4ms_widgets.hh"
#include "widgets/vcv_module_creator.hh"
#include "widgets/vcv_widget_creator.hh"

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
	using INFO = MetaModule::HubMediumInfo;

	HubMedium()
		: MetaModuleHubBase{HubMediumMappings::mapping_srcs} {

		// Register with VCV the number of elements of each type
		auto cnt = ElementCount::count<INFO>();
		config(cnt.num_params, cnt.num_inputs, cnt.num_outputs, cnt.num_lights);

		// Configure elements with VCV
		MetaModule::VCVModuleParamCreator<INFO> creator{this};
		for (auto &element : INFO::Elements) {
			std::visit([&creator](auto &el) { creator.config_element(el); }, element);
		}
	}

	void process(const ProcessArgs &args) override {
		processPatchButton(params[save_patch_button_idx].getValue());
		processMaps();
	}

	constexpr static auto indices = ElementCount::get_indices<INFO>();

	constexpr static auto element_index(INFO::Elem el) {
		return static_cast<std::underlying_type_t<INFO::Elem>>(el);
	}

	constexpr static ElementCount::Indices index(INFO::Elem el) {
		auto element_idx = element_index(el);
		return indices[element_idx];
	}

	unsigned save_patch_button_idx = index(INFO::Elem::SavepatchButton).param_idx;
};

struct HubMediumWidget : MetaModuleHubWidget {
	using INFO = MetaModule::HubMediumInfo;

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
			hubModule->updateDisplay = [this] {
				this->statusText->text = this->hubModule->labelText;
			};
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

		// create widgets from all elements
		MetaModule::HubWidgetCreator<INFO> creator(this, module);
		for (auto &element : INFO::Elements) {
			std::visit([&creator](auto &el) { creator.create(el); }, element);
		}

		// auto &midinote = MetaModuleInfo::Switches[MetaModuleInfo::SwitchNote];
		// addMidiValueMapSrc("MidiNote",
		// 				   HubMedium::MIDI_MONO_NOTE,
		// 				   rack::mm2px({midinote.x_mm, midinote.y_mm}),
		// 				   MappableObj::Type::MidiNote);

		// auto &midigate = MetaModuleInfo::Switches[MetaModuleInfo::SwitchGate];
		// addMidiValueMapSrc("MidiGate",
		// 				   HubMedium::MIDI_MONO_GATE,
		// 				   rack::mm2px({midigate.x_mm, midigate.y_mm}),
		// 				   MappableObj::Type::MidiGate);

		// auto &midicc = MetaModuleInfo::Switches[MetaModuleInfo::SwitchCc];
		// addMidiValueMapPt("MidiCC",
		// 				  HubMedium::MIDI_CC,
		// 				  rack::mm2px({midigate.x_mm, midigate.y_mm}),
		// 				  LabelButtonID::Types::MidiCC);
	}

	void onHover(const HoverEvent &e) override {
		if (hubModule->should_write_patch()) {
			hubModule->writePatchFile();
		}
	}
};

rack::Model *modelHubMedium = rack::createModel<HubMedium, HubMediumWidget>("HubMedium");
