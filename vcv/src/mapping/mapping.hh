#pragma once
#include <rack.hpp>

struct Mapping {
	rack::ParamHandle paramHandle;
	float range_min = 0.f;
	float range_max = 1.f;

	void clear() {
		paramHandle.moduleId = -1;
		paramHandle.module = nullptr;
		paramHandle.text = "";
		range_min = 0.f;
		range_max = 1.f;
	}
};
