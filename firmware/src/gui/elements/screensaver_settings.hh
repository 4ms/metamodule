#pragma once

#include "util/static_string.hh"
#include <array>
#include <cstdint>

namespace MetaModule
{

inline constexpr uint32_t minToMs(float minute) {
	return minute * 60 * 1000;
}

struct ScreensaverSettings {
	static constexpr auto defaultTimeout = UINT32_MAX; //never or 47.72 days
	struct Option {
		uint32_t timeout_ms;
		std::string_view label;
	};
	static constexpr std::array ValidOptions = {
		Option{minToMs(0.0624), "test"},
		Option{defaultTimeout, "Never"},
		Option{minToMs(0.5), "30 Sec"},
		Option{minToMs(1), "1 Min"},
		Option{minToMs(5), "5 Min"},
		Option{minToMs(10), "10 Min"},
		Option{minToMs(30), "30 Min"},
		Option{minToMs(60), "1 Hour"},
		Option{minToMs(60 * 4), "4 Hours"},
	};

	uint32_t timeout_ms{defaultTimeout};
	bool knobs_can_wake = true;

	void make_valid() {
		bool valid = false;
		for (auto o : ValidOptions) {
			if (timeout_ms == o.timeout_ms)
				valid = true;
		}
		if (!valid)
			timeout_ms = defaultTimeout;
	}
};
} // namespace MetaModule
