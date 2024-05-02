#include "CoreModules//moduleFactory.hh"
#include <app/ModuleWidget.hpp>
#include <deque>
#include <plugin/Model.hpp>
#include <plugin/Plugin.hpp>

#include "console/pr_dbg.hh"

namespace rack::plugin
{

void Plugin::addModel(Model *model) {
	if (!model)
		return;

	using namespace MetaModule;

	std::string_view slug = model->slug;
	pr_trace("Adding VCV_adaptor model %s\n", model->slug.c_str());

	if (ModuleFactory::isValidSlug(slug)) {
		pr_err("Duplicate module slug: %s, skipping\n", model->slug.c_str());
		return;
	}

	auto module = model->createModule();
	auto modulewidget = model->createModuleWidget(module);

	modulewidget->populate_elements(model->elements);
	model->move_strings();

	std::string panelsvg;
	if (modulewidget->svg_filename.size()) {
		panelsvg = modulewidget->svg_filename;
	} else if (modulewidget->panel && modulewidget->panel->svg) {
		panelsvg = modulewidget->panel->svg->filename;
	}

	if (panelsvg.size()) {
		auto panel_filename = model->add_string(panelsvg);
		ModuleFactory::registerModuleFaceplate(slug, panel_filename);
	} else
		pr_err("No faceplate for %s\n", model->slug.c_str());

	// if (slug == "MotionMTR")
	// 	model->debug_dump_strings();

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
		// pr_dbg("Deleting Model %s\n", model->slug.c_str());
		delete model;
	}
}

Model *Plugin::getModel(const std::string &slug) {
	//TODO: find slug in models
	// return std::find_if(models.begin(), models.end(), [&](auto &m) { return slug == m->slug; });
	return nullptr;
}

std::string Plugin::getBrand() {
	return slug;
}

} // namespace rack::plugin
