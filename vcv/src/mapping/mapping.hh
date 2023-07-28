#pragma once
#include <rack.hpp>

struct Mapping {
	int64_t moduleId = -1;
	int paramId = -1;
	// std::string text = "";

	float range_min = 0.f;
	float range_max = 1.f;

	void clear() {
		moduleId = -1;
		paramId = -1;
		// text = "";
		range_min = 0.f;
		range_max = 1.f;
	}
};
