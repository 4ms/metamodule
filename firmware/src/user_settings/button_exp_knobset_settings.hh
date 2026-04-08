#pragma once
#include <array>
#include <cstdint>
#include <string_view>

namespace MetaModule
{

struct ButtonExpKnobSetSettings {
	// Bitfield: each expander N (1-4) is represented by (1 << N)
	static constexpr uint32_t Disabled = 0;
	static constexpr uint32_t Any = 0b1111;
	static constexpr uint32_t Exp1 = (1 << 0);
	static constexpr uint32_t Exp2 = (1 << 1);
	static constexpr uint32_t Exp3 = (1 << 2);
	static constexpr uint32_t Exp4 = (1 << 3);

	struct Option {
		uint32_t value;
		std::string_view label;
	};
	static constexpr std::array ValidOptions = {
		Option{Disabled, "Off"},
		Option{Any, "Any"},
		Option{Exp1, "#1"},
		Option{Exp2, "#2"},
		Option{Exp3, "#3"},
		Option{Exp4, "#4"},
	};

	static constexpr uint32_t DefaultButtonExpander = Disabled;
	static constexpr bool DefaultRequireBack = true;
	static constexpr uint32_t ValidMask = Any | Exp1 | Exp2 | Exp3 | Exp4;

	uint32_t button_expander = DefaultButtonExpander;
	bool require_back = DefaultRequireBack;

	void make_valid() {
		// Check that only valid bits are set
		if (button_expander & ~ValidMask)
			button_expander = DefaultButtonExpander;

		if (*reinterpret_cast<uint8_t *>(&require_back) != 0)
			require_back = true;
		else
			require_back = false;
	}
};

} // namespace MetaModule
