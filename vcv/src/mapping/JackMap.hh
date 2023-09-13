#pragma once

#include <cstdint>
#include "lv_color.h"

struct CableMap {
	int sendingJackId = 0;
	int receivedJackId = 0;
	int64_t sendingModuleId = 0;
	int64_t receivedModuleId = 0;
	// lv_color_t color = {{0, 0, 0}};
	uint16_t color = 0;

	bool isSameJack(const CableMap &other) const {
		return (sendingJackId == other.sendingJackId) && (sendingModuleId == other.sendingModuleId);
	}
};
