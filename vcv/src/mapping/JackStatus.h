#pragma once

#include <cstdint>

struct JackStatus {
	int sendingJackId = 0;
	int receivedJackId = 0;
	int64_t sendingModuleId = 0;
	int64_t receivedModuleId = 0;
	bool connected = false;

	bool isSameJack(JackStatus &other) {
		return (sendingJackId == other.sendingJackId) && (sendingModuleId == other.sendingModuleId);
	}
};
