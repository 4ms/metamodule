#pragma once
#include "VCV_adaptor/common.hpp"
// #include "math.hpp"

namespace rack::engine
{

struct Param {
	float value = 0.f;

	float getValue() ;

	void setValue(float value) ;
};

} // namespace rack::engine
