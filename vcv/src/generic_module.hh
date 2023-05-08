#pragma once
#include "CoreModules/module_info_base.hh"
#include "CoreModules/moduleFactory.hh"
#include "comm_module.hh"
#include "comm_widget.hh"
#include "components.h"
#include "hub/mappable_jack.hh"
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
		selfID.slug = Defs::slug;

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
				// Special-case: 3pos switches have values 0, 1, 2 in VCV
				// but have values 0, 0.5, 1 in Metamodule/CoreModule
				commParams[Defs::NumKnobs + sw.id]->scaleFactor = 1.f / max;
			}
		}

		for (auto &alt : Defs::AltParams) {
			altParams.push_back({true, alt.id, alt.default_val});
		}
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
		addChild(createWidget<ScrewBlack>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewBlack>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		if (box.size.x > RACK_GRID_WIDTH * 7) // >7HP = 2 screws
		{
			addChild(createWidget<ScrewBlack>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
			addChild(
				createWidget<ScrewBlack>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		}

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
							createParamCentered<MappableKnob<FourmsLightSlider<WhiteLight>>>(ctr_pos, module, knob.id);
						addChild(new MappableSliderRing{*kn, 20, 40});
						addParam(kn);
					} else {
						auto *kn = createParamCentered<MappableKnob<FourmsLightSliderHorizontal<WhiteLight>>>(
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

		for (auto led : Defs::Leds) {
			auto pos = mm2px({led.x_mm, led.y_mm});
			addChild(createLightCentered<MediumLight<RedLight>>(pos, module, light_id));
			light_id++;
		}

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
	}

	//////////////////// Alt Params

	// TODO: make a choose-one-of-two/three button array instead of slider
	// Can use it when Range is Integer and max-min <= 3
	// Can query names with get_alt_param_value(id, min|..|max);
	struct AltParamQty : Quantity {
		const AltParamDef &_alt;
		CommModule &_module;
		float _val;

		AltParamQty(CommModule &module, const AltParamDef &alt)
			: _alt{alt}
			, _module{module}
			, _val{alt.default_val}
		{
			for (auto &ap : _module.altParams) {
				if (ap.id == _alt.id) {
					_val = ap.val;
					break;
				}
			}
		}

		void setValue(float value) override
		{
			float prev_val = _val;
			_val = std::clamp(value, _alt.min_val, _alt.max_val);
			if (_alt.control_type == AltParamDef::Range::Integer)
				_val = (int)(_val + 0.5f);

			if (prev_val == _val)
				return;

			for (auto &ap : _module.altParams) {
				if (ap.id == _alt.id) {
					ap.is_updated = true;
					ap.val = _val;
					break;
				}
			}
		}

		std::string getDisplayValueString() override
		{
			if (_module.core)
				return std::string{_module.core->get_alt_param_value(_alt.id, _val)};
			return std::to_string(_val);
		}

		float getValue() override { return _val; }
		float getMinValue() override { return _alt.min_val; }
		float getMaxValue() override { return _alt.max_val; }
		float getDefaultValue() override { return _alt.default_val; }
	};

	struct AltParamSlider : ui::Slider {
		AltParamSlider(CommModule &module, const AltParamDef &alt) { quantity = new AltParamQty{module, alt}; }
		~AltParamSlider() { delete quantity; }
	};

	void appendContextMenu(Menu *menu) override
	{
		menu->addChild(new MenuEntry);
		for (auto &alt : Defs::AltParams) {
			auto *item = new MenuItem;
			item->text = std::string{alt.short_name};
			menu->addChild(item);

			auto slider = new AltParamSlider{*mainModule, alt};
			slider->box.size.x = 100;
			menu->addChild(slider);
		}
	}
};

// Helper function
template<typename T>
Model *createModelFromInfo()
{
	return createModel<GenericModule<T>, GenericModuleWidget<T>>(T::slug.data());
}
