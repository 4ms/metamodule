#pragma once
#include <rack.hpp>

struct Mapping {
	struct ParamHandle {
		int64_t moduleId = -1;
		rack::Module *module = nullptr;
		int paramId = -1;
		std::string text = "";
	};

	Mapping::ParamHandle dest;
	float range_min = 0.f;
	float range_max = 1.f;

	void clear() {
		dest.moduleId = -1;
		dest.module = nullptr;
		dest.paramId = -1;
		dest.text = "";
		range_min = 0.f;
		range_max = 1.f;
	}
};
