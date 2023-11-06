#pragma once
#include "CoreModules/elements/element_state_conversion.hh"
#include "CoreModules/moduleFactory.hh"
#include "patch/patch.hh"
#include "patch/patch_data.hh"
#include "util/overloaded.hh"

namespace MetaModule
{

struct FullElementName {
	std::string_view module_name;
	std::string_view element_name;
};

enum class ElementType { Param, Input, Output, Light };

// return the module name and element name, when all we have is the IDs and type (not the Element)
inline FullElementName
get_full_element_name(unsigned module_id, unsigned element_idx, ElementType type, PatchData const &patch) {
	FullElementName fullname{"?", "?"};

	if (module_id < patch.module_slugs.size()) {
		fullname.module_name = patch.module_slugs[module_id];

		auto &info = ModuleFactory::getModuleInfo(patch.module_slugs[module_id]);

		if (info.width_hp) {
			// Search in reverse (the matching element is the last one with the matching index)
			for (int el_id = info.indices.size() - 1; el_id >= 0; el_id--) {

				auto idx = info.indices[el_id];

				bool is_found = (type == ElementType::Param)  ? element_idx == idx.param_idx :
								(type == ElementType::Input)  ? element_idx == idx.input_idx :
								(type == ElementType::Output) ? element_idx == idx.output_idx :
								(type == ElementType::Light)  ? element_idx == idx.light_idx :
																false;
				if (is_found) {
					fullname.element_name = base_element(info.elements[el_id]).short_name;
					break;
				}
			}
		}
	}
	return fullname;
}

//TODO:
// Put this in CoreModules?
inline std::string get_element_value_string(Element const &element, float value) {
	std::string s;

	std::visit(overloaded{
				   [=, &s](Pot const &) { s = std::to_string((int)(value * 100.f)) + "%"; },

				   [=, &s](Switch const &) { s = value < 0.5f ? "Down" : "Up"; },

				   [=, &s](SlideSwitch const &el) {
					   auto v = StateConversion::convertState(el, value);
					   s = std::to_string(v) + std::string("/") + std::to_string(el.num_pos);
				   },

				   [=, &s](FlipSwitch const &el) {
					   auto v = StateConversion::convertState(el, value);
					   if (v < el.pos_names.size())
						   s = el.pos_names[v];
				   },

				   [=, &s](MomentaryButton const &) { s = value < 0.5f ? "Released" : "Pressed"; },

				   [=, &s](LatchingButton const &) { s = value < 0.5f ? "Off" : "On"; },

				   [=, &s](Toggle2posHoriz const &) { s = value < 0.5f ? "Left" : "Right"; },

				   [=, &s](Toggle3pos const &) { s = value < 0.25f ? "Down" :
													 value < 0.75f ? "Mid" :
																	 "Up"; },

				   [=, &s](Toggle3posHoriz const &) { s = value < 0.25f ? "Left" :
														  value < 0.75f ? "Mid" :
																		  "Right"; },
				   [&s](BaseElement const &) { s = "?"; },
			   },
			   element);

	return s;
}

} // namespace MetaModule
