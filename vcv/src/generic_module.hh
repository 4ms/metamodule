// TO BE DEPRECATED: See generic_module_new.hh

#pragma once
#include "CoreModules/moduleFactory.hh"
#include "CoreModules/module_info_base.hh"
#include "comm/comm_module.hh"
#include "elements/4ms_widgets.hh"
#include "util/base_concepts.hh"

using namespace rack;

template<Derived<ModuleInfoBase> Defs>
struct GenericModule {
	static rack::Model *create() {
		return rack::createModel<Module, Widget>(Defs::slug.data());
	}

	struct Module : CommModule {
		Module() {
			// Calculate number of LED elements
			constexpr auto NumRGBLEDButtons = std::count_if(Defs::Switches.begin(), Defs::Switches.end(), [](auto &sw) {
				return sw.switch_type == SwitchDef::MomentaryButton;
			});
			constexpr auto NumMonoLEDButtons =
				std::count_if(Defs::Switches.begin(), Defs::Switches.end(), [](auto &sw) {
					return sw.switch_type == SwitchDef::LatchingButton;
				});
			constexpr auto NumLEDElements = Defs::Leds.size() + NumRGBLEDButtons * 3 + NumMonoLEDButtons;

			// Calculate number of parameters
			constexpr auto NumParams = Defs::Knobs.size() + Defs::Switches.size();

			// create the given number of elements of each type
			configComm(NumParams, Defs::InJacks.size(), Defs::OutJacks.size(), NumLEDElements);

			// create processing core
			core = ModuleFactory::create(Defs::slug);

			// Setup all the parameters (knobs and switches)
			int parameterCounter = 0;

			for (auto knob : Defs::Knobs) {
				configParam(parameterCounter++, 0.f, 1.f, knob.default_val, knob.long_name.data());
			}

			for (auto sw : Defs::Switches) {
				auto thisParamterID = parameterCounter++;

				if (sw.switch_type == SwitchDef::Encoder) {
					configParam(thisParamterID, -INFINITY, INFINITY, 0.0f, sw.long_name.data());
				} else {
					auto max = sw.switch_type == SwitchDef::Toggle3pos ? 2.f : 1.f;

					configParam(thisParamterID, 0.f, max, 0.f, sw.long_name.data());
					// commParams[thisParamterID]->scaleFactor = 1.f / max;
				}
			}

			uint32_t altID = 0;
			for (auto &alt : Defs::AltParams) {
				altParams.push_back({true, altID++, alt.default_val});
			}
		}
	};

	struct Widget : rack::app::ModuleWidget {
		CommModule *mainModule;

