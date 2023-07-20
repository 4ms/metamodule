#pragma once
#include "VCV_adaptor/common.hpp"
// #include "math.hpp"

namespace rack::engine
{

struct Param {
	float value = 0.f;

	float getValue() {
		return value;
	}

	void setValue(float value) {
		this->value = value;
	}
};

} // namespace rack::engine
