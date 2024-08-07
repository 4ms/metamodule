#include "console/pr_dbg.hh"
#include "module_widget_adaptor.hh"
#include "shared/CoreModules/moduleFactory.hh"
#include <app/ModuleWidget.hpp>
#include <deque>
#include <plugin/Model.hpp>
#include <plugin/Plugin.hpp>

extern rack::plugin::Plugin *pluginInstance;

namespace rack::plugin
{

void Plugin::addModel(Model *model) {
	if (!model)
		return;

	using namespace MetaModule;

	model->plugin = pluginInstance;
	std::string_view slug = model->slug;
	std::string_view brand = model->plugin->slug;

	pr_trace("Adding VCV_adaptor model %s:%s\n", brand.data(), slug.data());

	if (ModuleFactory::isValidBrandModule(brand, slug)) {
		pr_err("Duplicate module slug: %s, skipping\n", model->slug.c_str());
		return;
	}

	auto module = model->createModule();
	auto modulewidget = model->createModuleWidget(module);

	modulewidget->adaptor->populate_elements_indices(model->elements, model->indices);
	model->move_strings();

	std::string panelsvg;
	if (modulewidget->svg_filename.size()) {
		panelsvg = modulewidget->svg_filename;
	} else if (modulewidget->panel && modulewidget->panel->svg) {
		panelsvg = modulewidget->panel->svg->filename;
	}

	std::string_view panel_filename = "";

	if (panelsvg.size()) {
		panel_filename = model->add_string(panelsvg);
	} else {
		pr_err("No faceplate for %s\n", model->slug.c_str());
	}

	// if (slug == "MotionMTR")
	// 	model->debug_dump_strings();

	// if (slug.ends_with("ABC")) {
	// 	for (auto [el, ind] : zip(model->elements, model->indices)) {
	// 		auto base = base_element(el);
	// 		pr_dbg("%.*s - ", base.short_name.size(), base.short_name.data());
	// 		pr_dbg("p:%d i:%d o:%d l:%d\n", ind.param_idx, ind.input_idx, ind.output_idx, ind.light_idx);
	// 	}
	// }

	ModuleInfoView info;
	info.elements = model->elements;
	info.description = slug;
	info.width_hp = 1; //TODO: deprecate width_hp
	info.indices = model->indices;

	ModuleFactory::registerModuleType(brand, slug, model->creation_func, info, panel_filename);

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

		MetaModule::ModuleFactory::unregisterBrand(slug);
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