		Widget(CommModule *module)
			: mainModule{module} {
			// link this widget to given module
			setModule(static_cast<Module *>(module));

			// use svg file as panel
			setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, Defs::svg_filename.data())));

			// draw screws
			addChild(createWidget<ScrewBlack>(rack::math::Vec(RACK_GRID_WIDTH, 0)));
			addChild(createWidget<ScrewBlack>(rack::math::Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
			if (box.size.x > RACK_GRID_WIDTH * 7) // >7HP = 2 screws
			{
				addChild(createWidget<ScrewBlack>(rack::math::Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
				addChild(createWidget<ScrewBlack>(
					rack::math::Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
			}

			// Add lights
			int light_id = 0;

			for (auto led : Defs::Leds) {
				auto pos = rack::mm2px({led.x_mm, led.y_mm});
				addChild(createLightCentered<MediumLight<RedLight>>(pos, module, light_id));
				light_id++;
			}

			// Add parameters
			int parameterID = 0;

			for (auto knob : Defs::Knobs) {
				auto ctr_pos = rack::mm2px({knob.x_mm, knob.y_mm});
				auto thisParamerID = parameterID++;

				switch (knob.knob_style) {
					case KnobDef::Small: {
						auto *kn = rack::createParamCentered<Small9mmKnob>(ctr_pos, module, thisParamerID);
						addParam(kn);
					} break;

					case KnobDef::Medium: {
						auto *kn = rack::createParamCentered<Davies1900hBlackKnob4ms>(ctr_pos, module, thisParamerID);
						addParam(kn);
					} break;

					case KnobDef::Large: {
						auto *kn = rack::createParamCentered<DaviesLarge4ms>(ctr_pos, module, thisParamerID);
						addParam(kn);
					} break;

					case KnobDef::Slider25mm: {
						if (knob.orientation == KnobDef::Vertical) {
							auto *kn = rack::createParamCentered<FourmsLightSlider<rack::WhiteLight>>(
								ctr_pos, module, thisParamerID);
							addParam(kn);
						} else {
							auto *kn = rack::createParamCentered<FourmsLightSliderHorizontal<rack::WhiteLight>>(
								ctr_pos, module, thisParamerID);
							addParam(kn);
						}
					} break;
				}
			}

			for (auto sw : Defs::Switches) {
				auto thisParamerID = parameterID++;
				auto pos = rack::mm2px({sw.x_mm, sw.y_mm});

				if (sw.switch_type == SwitchDef::LatchingButton) {
					// These use a single white LED
					addParam(rack::createParamCentered<LatchingSwitch<LEDBezel>>(pos, module, thisParamerID));
					addChild(createLightCentered<LEDBezelLight<WhiteLight>>(pos, module, light_id));
					light_id++;

				} else if (sw.switch_type == SwitchDef::MomentaryButton) {
					// These use an RGB LED (3 elements)
					addParam(rack::createParamCentered<MomentarySwitch<LEDBezel>>(pos, module, thisParamerID));
					addChild(createLightCentered<LEDBezelLight<RedGreenBlueLight>>(pos, module, light_id));
					light_id += 3;

				} else if (sw.switch_type == SwitchDef::Toggle2pos) {
					if (sw.orientation == SwitchDef::Vertical)
						addParam(rack::createParamCentered<SubMiniToggle2pos>(pos, module, thisParamerID));
					else
						addParam(rack::createParamCentered<SubMiniToggleHoriz2pos>(pos, module, thisParamerID));

				} else if (sw.switch_type == SwitchDef::Toggle3pos) {
					if (sw.orientation == SwitchDef::Vertical)
						addParam(rack::createParamCentered<SubMiniToggle3pos>(pos, module, thisParamerID));
					else
						addParam(rack::createParamCentered<SubMiniToggleHoriz3pos>(pos, module, thisParamerID));

				} else if (sw.switch_type == SwitchDef::Encoder) {
					// TODO: add un-lined knobs
					if (sw.encoder_knob_style == SwitchDef::Small)
						addParam(rack::createParamCentered<Small9mmUnlinedKnob>(pos, module, thisParamerID));
					else if (sw.encoder_knob_style == SwitchDef::Medium)
						addParam(rack::createParamCentered<Davies1900hBlackKnobUnlined4ms>(pos, module, thisParamerID));
				}
			}

			int inJackID = 0;
			for (auto jack : Defs::InJacks) {
				addInput(createInputCentered<PJ301MPort>(rack::mm2px({jack.x_mm, jack.y_mm}), module, inJackID++));
			}

			int outJackID = 0;
			for (auto jack : Defs::OutJacks) {
				addOutput(createOutputCentered<PJ301MPort>(rack::mm2px({jack.x_mm, jack.y_mm}), module, outJackID++));
			}
		}

		//////////////////// Alt Params

		// TODO: make a choose-one-of-two/three button array instead of slider
		// Can use it when Range is Integer and max-min <= 3
		// Can query names with get_alt_param_value(id, min|..|max);
		struct AltParamQty : rack::Quantity {
			const AltParamDef &_alt;
			CommModule &_module;
			float _val;

			AltParamQty(CommModule &module, const AltParamDef &alt)
				: _alt{alt}
				, _module{module}
				, _val{alt.default_val} {
				for (auto &ap : _module.altParams) {
					if (ap.id == _alt.id) {
						_val = ap.val;
						break;
					}
				}
			}

			void setValue(float value) override {
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

			std::string getDisplayValueString() override {
				if (_module.core)
					return std::string{_module.core->get_alt_param_value(_alt.id, _val)};
				return std::to_string(_val);
			}

			float getValue() override {
				return _val;
			}
			float getMinValue() override {
				return _alt.min_val;
			}
			float getMaxValue() override {
				return _alt.max_val;
			}
			float getDefaultValue() override {
				return _alt.default_val;
			}
		};

		struct AltParamSlider : rack::ui::Slider {
			AltParamSlider(CommModule &module, const AltParamDef &alt) {
				quantity = new AltParamQty{module, alt};
			}
			~AltParamSlider() {
				delete quantity;
			}
		};

		void appendContextMenu(rack::ui::Menu *menu) override {
			menu->addChild(new rack::ui::MenuEntry);
			for (auto &alt : Defs::AltParams) {
				auto *item = new rack::ui::MenuItem;
				item->text = std::string{alt.short_name};
				menu->addChild(item);

				auto slider = new AltParamSlider{*mainModule, alt};
				slider->box.size.x = 100;
				menu->addChild(slider);
			}
		}
	};
};
