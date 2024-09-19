#pragma once
#include "CoreModules/elements/element_state_conversion.hh"
#include "util/overloaded.hh"
#include <string>

// TODO: there should be no dependency on a specific brand here
#include "CoreModules/4ms/4ms_element_state_conversions.hh"

namespace MetaModule
{

inline std::string get_element_value_string(Element const &element, float value, float resolution) {
	std::string s;

	std::visit(overloaded{
				   [value = value, res = resolution, &s](Pot const &) {
					   float v = std::clamp(value * 100.f, 0.f, 100.f);
					   char buf[16];
					   if (res <= 100)
						   std::snprintf(buf, sizeof buf, "%.0f", v);
					   if (res == 1000)
						   std::snprintf(buf, sizeof buf, "%.1f", v);
					   if (res >= 10000)
						   std::snprintf(buf, sizeof buf, "%.2f", v);
					   s = std::string(buf) + "%";
				   },

				   [value = value, &s](ParamElement const &) { s = std::to_string((int)(value * 100.f)) + "%"; },

				   [value = value, &s](SlideSwitch const &el) {
					   auto v = StateConversion::convertState(el, value);
					   if (v > 0 && v <= el.pos_names.size() && el.pos_names[v - 1].size())
						   s = el.pos_names[v - 1];
					   else
						   s = std::to_string(v) + std::string("/") + std::to_string(el.num_pos);
				   },

				   [value = value, &s](FlipSwitch const &el) {
					   auto v = StateConversion::convertState(el, value);
					   if (v < el.pos_names.size())
						   s = el.pos_names[v];
					   else
						   s = std::to_string(v);
				   },

				   [value = value, &s](MomentaryButton const &) { s = value < 0.5f ? "Released" : "Pressed"; },

				   [value = value, &s](LatchingButton const &) { s = value < 0.5f ? "Off" : "On"; },

				   [value = value, &s](AltParamContinuous const &) { s = std::to_string((int)(value * 100.f)) + "%"; },

				   [value = value, &s](AltParamChoice const &el) {
					   auto v = StateConversion::convertState(el, value);
					   s = std::to_string(v + 1) + std::string("/") + std::to_string(el.num_pos);
				   },

				   [value = value, &s](AltParamChoiceLabeled const &el) {
					   auto v = StateConversion::convertState(el, value);
					   if (v >= 0 && v < el.pos_names.size() && el.pos_names[v].size())
						   s = el.pos_names[v];
					   else
						   s = std::to_string(v + 1) + std::string("/") + std::to_string(el.num_pos);
				   },

				   [](BaseElement const &) {},
			   },
			   element);

	return s;
}

} // namespace MetaModule
