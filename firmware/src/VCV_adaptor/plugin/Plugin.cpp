#include "VCV_adaptor/plugin/Plugin.hpp"
#include "CoreModules//moduleFactory.hh"

namespace MetaModule
{

template<typename ModuleT>
std::unique_ptr<CoreProcessor> create_vcv_module() {
	return std::make_unique<ModuleT>();
}

} // namespace MetaModule

namespace rack::plugin
{

void Plugin::addModel(Model *model) {
	auto module = model->createModule();
	auto modulewidget = model->createModuleWidget(module);

	using namespace MetaModule;

	ModuleFactory::registerModuleType(slug, model->create_vcv_module);

	model->plugin = this;
	models.push_back(model);
}

Plugin::~Plugin() {
	for (Model *model : models) {
		model->plugin = nullptr;
		// Don't delete model because it's allocated once and referenced by a global.
		// TODO: is the right behavior for MetaModule?
	}
}

} // namespace rack::plugin
