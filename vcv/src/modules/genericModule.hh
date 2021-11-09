#pragma once
#include "CommModule.h"
#include "CommWidget.h"
#include "CoreModules/info/module_info_base.hh"
#include "CoreModules/moduleTypes.h"
#include "MappableJack.hh"
#include "math.hh"
#include "util/base_concepts.hh"

template<Derived<ModuleInfoBase> Defs>
struct GenericModule : CommModule {

	GenericModule()
	{
		constexpr auto NumParams = Defs::NumKnobs + Defs::NumSwitches;

		// Calculate number of LED elements
		constexpr auto NumRGBLEDButtons = std::count_if(Defs::Switches.begin(), Defs::Switches.end(), [](auto &sw) {
			return sw.switch_type == SwitchDef::MomentaryButton;
		});
		constexpr auto NumMonoLEDButtons = std::count_if(Defs::Switches.begin(), Defs::Switches.end(), [](auto &sw) {
			return sw.switch_type == SwitchDef::LatchingButton;
		});
		constexpr auto NumLEDElements = Defs::NumDiscreteLeds + NumRGBLEDButtons * 3 + NumMonoLEDButtons;
		configComm(NumParams, Defs::NumInJacks, Defs::NumOutJacks, NumLEDElements);

		core = ModuleFactory::create(Defs::slug);
		selfID.typeID = Defs::slug;

		for (auto knob : Defs::Knobs)
			configParam(knob.id, 0.f, 1.f, knob.default_val, knob.long_name.data());

		for (auto sw : Defs::Switches) {
			float max = 1.f;
			if (sw.switch_type == SwitchDef::Toggle3pos)
				max = 2.f;
			configParam(Defs::NumKnobs + sw.id, 0.f, max, 0.f, sw.long_name.data());
		}

		// TODO: let us set the in/out conversion functions somehow...
		for (auto input : Defs::InJacks)
			inputJacks[input.id]->scale = [](float volts) { return volts / 5.0f; };

		for (auto output : Defs::OutJacks)
			outputJacks[output.id]->scale = [](float f) { return f * 5.0f; }; //=>volts
	}
};

template<Derived<ModuleInfoBase> Defs>
struct GenericModuleWidget : CommModuleWidget {

	CommModule *mainModule;

	GenericModuleWidget(CommModule *module)
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
				addParam(createParamCentered<SubMiniToggle2pos>(pos, module, param_id));

			} else if (sw.switch_type == SwitchDef::Toggle3pos) {
				addParam(createParamCentered<SubMiniToggle3pos>(pos, module, param_id));
			}
		}

		for (auto led : Defs::Leds) {
			auto pos = mm2px({led.x_mm, led.y_mm});
			addChild(createLightCentered<MediumLight<RedLight>>(pos, module, light_id));
			light_id++;
		}
	}
};

// Helper function
template<typename T>
Model *createModelFromInfo()
{
	return createModel<GenericModule<T>, GenericModuleWidget<T>>(T::slug.data());
}
