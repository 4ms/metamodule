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
		constexpr auto NumParams = Defs::NumKnobs + Defs::NumSwitches;
		// Calculate number of LED elements (we only support LEDs that are in buttons)
		constexpr auto NumRGBLEDButtons = std::count_if(Defs::Switches.begin(), Defs::Switches.end(), [](auto &sw) {
			return sw.switch_type == SwitchDef::MomentaryButton;
		});
		constexpr auto NumMonoLEDButtons = std::count_if(Defs::Switches.begin(), Defs::Switches.end(), [](auto &sw) {
			return sw.switch_type == SwitchDef::LatchingButton;
		});
		constexpr auto NumLEDElements = NumRGBLEDButtons * 3 + NumMonoLEDButtons;
		configComm(NumParams, Defs::NumInJacks, Defs::NumOutJacks, NumLEDElements);

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

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, Defs::svg_filename.data())));

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

		int light_id = 0;
		for (auto sw : Defs::Switches) {
			auto param_id = sw.id + Defs::NumKnobs;
			auto pos = mm2px({sw.x_mm, sw.y_mm});

			if (sw.switch_type == SwitchDef::LatchingButton) {
				// These use a single white LED
				addParam(createParamCentered<LatchingSwitch<LEDBezel>>(pos, module, param_id));
				addChild(createLightCentered<LEDBezelLight<WhiteLight>>(pos, module, light_id));
				light_id++;

			} else if (sw.switch_type == SwitchDef::MomentaryButton) {
				// These use an RGB LED (3 elements)
				addParam(createParamCentered<MomentarySwitch<LEDBezel>>(pos, module, param_id));
				addChild(createLightCentered<LEDBezelLight<RedGreenBlueLight>>(pos, module, light_id));
				light_id += 3;

			} else if (sw.switch_type == SwitchDef::Toggle2pos) {
				addParam(createParamCentered<NKK>(pos, module, param_id));

			} else if (sw.switch_type == SwitchDef::Toggle3pos) {
				addParam(createParamCentered<NKK>(pos, module, param_id));
			}
		}
	}
};

Model *modelEnOsc = createModel<EnOscModule, EnOscWidget>(EnOscInfo::slug.data());
