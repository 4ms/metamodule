#pragma once
#include "CoreModules/CoreProcessor.hh"
#include "CoreModules/moduleFactory.hh"
#include "VCV_adaptor/app/ModuleWidget.hpp"
#include "VCV_adaptor/plugin/Model.hpp"
#include <string_view>

namespace rack
{

template<typename ModuleT>
std::unique_ptr<CoreProcessor> create_vcv_module() {
	return std::make_unique<ModuleT>();
}

// Allocates and constructs a Model that can
// create the given Module and ModuleWidget subclasses
// To match VCV Rack API, ownership of the Model is passed to the caller.
template<class ModuleT, class ModuleWidgetT>
requires(std::derived_from<ModuleWidgetT, rack::ModuleWidget>) && (std::derived_from<ModuleT, rack::engine::Module>)

plugin::Model *createModel(std::string_view slug) {

	MetaModule::ModuleFactory::registerModuleType(slug, create_vcv_module<ModuleT>);

	struct ModelT : plugin::Model {

		rack::engine::Module *createModule() override {
			engine::Module *m = new ModuleT;
			m->model = this;
			return m;
		}

		/*app::*/ ModuleWidget *createModuleWidget(engine::Module *m) override {
			auto tm = static_cast<ModuleT *>(m);
			/*app::*/ ModuleWidget *mw = new ModuleWidgetT(tm);
			mw->setModule(m);
			mw->setModel(this);
			return mw;
		}
	};

	plugin::Model *model = new ModelT;
	model->slug = slug;
	return model;
}

} // namespace rack

// using namespace rack;
