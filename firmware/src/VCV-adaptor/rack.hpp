#pragma once

// #pragma gcc add -Wno-double-promotion
#include "VCV-adaptor/simd/Vector.hpp"
#include "VCV-adaptor/simd/functions.hpp"
// #pragma pop option

#include "VCV-adaptor/Module.hpp"
#include "VCV-adaptor/ModuleWidget.hpp"
#include "VCV-adaptor/assert.hh"
#include "VCV-adaptor/dsp/filter.hpp"
#include "VCV-adaptor/dsp/minblep.hpp"
#include "VCV-adaptor/math.hpp"
#include "VCV-adaptor/port.hh"
#include "VCV-adaptor/widgets.hh"
#include <string_view>

#include "CoreModules/coreProcessor.h"
#include "CoreModules/moduleFactory.hh"

using namespace rack::math;

namespace rack
{

#define dynamic_cast stub_dynamic_cast

template<typename T>
T stub_dynamic_cast(void *) {
	return nullptr;
}

//math
inline math::Vec mm2px(math::Vec) {
	return {0, 0};
}

template<typename ModuleT>
std::unique_ptr<CoreProcessor> create_vcv_module() {
	return std::make_unique<ModuleT>();
}

//model
template<typename ModuleT, typename WidgetT>
Model *createModel(std::string_view slug) {
	ModuleFactory::registerModuleType(slug, create_vcv_module<ModuleT>);
	return nullptr;
}

} // namespace rack

using namespace rack;
