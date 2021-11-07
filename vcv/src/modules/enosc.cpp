#include "CommModule.h"
#include "CommWidget.h"
#include "CoreModules/info/enosc_info.hh"
#include "CoreModules/moduleTypes.h"
#include "MappableJack.hh"
#include "math.hh"

struct EnOscModule : CommModule {
	using Defs = EnOscInfo;

	EnOscModule()
	{
		configComm(Defs::NumKnobs + Defs::NumSwitches, Defs::NumInJacks, Defs::NumOutJacks, Defs::NumSwitches);
		core = ModuleFactory::create(Defs::slug);
		selfID.typeID = Defs::slug;

		for (auto knob : Defs::Knobs) {
			configParam(knob.id, 0.f, 1.f, knob.default_val, knob.long_name.data());
		}
		for (auto sw : Defs::Switches) {
			float max = 1.f;
			if (sw.switch_type == SwitchDef::Toggle3pos)
				max = 2.f;
			configParam(Defs::NumKnobs + sw.id, 0.f, max, 0.f, sw.long_name.data());
		}
		for (auto input : Defs::InJacks) {
			inputJacks[input.id]->scale = [](float volts) { return volts / 5.0f; };
		}
		for (auto output : Defs::OutJacks) {
			outputJacks[output.id]->scale = [](float f) { return f * 5.0f; }; //=>volts
		}
	}
};

struct EnOscWidget : CommModuleWidget {
	using Defs = EnOscInfo;

	CommModule *mainModule;

	EnOscWidget(CommModule *module)
	{
		setModule(static_cast<Module *>(module));
		mainModule = module;

		// std::string svg_name{Defs::svg_filename}; // clone it because asset::plugin requires a string
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/16hptemplate.svg")));

		for (auto knob : Defs::Knobs) {
			switch (knob.knob_style) {
				case KnobDef::Small:
					addParam(createParamCentered<Trimpot>(mm2px({knob.x_mm, knob.y_mm}), module, knob.id));
					break;
				case KnobDef::Medium:
					addParam(createParamCentered<Davies1900hBlackKnob>(mm2px({knob.x_mm, knob.y_mm}), module, knob.id));
					break;
				case KnobDef::Large:
					addParam(
						createParamCentered<Davies1900hLargeBlackKnob>(mm2px({knob.x_mm, knob.y_mm}), module, knob.id));
					break;
			}
		}

		for (auto jack : Defs::InJacks) {
			addInput(
				createInputCentered<MappableInputJack<PJ301MPort>>(mm2px({jack.x_mm, jack.y_mm}), module, jack.id));
		}

		for (auto jack : Defs::OutJacks) {
			addOutput(
				createOutputCentered<MappableOutputJack<PJ301MPort>>(mm2px({jack.x_mm, jack.y_mm}), module, jack.id));
		}

		for (auto sw : Defs::Switches) {
			auto param_id = sw.id + Defs::NumKnobs;
			auto light_id = sw.id;

			if (sw.switch_type == SwitchDef::LatchingButton) {
				addParam(createParamCentered<LatchingSwitch<LEDBezel>>(mm2px({sw.x_mm, sw.y_mm}), module, param_id));
				addChild(
					createLight<LEDBezelLight<WhiteLight>>(mm2px({sw.x_mm - 3.0f, sw.y_mm - 3.0f}), module, light_id));
			} else if (sw.switch_type == SwitchDef::MomentaryButton) {
				addParam(createParamCentered<MomentarySwitch<LEDBezel>>(mm2px({sw.x_mm, sw.y_mm}), module, param_id));
				addChild(
					createLight<LEDBezelLight<WhiteLight>>(mm2px({sw.x_mm - 3.0f, sw.y_mm - 3.0f}), module, light_id));
				// } else if (sw.switch_type == SwitchDef::Toggle2pos) {
				// 	addParam(createParamCentered<NKK>(mm2px({sw.x_mm, sw.y_mm}), module, param_id));
				// } else if (sw.switch_type == SwitchDef::Toggle3pos) {
				// 	addParam(createParamCentered<NKK>(mm2px({sw.x_mm, sw.y_mm}), module, param_id));
			}
		}

		addModuleTitle(Defs::slug.data());
	}
};

Model *modelEnOsc = createModel<EnOscModule, EnOscWidget>(EnOscInfo::slug.data());
