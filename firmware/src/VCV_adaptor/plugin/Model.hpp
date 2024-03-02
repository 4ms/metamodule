#pragma once
#include "CoreModules/CoreProcessor.hh"
#include "CoreModules/elements/element_counter.hh"
#include <deque>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace rack
{

namespace app
{
struct ModuleWidget;
}

namespace engine
{
struct Module;
}

namespace plugin
{

struct Plugin;

struct Model {
	std::string slug{};
	Plugin *plugin = nullptr; //weak reference

	std::vector<MetaModule::Element> elements;
	std::vector<ElementCount::Indices> indices;
	std::deque<std::string> string_table;

	// Model() = default;

	virtual ~Model() = default;

	virtual engine::Module *createModule() {
		return nullptr;
	}

	virtual app::ModuleWidget *createModuleWidget(engine::Module *m) {
		return nullptr;
	}
};

} // namespace plugin

} // namespace rack
