#pragma once

#include <cstdint>

struct JackMap {
	int sendingJackId = 0;
	int receivedJackId = 0;
	int64_t sendingModuleId = 0;
	int64_t receivedModuleId = 0;
	bool connected = false;

	bool isSameJack(JackMap &other) {
		return (sendingJackId == other.sendingJackId) && (sendingModuleId == other.sendingModuleId);
	}
};
