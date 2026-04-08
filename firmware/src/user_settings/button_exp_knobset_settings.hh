#pragma once
#include <cstdint>

namespace MetaModule
{

struct ButtonExpKnobSetSettings {
	static constexpr uint32_t DefaultButtonExpander = 0;
	static constexpr bool DefaultRequireBack = true;

	uint32_t button_expander = DefaultButtonExpander; // 0=disabled, 1-4
	bool require_back = DefaultRequireBack;

	void make_valid() {
		if (button_expander > 4)
			button_expander = DefaultButtonExpander;

		if (*reinterpret_cast<uint8_t *>(&require_back) != 0)
			require_back = true;
		else
			require_back = false;
	}
};

} // namespace MetaModule
