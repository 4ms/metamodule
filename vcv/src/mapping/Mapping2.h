#pragma once
#include <rack.hpp>

struct Mapping2 {
	rack::ParamHandle paramHandle;
	float range_min = 0.f;
	float range_max = 1.f;
	std::string alias_name{""};

	void clear() {
		paramHandle.moduleId = -1;
		paramHandle.module = nullptr;
		paramHandle.text = "";
		range_min = 0.f;
		range_max = 1.f;
		alias_name = "";
	}
};
