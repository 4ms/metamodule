#pragma once
#include <string>

namespace rack::plugin
{

struct ModuleWidget;

namespace engine
{
struct Module;
}

struct Model {
	std::string slug{};

	virtual ~Model() = default;

	virtual engine::Module *createModule() {
		return nullptr;
	}

	virtual /*app::*/ ModuleWidget *createModuleWidget(engine::Module *m) {
		return nullptr;
	}
};

} // namespace rack::plugin
