#pragma once
#include "CoreModules/CoreProcessor.hh"
#include <memory>
#include <string>

namespace rack
{

//namespace app {
struct ModuleWidget;
//}

namespace engine
{
struct Module;
}

namespace plugin
{

struct Plugin;

struct Model {
	std::string slug{};
	Plugin *plugin;

	virtual ~Model() = default;

	virtual engine::Module *createModule() {
		return nullptr;
	}

	virtual /*app::*/ ModuleWidget *createModuleWidget(engine::Module *m) {
		return nullptr;
	}

	virtual std::unique_ptr<CoreProcessor> create_vcv_module() {
		return nullptr;
	}
};

} // namespace plugin

} // namespace rack
