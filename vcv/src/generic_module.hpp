#pragma once
#include "CommModule.hpp"
#include "CommWidget.hpp"
#include "CoreModules/info/module_info_base.hh"
#include "CoreModules/moduleFactory.hh"
#include "MappableJack.hpp"
#include "util/base_concepts.hh"
#include "util/math.hh"

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
			if (sw.switch_type == SwitchDef::Encoder) {
				configParam(Defs::NumKnobs + sw.id, -INFINITY, INFINITY, 0.0f, sw.long_name.data());
			} else {
				float max = 1.f;
				if (sw.switch_type == SwitchDef::Toggle3pos)
					max = 2.f;
				configParam(Defs::NumKnobs + sw.id, 0.f, max, 0.f, sw.long_name.data());
			}
		}

		// TODO: let us set the in/out conversion functions in Defs...
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
		: mainModule{module}
	{
		setModule(static_cast<Module *>(module));

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, Defs::svg_filename.data())));

		for (auto knob : Defs::Knobs) {
			auto ctr_pos = mm2px({knob.x_mm, knob.y_mm});
			switch (knob.knob_style) {
				case KnobDef::Small: {
					auto *kn = createParamCentered<Small9mmKnob>(ctr_pos, module, knob.id);
					addChild(new MappableKnobRing{*kn, 10});
					addParam(kn);
				} break;

				case KnobDef::Medium: {
					auto *kn = createParamCentered<Davies1900hBlackKnob4ms>(ctr_pos, module, knob.id);
					addChild(new MappableKnobRing{*kn, 10});
					addParam(kn);
				} break;

				case KnobDef::Large: {
					auto *kn = createParamCentered<DaviesLarge4ms>(ctr_pos, module, knob.id);
					addChild(new MappableKnobRing{*kn, 20});
					addParam(kn);
				} break;

				case KnobDef::Slider25mm: {
					if (knob.orientation == KnobDef::Vertical) {
						auto *kn =
							createParamCentered<MappableKnob<LEDLightSlider<WhiteLight>>>(ctr_pos, module, knob.id);
						addChild(new MappableSliderRing{*kn, 20, 40});
						addParam(kn);
					} else {
						auto *kn = createParamCentered<MappableKnob<LEDLightSliderHorizontal<WhiteLight>>>(
							ctr_pos, module, knob.id);
						addChild(new MappableSliderRing{*kn, 40, 20});
						addParam(kn);
					}
				} break;
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
				if (sw.orientation == SwitchDef::Vertical)
					addParam(createParamCentered<SubMiniToggle2pos>(pos, module, param_id));
				else
					addParam(createParamCentered<SubMiniToggleHoriz2pos>(pos, module, param_id));

			} else if (sw.switch_type == SwitchDef::Toggle3pos) {
				if (sw.orientation == SwitchDef::Vertical)
					addParam(createParamCentered<SubMiniToggle3pos>(pos, module, param_id));
				else
					addParam(createParamCentered<SubMiniToggleHoriz3pos>(pos, module, param_id));

			} else if (sw.switch_type == SwitchDef::Encoder) {
				// TODO: add un-lined knobs
				if (sw.encoder_knob_style == SwitchDef::Small)
					addParam(createParamCentered<Small9mmUnlinedKnob>(pos, module, param_id));
				else if (sw.encoder_knob_style == SwitchDef::Medium)
					addParam(createParamCentered<Davies1900hBlackKnobUnlined4ms>(pos, module, param_id));
			}
		}

		for (auto led : Defs::Leds) {
			auto pos = mm2px({led.x_mm, led.y_mm});
			addChild(createLightCentered<MediumLight<RedLight>>(pos, module, light_id));
			light_id++;
		}
	}

	//////////////////// Alt Params

	struct AltParamQty : Quantity {
		const AltParamDef &_alt;
		CommModule &_module;
		float _val;

		AltParamQty(CommModule &module, const AltParamDef &alt)
			: _alt{alt}
			, _module{module}
			, _val{alt.default_val}
		{}

		void setValue(float value) override
		{
			if (_alt.control_type == AltParamDef::Range::Continuous)
				_val = value;
			else
				_val = (int)(value + 0.5f);
		}

		float getValue() override { return _val; }

		float getMinValue() override { return _alt.min_val; }
		float getMaxValue() override { return _alt.max_val; }
		float getDefaultValue() override { return _alt.default_val; }

		std::string getDisplayValueString() override
		{
			if (_module.core)
				// return std::string{Defs::get_alt_param_value(_alt.id, _val)};
				return std::string{_module.core->get_alt_param_value(_alt.id, _val)};
			return "";
		}
	};

	struct AltParamSlider : ui::Slider {
		AltParamSlider(CommModule &module, const AltParamDef &alt) { quantity = new AltParamQty{module, alt}; }
		~AltParamSlider() { delete quantity; }
	};

	struct AltParamMenuItem : MenuItem {
		CommModule &module;
		const AltParamDef &_alt;

		AltParamMenuItem(CommModule &module, const AltParamDef &alt)
			: module{module}
			, _alt{alt}
		{}

		void onAction(const event::Action &e) override { std::cout << this->text << std::endl; }
	};

	void appendContextMenu(Menu *menu) override
	{
		// auto module = dynamic_cast<GenericModuleWidget *>(this->module);

		menu->addChild(new MenuEntry);
		for (auto &alt : Defs::AltParams) {
			auto *item = new AltParamMenuItem{*mainModule, alt};
			item->text = std::string{alt.short_name};
			menu->addChild(item);

			auto slider = new AltParamSlider{*mainModule, alt};
			slider->box.size.x = 100;
			menu->addChild(slider);
		}

		// ClockDivisionItem* clockDivisionItem = new ClockDivisionItem;
		// clockDivisionItem->text = "CLK/N divider";
		// clockDivisionItem->rightText = RIGHT_ARROW;
		// clockDivisionItem->module = module;
		// menu->addChild(clockDivisionItem);

		// ChannelItem* channelItem = new ChannelItem;
		// channelItem->text = "Polyphony channels";
		// channelItem->rightText = string::f("%d", module->channels) + " " + RIGHT_ARROW;
		// channelItem->module = module;
		// menu->addChild(channelItem);

		// PolyModeItem* polyModeItem = new PolyModeItem;
		// polyModeItem->text = "Polyphony mode";
		// polyModeItem->rightText = RIGHT_ARROW;
		// polyModeItem->module = module;
		// menu->addChild(polyModeItem);

		// MIDI_CVPanicItem* panicItem = new MIDI_CVPanicItem;
		// panicItem->text = "Panic";
		// panicItem->module = module;
		// menu->addChild(panicItem);
	}
};

// Helper function
template<typename T>
Model *createModelFromInfo()
{
	return createModel<GenericModule<T>, GenericModuleWidget<T>>(T::slug.data());
}
