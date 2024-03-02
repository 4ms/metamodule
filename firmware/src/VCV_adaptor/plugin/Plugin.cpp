#include "VCV_adaptor/plugin/Plugin.hpp"
#include "CoreModules//moduleFactory.hh"
#include "app/ModuleWidget.hpp"
#include "console/pr_dbg.hh"
#include "util/overloaded.hh"
#include <deque>

namespace MetaModule
{

// Transfer ownership of a model's strings from the Module and ModuleWidget (as VCV does) to the Model/Pluin (which is what MetaModule wants)
// This is done by copying the strings that elements[] string_views point to, and putting the copy in strings[] (which is a member of Model)
// Then point the elements[] string_views to strings[].
inline void move_strings(std::vector<MetaModule::Element> &elements, std::deque<std::string> &strings) {
	for (auto &element : elements) {
		std::visit(
			[&strings](BaseElement &el) {
				el.short_name = strings.emplace_back(el.short_name);
				el.long_name = strings.emplace_back(el.long_name);
			},
			element);

		std::visit(overloaded{[](BaseElement &el) {},
							  [&strings](ImageElement &el) {
								  el.image = strings.emplace_back(el.image);
							  }},
				   element);
		std::visit(overloaded{[](BaseElement &el) {},
							  [&strings](Slider &el) {
								  el.image_handle = strings.emplace_back(el.image_handle);
							  }},
				   element);
		std::visit(overloaded{[](BaseElement &el) {},
							  [&strings](FlipSwitch &el) {
								  for (auto &pos_name : el.pos_names)
									  pos_name = strings.emplace_back(pos_name);

								  for (auto &frame : el.frames) {
									  frame = strings.emplace_back(frame);
								  }
							  }},
				   element);
		std::visit(overloaded{[](BaseElement &el) {},
							  [&strings](SlideSwitch &el) {
								  el.image_handle = strings.emplace_back(el.image_handle);

								  for (auto &pos_name : el.pos_names)
									  pos_name = strings.emplace_back(pos_name);
							  }},
				   element);
	}
}

inline void inspect_sv(std::string_view const &sv) {
	printf("%.*s %p(+%u)\n", sv.size(), sv.data(), sv.data(), sv.size());
}

inline void debug_dump_strings(std::span<MetaModule::Element> elements, std::deque<std::string> const &string_table) {

	for (auto const &s : string_table)
		printf("strtab: %p %s\n", s.data(), s.c_str());

	printf("Dumping element strings: (%zu)\n", elements.size());
	for (auto &element : elements) {
		printf("Type %zu\n", element.index());
		auto el = base_element(element);
		printf("el.short_name: %.*s: %p\n", (int)el.short_name.size(), el.short_name.data(), el.short_name.data());

		std::visit(overloaded{[](BaseElement const &el) {},
							  [](ImageElement const &el) {
								  printf("image: ");
								  inspect_sv(el.image);
							  }},
				   element);

		std::visit(overloaded{[](BaseElement const &el) {},
							  [](SlideSwitch const &el) {
								  for (auto &pos_name : el.pos_names) {
									  printf("slide switch el.pos_names[]: ");
									  inspect_sv(pos_name);
								  }
								  inspect_sv(el.image_handle);
							  },
							  [](FlipSwitch const &el) {
								  for (auto &pos_name : el.pos_names) {
									  printf("flip switch el.pos_names[]: ");
									  inspect_sv(pos_name);
								  }
							  }},
				   element);
	}

	printf("\n");
}

} // namespace MetaModule

namespace rack::plugin
{

void Plugin::addModel(Model *model) {
	using namespace MetaModule;

	std::string_view slug = model->slug;
	pr_dbg("Adding VCV_adaptor model %s\n", model->slug.c_str());

	if (ModuleFactory::isValidSlug(slug)) {
		pr_err("Duplicate module slug: %s, skipping\n", model->slug.c_str());
		return;
	}

	auto module = model->createModule();
	auto modulewidget = model->createModuleWidget(module);

	modulewidget->populate_elements(model->elements);
	move_strings(model->elements, model->string_table);

	// debug_dump_strings(model->elements, model->string_table);

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
