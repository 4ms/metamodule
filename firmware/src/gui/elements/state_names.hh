#pragma once
#include "CoreModules/elements/element_state_conversion.hh"
#include "CoreModules/elements/elements.hh"
#include "util/overloaded.hh"
#include <charconv>
#include <string>

namespace MetaModule
{

inline std::string custom_display_value_string(Pot const &el, float value, bool integral = false) {
	std::string s;

	float v = value * (el.max_value - el.min_value) + el.min_value;

	if (integral)
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
		auto res = std::to_chars(s.data(), s.data() + s.size(), v, std::chars_format::general, 5);
		*res.ptr = '\0';
		s.resize(res.ptr - s.data());
	}

	if (el.units.length()) {
		s = s + std::string(el.units);
	}

	return s;
}

inline std::string percent_value_string(float value, float res) {
	std::string s;

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

	return s;
}

inline bool has_custom_display(Pot const &el) {
	return el.display_mult != 1 || el.display_offset != 0 || el.display_base != 0 || el.units.length() > 0 ||
		   el.min_value != 0 || el.max_value != 1;
}

inline bool has_pos_label(KnobSnapped const &el, float value) {
	if (el.num_pos == 0 || el.num_pos > 1000) {
		return false;

	} else {
		unsigned v = std::round(std::clamp(value, 0.f, 1.f) * (float)(el.num_pos - 1));
		return (v >= 0 && v < el.pos_names.size() && el.pos_names[v].length() > 0 && el.pos_names[v].length() < 256);
	}
}

inline std::string snapped_value_string(KnobSnapped const &el, float value) {
	std::string s;
	unsigned v = std::round(std::clamp(value, 0.f, 1.f) * (float)(el.num_pos - 1));

	if (v >= 0 && v < el.pos_names.size()) {
		s = el.pos_names[v];
	}

	return s;
}

inline std::string snapped_value_fallback_string(KnobSnapped const &el, float value) {
	std::string s;
	unsigned v = std::round(std::clamp(value, 0.f, 1.f) * (float)(el.num_pos - 1));

	s.resize(16, '\0');
	auto sz = std::snprintf(s.data(), s.size(), "(Pos. %u/%u)", v + 1, el.num_pos);
	s.resize(sz);

	return s;
}

inline std::string get_element_value_string(Element const &element, float value, float resolution) {
	std::string s;

	std::visit(
		overloaded{
			[value = value, res = resolution, &s](Slider const &el) {
				if (has_custom_display(el))
					s = custom_display_value_string(el, value);
				else
					s = percent_value_string(value, res);
			},

			[value = value, res = resolution, &s](Knob const &el) {
				if (has_custom_display(el))
					s = custom_display_value_string(el, value);
				else
					s = percent_value_string(value, res);
			},

			[value = value, res = resolution, &s](KnobSnapped const &el) {
				bool snap = el.num_pos > 0 && el.num_pos < 1000;

				if (has_pos_label(el, value))
					s = snapped_value_string(el, value);
				else if (has_custom_display(el))
					s = custom_display_value_string(el, value, snap);
				else if (snap)
					s = snapped_value_fallback_string(el, value);
				else
					s = percent_value_string(value, res);
			},

			[value = value, res = resolution, &s](ParamElement const &) { s = percent_value_string(value, res); },

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
