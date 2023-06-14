#pragma once
#include "CoreModules/moduleFactory.hh"
#include "CoreModules/module_info_base.hh"
#include "comm/comm_module.hh"
#include "elements/vcv_module_creator.hh"
#include "elements/widget_creator.hh"
#include "util/base_concepts.hh"

using namespace rack;
using namespace MetaModule;

template<Derived<ElementInfoBase> Defs>
struct GenericModuleNew {
	static rack::Model *create() {
		return rack::createModel<Module, Widget>(Defs::slug.data());
	}

	struct Module : CommModule {
		Module() {
			// create processing core
			core = ModuleFactory::create(Defs::slug);

			VCVModuleParamCreator creator{this};

			// Count the elements of each type
			for (auto &element : Defs::Elements) {
				std::visit([&creator](auto &el) { creator.count_element(el); }, element);
			}

			// Register with VCV the number of elements of each type
			configComm(creator.num_params, creator.num_inputs, creator.num_outputs, creator.num_lights);

			// Configure elements with VCV
			for (auto &element : Defs::Elements) {
				std::visit([&creator](auto &el) { creator.config_element(el); }, element);
			}

			// TODO: alt params
			// uint32_t altID = 0;
			// for (auto &alt : Defs::AltParams) {
			// 	altParams.push_back({true, altID++, alt.default_val});
			// }
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

			// create widgets from all elements
			VCVWidgetCreator creator{this, module};
			for (auto &element : Defs::Elements) {
				std::visit([&creator](auto &el) { creator.create(el); }, element);
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

		// void appendContextMenu(rack::ui::Menu *menu) override
		// {
		// 	menu->addChild(new rack::ui::MenuEntry);
		// 	for (auto &alt : Defs::AltParams) {
		// 		auto *item = new rack::ui::MenuItem;
		// 		item->text = std::string{alt.short_name};
		// 		menu->addChild(item);

		// 		auto slider = new AltParamSlider{*mainModule, alt};
		// 		slider->box.size.x = 100;
		// 		menu->addChild(slider);
		// 	}
		// }
	};
};
