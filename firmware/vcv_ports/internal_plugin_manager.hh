#pragma once
#include "internal_plugins.hh"
#include "plugin/Plugin.hpp"
#include <context.hpp>
#include <list>

namespace MetaModule
{

struct InternalPluginManager {
	std::list<rack::plugin::Plugin> internal_plugins;

	InternalPluginManager() {
		load_internal_plugins();
	}

	void load_internal_plugins() {
		rack::contextSet(nullptr);

		pluginInstance = &internal_plugins.emplace_back("listenclosely");
		pluginInstance->addModel(modelListenClosely);
	}
};
} // namespace MetaModule
