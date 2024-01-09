#pragma once
#include "CoreModules/CoreProcessor.hh"
#include <memory>
#include <vector>
#include "CoreModules/moduleFactory.hh"
#include "VCV_adaptor/app/ModuleWidget.hpp"
#include "CoreModules/elements/element_counter.hh"
#include "VCV_adaptor/plugin/Model.hpp"
#include <string_view>


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

	// Register creation function
	ModuleFactory::registerModuleType(slug, create_vcv_module<ModuleT>); //500k

	if (!ModuleFactory::isValidSlug(slug)) {
		static ModuleT module; //400k
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
