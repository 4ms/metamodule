#pragma once
#include "CoreModules/CoreProcessor.hh"
#include "CoreModules/moduleFactory.hh"
#include "VCV_adaptor/app/ModuleWidget.hpp"
#include "VCV_adaptor/plugin/Model.hpp"
#include <string_view>

#include "CoreModules/AudibleInstruments/info/Braids_info.hh"

namespace rack
{

template<typename ModuleT>
std::unique_ptr<CoreProcessor> create_vcv_module() {
	return std::make_unique<ModuleT>();
}

template<typename ModuleT, typename WidgetT>
requires(std::derived_from<WidgetT, rack::ModuleWidget>) && (std::derived_from<ModuleT, rack::engine::Module>)
plugin::Model *createModel(std::string_view slug) {

	if (slug == "Braids") {
		ModuleFactory::registerModuleType(
			slug, create_vcv_module<ModuleT>, MetaModule::ModuleInfoView::makeView<MetaModule::BraidsInfo>());
		return nullptr;
	}

	// Register creation function
	ModuleFactory::registerModuleType(slug, create_vcv_module<ModuleT>);

	if (!ModuleFactory::isValidSlug(slug)) {
		ModuleT module;
		WidgetT mw{&module};

		// static storage: each calls to createModel has unique ModuleT/WidgetT
		static std::vector<MetaModule::Element> elements;

		mw.populate_elements(elements);
		MetaModule::ModuleInfoView info;
		info.elements = elements;
		info.description = slug;
		info.width_hp = 1; //TODO: deprecate width_hp

		ModuleFactory::registerModuleType(slug, info);
		return nullptr;
	}

	return nullptr;
}

} // namespace rack

using namespace rack;
