#pragma once
#include "CoreModules/elements/element_state_conversion.hh"
#include "CoreModules/elements/elements.hh"
#include "util/overloaded.hh"
#include <charconv>
#include <string>

// TODO: there should be no dependency on a specific brand here
#include "CoreModules/4ms/4ms_element_state_conversions.hh"

namespace MetaModule
{

inline std::string get_element_value_string(Element const &element, float value, float resolution) {
	std::string s;

	std::visit(overloaded{
				   [value = value, res = resolution, &s](Pot const &el) {
					if (el.min_value == 0 && el.max_value == 1 && el.display_mult == 1 && el.display_offset == 0 &&
						   el.display_base == 0 && el.units.length() == 0)
					   {
						   // No custom range or display: show it as a percentage
						   float v = std::clamp(value * 100.f, 0.f, 100.f);
						   char buf[16];
						   if (res <= 100)
							   std::snprintf(buf, sizeof buf, "%.0f", v);
						   else if (res <= 1000)
							   std::snprintf(buf, sizeof buf, "%.1f", v);
						   else
							   std::snprintf(buf, sizeof buf, "%.2f", v);
						   s = std::string(buf) + "%";

					  	} else if (el.integral && el.num_pos > 0 && el.display_mult == 1 && el.display_offset == 0 &&
						   el.display_base == 0 && el.units.length() == 0) {
						   unsigned v = std::round(std::clamp(value, 0.f, 1.f) * (float)(el.num_pos - 1));

						   if (v >= 0 && v < el.pos_names.size() && el.num_pos <= el.pos_names.size()) {
							   s = el.pos_names[v];
						   } else {
								s.resize(16, '\0');
								auto sz = std::snprintf(s.data(), s.size(), "#%u/%u", v + 1, el.num_pos);
								s.resize(sz);
							}
						} 
						
						if (!s.size()) {
						   // Scale it
						   float v = value * (el.max_value - el.min_value) + el.min_value;
						   if (el.integral)
							   v = std::round(v);
						   if (el.display_base < 0.f) {
							   v = std::log(v) / std::log(-el.display_base);
						   } else if (el.display_base > 0.f) {
							   v = std::pow(el.display_base, v);
						   }
						   v = v * el.display_mult + el.display_offset;

						   s.resize(32, '\0');
						   if (el.display_precision > 0) {
							   auto sz = std::snprintf(s.data(), s.size(), "%.*g", el.display_precision, v);
							   s.resize(sz);
						   } else {
							   auto res = std::to_chars(s.data(), s.data() + s.size(), v); // automatic precision
							   *res.ptr = '\0';
							   s.resize(res.ptr - s.data());
						   }

						   if (el.units.length()) {
							   s = s + std::string(el.units);
						   }
					   }
				   },

				   [value = value, &s](ParamElement const &) { s = std::to_string((int)(value * 100.f)) + "%"; },

				   [value = value, &s](SlideSwitch const &el) {
					   auto v = StateConversion::convertState(el, value);
					   if (v >= 0 && v < el.pos_names.size() && el.pos_names[v].size())
						   s = el.pos_names[v];
					   else
						   s = std::to_string(v + 1) + std::string("/") + std::to_string(el.num_pos);
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
