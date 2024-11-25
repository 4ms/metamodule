#pragma once
#include "catchup_param.hh"
#include <array>
#include <cstdint>
#include <string_view>

namespace MetaModule
{

struct CatchupSettings {
	struct Option {
		CatchupParam::Mode mode;
		std::string_view label;
	};
	static constexpr std::array ValidOptions = {
		Option{CatchupParam::Mode::ResumeOnMotion, "Track if knob moves"},
		Option{CatchupParam::Mode::ResumeOnEqual, "Track when equal"},
		Option{CatchupParam::Mode::LinearFade, "Linear fade"},
	};
	static constexpr CatchupParam::Mode DefaultMode = CatchupParam::Mode::ResumeOnMotion;
	static constexpr bool DefaultButtonExclude = true;

	CatchupParam::Mode mode = DefaultMode;
	bool button_exclude = DefaultButtonExclude;

	void make_valid() {

		bool valid = false;
		for (auto opt : ValidOptions) {
			if (mode == opt.mode)
				valid = true;
		}
		if (!valid)
			mode = DefaultMode;

		// Check if deserialized data contains a value other than 0 or 1
		if (*reinterpret_cast<int *>(&button_exclude) != 0)
			button_exclude = true;
		else
			button_exclude = false;
	}
};

} // namespace MetaModule
