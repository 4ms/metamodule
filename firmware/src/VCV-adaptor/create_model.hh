#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/moduleFactory.hh"
#include "VCV-adaptor/app/ModuleWidget.hpp"
#include "VCV-adaptor/plugin/Model.hpp"
#include <string_view>

namespace rack
{

template<typename ModuleT>
std::unique_ptr<CoreProcessor> create_vcv_module() {
	return std::make_unique<ModuleT>();
}

//model
template<typename ModuleT, typename WidgetT>
requires(std::derived_from<WidgetT, rack::ModuleWidget>)
plugin::Model *createModel(std::string_view slug) {
	// Register creation function
	ModuleFactory::registerModuleType(slug, create_vcv_module<ModuleT>);

	// if (!ModuleFactory::isValidSlug(slug)) {
	// ModuleWidget constructor will call addParam, addInput, etc.
	// and generate the info struct
	ModuleT module;
	WidgetT mw{&module};
	auto info = mw.get_info_view();
	ModuleFactory::registerModuleType(slug, info);
	// }

	return nullptr;
}

} // namespace rack

using namespace rack;
