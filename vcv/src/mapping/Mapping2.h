#pragma once
#include <rack.hpp>

struct Mapping2 {
	int panelParamId = -1;
	rack::ParamHandle paramHandle;
	float range_min = 0.f;
	float range_max = 1.f;
	std::string alias_name{""};

	void clear() {
		panelParamId = -1;
		paramHandle.moduleId = -1;
		paramHandle.module = nullptr;
		paramHandle.text = "";
		range_min = 0.f;
		range_max = 1.f;
		alias_name = "";
	}
};
