#include "VCV_adaptor/plugin/Plugin.hpp"
#include "CoreModules//moduleFactory.hh"
#include "app/ModuleWidget.hpp"
#include "console/pr_dbg.hh"
#include "util/overloaded.hh"
#include <deque>

namespace MetaModule
{} // namespace MetaModule

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
	model->move_strings();

	auto panel_filename = model->add_string(modulewidget->svg_filename);
	ModuleFactory::registerModuleFaceplate(slug, panel_filename);

	// model->debug_dump_strings();

	model->indices.resize(model->elements.size());
	ElementCount::get_indices(model->elements, model->indices);

	MetaModule::ModuleInfoView info;
	info.elements = model->elements;
	info.description = slug;
	info.width_hp = 1; //TODO: deprecate width_hp
	info.indices = model->indices;

	ModuleFactory::registerModuleInfo(slug, info);

	model->plugin = this;
	models.push_back(model);

	delete modulewidget;
	delete module;
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
