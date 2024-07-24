#pragma once
#include "AirwinRegistry.h"
#include "CoreModules/elements/element_sort.hh"
#include "CoreModules/elements/elements_index.hh"
#include "CoreModules/register_module.hh"
#include "module.hh"
#include <memory>

namespace MetaModuleAirwindows
{

class ModuleCreator {
public:
	ModuleCreator(unsigned reg_idx)
		: registry_idx{reg_idx} {

		create_elements();
		register_module();
	}

private:
	template<typename T>
	T new_element(unsigned x, unsigned y, std::string_view image, std::string name) {
		auto el = T{};
		el.x_mm = MetaModule::to_mm(x);
		el.y_mm = MetaModule::to_mm(y);
		el.image = image;
		el.short_name = element_names.emplace_back(name);
		return el;
	}

	void index_element(auto &elem_idx, MetaModule::Element const &element, uint8_t idx) {
		auto indices = MetaModule::ElementIndex::set_index(element, idx);
		elem_idx.push_back({element, indices});
	}

	void create_elements() {
		constexpr float WidthHP = 10;
		constexpr float WidthPx = WidthHP * 0.2f * 75;

		constexpr std::string_view JackImage = "Airwin2Rack/comp/jack.png";
		constexpr std::string_view MainKnobImage = "Airwin2Rack/comp/main_knob.png";
		constexpr std::string_view AttenKnob = "Airwin2Rack/comp/atten_knob.png";
		constexpr std::string_view SliderBg = "Airwin2Rack/comp/slider_bg.png";
		constexpr std::string_view SliderHandle = "Airwin2Rack/comp/slider_handle.png";

		auto fx = AirwinRegistry::registry[registry_idx].generator();
		auto num_fx_params = std::min<unsigned>(AirwinRegistry::registry[registry_idx].nParams, maxParams);

		// printf("Creating %s with %u params\n", Name, num_fx_params);

		element_names.clear();
		element_names.reserve(6 + num_fx_params * 3); //InL InR OutL OutR VolL VolR

		std::vector<std::pair<MetaModule::Element, ElementCount::Indices>> elem_idx;

		// Try to match Airwin2Rack VCV module layout:
		{
			float row_spacing = 270.f / num_fx_params;
			float ypos = 28.f + row_spacing / 2.f;

			char name_buffer[256]{};

			for (auto i = 0u; i < num_fx_params; i++) {
				fx->getParameterName(i + PARAM_0, name_buffer);
				if (name_buffer[0] == '\0') {
					printf("Skip param with no name\n");
					continue;
				}

				auto param_name = std::string{name_buffer};
				auto main_knob = new_element<MetaModule::Knob>(WidthPx - 70, ypos, MainKnobImage, param_name);
				main_knob.DefaultValue = 0;
				index_element(elem_idx, main_knob, i + ParamIds::PARAM_0);

				auto cv_knob = new_element<MetaModule::Knob>(WidthPx - 45, ypos, AttenKnob, param_name + " CV Scale");
				cv_knob.DefaultValue = 0.5f;
				index_element(elem_idx, cv_knob, i + ParamIds::ATTEN_0);

				auto cv_jack = new_element<MetaModule::JackInput>(WidthPx - 18, ypos, JackImage, param_name + " CV In");
				index_element(elem_idx, cv_jack, i + InputIds::CV_0);

				ypos += row_spacing;
			}
		}

		constexpr float RACK_HEIGHT = 380;
		auto q = RACK_HEIGHT - 56;

		auto inL_jack = new_element<MetaModule::JackInput>(18, q, JackImage, "Audio In L");
		auto inR_jack = new_element<MetaModule::JackInput>(43, q, JackImage, "Audio In R");
		index_element(elem_idx, inL_jack, InputIds::INPUT_L);
		index_element(elem_idx, inR_jack, InputIds::INPUT_R);

		auto outL_jack = new_element<MetaModule::JackOutput>(107, q, JackImage, "Audio Out L");
		auto outR_jack = new_element<MetaModule::JackOutput>(132, q, JackImage, "Audio Out R");
		index_element(elem_idx, outL_jack, OutputIds::OUTPUT_L);
		index_element(elem_idx, outR_jack, OutputIds::OUTPUT_R);

		{
			auto slider_in = new_element<MetaModule::Slider>(65, 325, SliderBg, "Input Level");
			slider_in.image_handle = SliderHandle;
			slider_in.DefaultValue = 0.7f;
			index_element(elem_idx, slider_in, ParamIds::IN_LEVEL);
		}

		{
			auto slider_out = new_element<MetaModule::Slider>(86, 325, SliderBg, "Output Level");
			slider_out.image_handle = SliderHandle;
			slider_out.DefaultValue = 0.7f;
			index_element(elem_idx, slider_out, ParamIds::OUT_LEVEL);
		}

		MetaModule::populate_sorted_elements_indices(elem_idx, elements, indices);
	}

	void register_module() {

		MetaModule::ModuleInfoView info;

		auto Name = AirwinRegistry::registry[registry_idx].name;
		auto name = std::string(Name);

		info.elements = elements;
		info.indices = indices;
		info.width_hp = 10;
		std::string description = "Airwindows module " + name;
		//TODO: add other strings from airwin registry?
		info.description = description;

		// TODO: auto-gen artwork:
		// std::string panel_name = "Airwin2Rack/panel/" + name + ".png";

		std::string panel_name = "Airwin2Rack/panel/panel.png";
		std::string brand = "Airwindows";

		MetaModule::register_module(
			brand, Name, [idx = registry_idx]() { return std::make_unique<Module>(idx); }, info, panel_name);
	}

	unsigned registry_idx;

	std::vector<MetaModule::Element> elements;
	std::vector<ElementCount::Indices> indices;
	std::vector<std::string> element_names;
};

} // namespace MetaModuleAirwindows
