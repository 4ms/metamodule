#pragma once
#include "CoreModules/CoreProcessor.hh"
#include "CoreModules/moduleFactory.hh"
#include "VCV_adaptor/app/ModuleWidget.hpp"
#include "VCV_adaptor/plugin/Model.hpp"
#include <string_view>

#include "CoreModules/AudibleInstruments/info/Braids_info.hh"
// #include "lib/printf/printf.h"

namespace rack
{

template<typename ModuleT>
std::unique_ptr<CoreProcessor> create_vcv_module() {
	return std::make_unique<ModuleT>();
}

template<typename ModuleT, typename WidgetT>
plugin::Model *createModel(std::string_view slug)
	requires(std::derived_from<WidgetT, rack::ModuleWidget>) && (std::derived_from<ModuleT, rack::engine::Module>)
{

	if (slug == "Braids") {
		ModuleFactory::registerModuleType(
			slug, create_vcv_module<ModuleT>, MetaModule::ModuleInfoView::makeView<MetaModule::BraidsInfo>());
		return nullptr;
	}

	// Register creation function
	ModuleFactory::registerModuleType(slug, create_vcv_module<ModuleT>);

	if (!ModuleFactory::isValidSlug(slug)) {
		// Create a ModuleInfoView at runtime
		// Each call to createModel<...> has unique ModuleT/WidgetT, so each of the static vars below are unique.
		// The static ModuleT holds the strings
		// The static elements vector points to those strings
		// The ModuleInfoView::Elements (that gets registered with ModuleFactory) points to the static elements vector.
		// ModuleInfoView::indices points to the static indices vector
		static ModuleT module;
		WidgetT mw{&module};
		static std::vector<MetaModule::Element> elements;
		static std::vector<ElementCount::Indices> indices;

		mw.populate_elements(elements);
		indices.resize(elements.size());
		ElementCount::get_indices(elements, indices);

		MetaModule::ModuleInfoView info;
		info.elements = elements;
		info.description = slug;
		info.width_hp = 1; //TODO: deprecate width_hp
		info.indices = indices;

		ModuleFactory::registerModuleType(slug, info);

		// TODO: create a Model type which refers to ModuleT and WidgetT, and return a ptr to a static instance of it
		return nullptr;
	}

	return nullptr;
}

} // namespace rack

using namespace rack;
