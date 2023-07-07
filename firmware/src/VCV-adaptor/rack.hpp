#pragma once

// #pragma gcc add -Wno-double-promotion
#include "VCV-adaptor/simd/Vector.hpp"
#include "VCV-adaptor/simd/functions.hpp"
// #pragma pop option

#include "VCV-adaptor/Module.hpp"
#include "VCV-adaptor/ModuleWidget.hpp"
#include "VCV-adaptor/dsp/filter.hpp"
#include "VCV-adaptor/math.hpp"
#include "VCV-adaptor/port.hh"
#include "VCV-adaptor/widgets.hh"
#include <string_view>

using namespace rack::math;

namespace rack
{

//math
math::Vec mm2px(math::Vec) {
	return {0, 0};
}

//ParamQuantity
struct ParamQuantity {
	float maxValue, minValue;
	float getValue() {
		return 0;
	}
	void setValue(float) {
	}
};

//model
template<typename ModuleT, typename WidgetT>
Model *createModel(std::string_view slug) {
	return nullptr;
}

} // namespace rack

using namespace rack;
