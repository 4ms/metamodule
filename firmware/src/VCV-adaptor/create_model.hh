#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/moduleFactory.hh"
#include "VCV-adaptor/plugin/Model.hpp"
#include <string_view>

namespace rack
{

#define WARN(...) printf(...)

template<typename ModuleT>
std::unique_ptr<CoreProcessor> create_vcv_module() {
	return std::make_unique<ModuleT>();
}

//model
template<typename ModuleT, typename WidgetT>
plugin::Model *createModel(std::string_view slug) {
	ModuleFactory::registerModuleType(slug, create_vcv_module<ModuleT>);
	return nullptr;
}

} // namespace rack

using namespace rack;
