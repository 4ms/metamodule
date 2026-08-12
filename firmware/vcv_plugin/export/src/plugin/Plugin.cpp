#include "console/pr_dbg.hh"
#include "module_widget_adaptor.hh"
#include <app/ModuleWidget.hpp>
#include <engine/Module.hpp>
#include <memory>
#include <plugin/Model.hpp>
#include <plugin/Plugin.hpp>
#include <string>
#include <string_view>

#include "CoreModules/moduleFactory.hh"

extern rack::plugin::Plugin *pluginInstance;

namespace rack::plugin
{

namespace
{

// Runs for populate_elements_indices() -> move_strings() -> update Info in ModuleFactory
bool populate_element_data(Model *model, std::string const &combined_slug, CoreProcessor *proc) {
	auto module = dynamic_cast<rack::engine::Module *>(proc);
	if (!module) {
		pr_warn("Cannot populate element data for %s: not a rack module\n", combined_slug.c_str());
		return false;
	}

	auto module_widget = module->module_widget.get();
	if (!module_widget) {
		pr_warn("Cannot populate element data for %s: module has no ModuleWidget\n", combined_slug.c_str());
		return false;
	}

	// VCV always has these set; the create_vcv_module() path does not set them
	module->model = model;
	module_widget->setModel(model);

	auto prev_num_elements = model->elements.size();

	module_widget->populate_elements_indices(model);
	model->move_strings();

	if (model->elements.size() != prev_num_elements) {
		// The element vector changed size, so it might have been re-allocated, which invalidates
		// the ModuleInfoView
		pr_warn("Module %s: element count changed from %zu to %zu when populating with a live module\n",
				combined_slug.c_str(),
				prev_num_elements,
				model->elements.size());
	}

	if (MetaModule::ModuleFactory::isValidSlug(combined_slug)) {
		auto &info = MetaModule::ModuleFactory::getModuleInfo(combined_slug);
		info.elements = model->elements;
		info.indices = model->indices;
	} else {
		pr_err("Cannot re-register element data: %s is not a valid slug\n", combined_slug.c_str());
		return false;
	}

	pr_trace("Populated element data for %s (%zu elements)\n", combined_slug.c_str(), model->elements.size());

	return true;
}

} // namespace

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

	// Build a ModuleWidget with no Module, in order to avoid allocating a rack::engine::Module
	auto modulewidget = model->createModuleWidget(nullptr);

	modulewidget->populate_elements_indices(model);
	model->move_strings();

	std::string panelsvg;

	if (modulewidget->getPanel() && modulewidget->getPanel()->svg) {
		panelsvg = modulewidget->getPanel()->svg->filename();
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

	ModuleInfoView info{
		.description = "", .width_hp = 1, .elements = model->elements, .indices = model->indices, .bypass_routes = {}};

	std::string combined_slug = std::string(brand) + ":" + std::string(slug);
	auto is_populated = std::make_shared<bool>(false);

	// Wrapper for model->creation_func(): lazily run populate_element_data() when module is first constructed
	auto create_module = [model, combined_slug, is_populated]() -> std::unique_ptr<CoreProcessor> {
		if (!model->creation_func)
			return nullptr;

		// Temporarily set pluginInstance so paths to assets work
		auto prev_plugin_instance = pluginInstance;
		pluginInstance = model->plugin;

		auto module = model->creation_func();

		pluginInstance = prev_plugin_instance;

		if (module && !*is_populated) {
			populate_element_data(model, combined_slug, module.get());
			*is_populated = true;
		}

		return module;
	};

	ModuleFactory::registerModuleType(brand, slug, create_module, info, panel_filename);

	model->plugin = this;
	models.push_back(model);

	delete modulewidget;
}

Plugin::Plugin()
	: slug{""} {
}

Plugin::Plugin(std::string slug)
	: slug{slug} {
}

Plugin::~Plugin() {
	for (Model *model : models) {
		// In VCV Rack: don't delete model because it's allocated once and referenced by a global.

		// In MetaModule: we need to delete the models when the Plugin is removed
		pr_trace("Deleting Model %s (%p)\n", model->slug.c_str(), model);

		auto removed_ok = MetaModule::ModuleFactory::unregisterModule(slug, model->slug);
		if (!removed_ok) {
			pr_warn("Failed to remove VCV module '%s' in brand '%s'\n", model->slug.c_str(), slug.c_str());
		}
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

void Plugin::fromJson(json_t *rootJ) {
}

void Plugin::modulesFromJson(json_t *rootJ) {
}

} // namespace rack::plugin
