#pragma once
#include "params/catchup_param.hh"
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
	static constexpr bool DefaultAllowJump = true;

	CatchupParam::Mode mode = DefaultMode;
	bool allow_jump_outofrange = DefaultAllowJump;

	void make_valid() {

		bool valid = false;
		for (auto opt : ValidOptions) {
			if (mode == opt.mode)
				valid = true;
		}
		if (!valid)
			mode = DefaultMode;

		// Check if deserialized data contains a value other than 0 or 1
		if (*reinterpret_cast<uint8_t *>(&allow_jump_outofrange) != 0)
			allow_jump_outofrange = true;
		else
			allow_jump_outofrange = false;
	}
};

} // namespace MetaModule
