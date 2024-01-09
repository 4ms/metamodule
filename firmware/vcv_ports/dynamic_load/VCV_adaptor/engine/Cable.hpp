#pragma once
#include "VCV_adaptor/common.hpp"
#include "VCV_adaptor/engine/Module.hpp"

namespace rack::engine
{

struct Cable {
	int64_t id = -1;
	Module *inputModule = nullptr;
	int inputId = -1;
	Module *outputModule = nullptr;
	int outputId = -1;

	json_t *toJson() {
		return nullptr;
	}

	void fromJson(json_t *rootJ) {
	}

	PRIVATE static void jsonStripIds(json_t *rootJ) {
	}
};

} // namespace rack::engine
