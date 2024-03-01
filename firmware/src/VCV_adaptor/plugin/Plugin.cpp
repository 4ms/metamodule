#include "VCV_adaptor/plugin/Plugin.hpp"
#include "CoreModules//moduleFactory.hh"
#include "app/ModuleWidget.hpp"
#include "console/pr_dbg.hh"
#include "util/overloaded.hh"

namespace MetaModule
{

// template<typename ModuleT>
// std::unique_ptr<CoreProcessor> create_vcv_module() {
// 	return std::make_unique<ModuleT>();
// }

// Points all string_views of elements to strings in the returned strings
inline void rebase_strings(std::vector<MetaModule::Element> &elements, std::vector<std::string> &strings) {
	size_t num_strings = 0;
	for (auto &element : elements) {
		std::visit(overloaded{
					   [&num_strings](MetaModule::BaseElement) { num_strings += 2; },
					   [&num_strings](MetaModule::ImageElement &el) { num_strings += 3; },
					   [&num_strings](MetaModule::Slider &el) { num_strings += 4; },
					   [&num_strings](MetaModule::FlipSwitch &el) { num_strings += 9; },
					   [&num_strings](MetaModule::SlideSwitch &el) { num_strings += el.num_pos + 4; },
				   },
				   element);
	}
	strings.reserve(num_strings);
	printf("Reserved %zu strings\n", num_strings);

	for (auto &element : elements) {
		std::visit(
			[&strings](BaseElement &el) {
				el.short_name = strings.emplace_back(el.short_name);
				el.long_name = strings.emplace_back(el.long_name);
			},
			element);

		std::visit(overloaded{[](auto &el) {},
							  [&strings](ImageElement &el) {
								  el.image = strings.emplace_back(el.image);
							  }},
				   element);
		std::visit(overloaded{[](auto &el) {},
							  [&strings](Slider &el) {
								  el.image_handle = strings.emplace_back(el.image_handle);
							  }},
				   element);
		std::visit(overloaded{[](auto &el) {},
							  [&strings](FlipSwitch &el) {
								  for (auto &pos_name : el.pos_names)
									  pos_name = strings.emplace_back(pos_name);

								  for (auto &frame : el.frames)
									  frame = strings.emplace_back(frame);
							  }},
				   element);
		std::visit(overloaded{[](auto &el) {},
							  [&strings](SlideSwitch &el) {
								  el.image_handle = strings.emplace_back(el.image_handle);

								  for (auto &pos_name : el.pos_names)
									  pos_name = strings.emplace_back(pos_name);
							  }},
				   element);
	}
}

inline void debug_dump_strings(std::span<MetaModule::Element> elements, std::span<std::string> string_table) {
	for (auto &s : string_table)
		printf("strtab:\t%p\t%s\n", s.data(), s.c_str());

	for (auto &element : elements) {
		auto el = base_element(element);
		printf("el.short_name: %.*s: %p\n", (int)el.short_name.size(), el.short_name.data(), el.short_name.data());
		std::visit(overloaded{[](auto &el) {},
							  [](SlideSwitch &el) {
								  for (auto &pos_name : el.pos_names)
									  printf("el.pos_names[]: %.*s: %p\n",
											 (int)pos_name.size(),
											 pos_name.data(),
											 pos_name.data());
							  }},
				   element);
	}

	printf("\n\n");
}

// template<typename ModuleT, typename WidgetT>
// rack::plugin::Model *createModel2(std::string_view slug)
// 	requires(std::derived_from<WidgetT, rack::ModuleWidget>) && (std::derived_from<ModuleT, rack::engine::Module>)
// {
// 	using namespace MetaModule;

// 	// ModuleFactory::registerModuleType(slug, create_vcv_module<ModuleT>);

// 	if (!ModuleFactory::isValidSlug(slug)) {
// 		// Construct the module and modulewidget, so we can intercept their calls
// 		ModuleT module;
// 		WidgetT mw{&module};

// 		// Store backing data for Info struct as static data, unique to each call of createModel<ModuleT, WidgetT>
// 		static std::vector<MetaModule::Element> elements;
// 		static std::vector<ElementCount::Indices> indices;
// 		static std::vector<std::string> string_table;

// 		mw.populate_elements(elements);
// 		rebase_strings(elements, string_table);

// 		indices.resize(elements.size());
// 		ElementCount::get_indices(elements, indices);

// 		MetaModule::ModuleInfoView info;
// 		info.elements = elements;
// 		info.description = slug;
// 		info.width_hp = 1; //TODO: deprecate width_hp
// 		info.indices = indices;

// 		ModuleFactory::registerModuleType(slug, info);

// 		// debug_dump_strings(elements, string_table);

// 		// TODO: create a Model type which refers to ModuleT and WidgetT, and return a ptr to a static instance of it
// 		return nullptr;
// 	}

// 	return nullptr;
// }

} // namespace MetaModule

namespace rack::plugin
{

void Plugin::addModel(Model *model) {
	using namespace MetaModule;

	std::string_view slug = model->slug;

	if (ModuleFactory::isValidSlug(slug)) {
		pr_err("Duplicate module slug: %s, skipping\n", model->slug.c_str());
		return;
	}

	auto module = model->createModule();
	auto modulewidget = model->createModuleWidget(module);

	modulewidget->populate_elements(model->elements);
	rebase_strings(model->elements, model->string_table);

	model->indices.resize(model->elements.size());
	ElementCount::get_indices(model->elements, model->indices);

	MetaModule::ModuleInfoView info;
	info.elements = model->elements;
	info.description = slug;
	info.width_hp = 1; //TODO: deprecate width_hp
	info.indices = model->indices;

	ModuleFactory::registerModuleType(slug, info);

	model->plugin = this;
	models.push_back(model);
}

Plugin::~Plugin() {
	for (Model *model : models) {
		model->plugin = nullptr;
		// In VCV Rack: don't delete model because it's allocated once and referenced by a global.

		// In MetaModule: we need to delete the models when the Plugin is removed
		pr_dbg("Deleting Model %s\n", model->slug.c_str());
		delete model;
	}
}

} // namespace rack::plugin
