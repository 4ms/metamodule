#pragma once
#include "CoreModules/CoreProcessor.hh"
#include "CoreModules/moduleFactory.hh"
#include "VCV_adaptor/app/ModuleWidget.hpp"
#include "VCV_adaptor/plugin/Model.hpp"
#include <string_view>

// #include "CoreModules/AudibleInstruments/info/Braids_info.hh"

namespace rack
{

template<typename ModuleT>
std::unique_ptr<CoreProcessor> create_vcv_module() {
	return std::make_unique<ModuleT>();
}

// Points all string_views of elements to strings in the returned strings
inline void rebase_strings(std::span<MetaModule::Element> elements, std::vector<std::string> &strings) {

	for (auto &element : elements) {
		// Copy the string_view's data to a new string, and then point the string_view to it
		{
			auto el = MetaModule::base_element(element);
			el.short_name = strings.emplace_back(el.short_name);
			el.long_name = strings.emplace_back(el.long_name);
		}
		std::visit(overloaded{[](auto &el) {},
							  [&strings](MetaModule::ImageElement &el) {
								  el.image = strings.emplace_back(el.image);
							  }},
				   element);
		std::visit(overloaded{[](auto &el) {},
							  [&strings](MetaModule::Slider &el) {
								  el.image_handle = strings.emplace_back(el.image_handle);
							  }},
				   element);
		std::visit(overloaded{[](auto &el) {},
							  [&strings](MetaModule::FlipSwitch &el) {
								  for (auto &pos_name : el.pos_names)
									  pos_name = strings.emplace_back(pos_name);
								  for (auto &frame : el.frames)
									  frame = strings.emplace_back(frame);
							  }},
				   element);
		std::visit(overloaded{[](auto &el) {},
							  [&strings](MetaModule::SlideSwitch &el) {
								  el.image_handle = strings.emplace_back(el.image_handle);
								  for (auto &pos_name : el.pos_names)
									  pos_name = strings.emplace_back(pos_name);
							  }},
				   element);
	}
}

template<typename ModuleT, typename WidgetT>
plugin::Model *createModel(std::string_view slug)
	requires(std::derived_from<WidgetT, rack::ModuleWidget>) && (std::derived_from<ModuleT, rack::engine::Module>)
{
	using namespace MetaModule;

	// if (slug == "Braids") {
	// 	ModuleFactory::registerModuleType(
	// 		slug, create_vcv_module<ModuleT>, MetaModule::ModuleInfoView::makeView<MetaModule::BraidsInfo>());
	// 	return nullptr;
	// }

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
