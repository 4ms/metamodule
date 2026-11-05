#pragma once
#include "CoreModules/moduleFactory.hh"
#include <string>
#include <string_view>
#include <vector>

namespace MetaModule::PluginRegistrationCheck
{

// Records each module registered while a plugin is being loaded (from its static
// constructors and from init()), so the loader can check that the brand and module
// slugs match the plugin's plugin.json/plugin-mm.json, and can remove them on unload.
//
// This sees every registration: native plugins' register_module() and VCV-style
// plugins' Plugin::addModel() both end up in ModuleFactory::registerModuleType().
// Built-in modules register during static initialization, before any plugin loads.

struct Registration {
	std::string brand;
	std::string module_slug;
};

// Records registrations while it's in scope. Only one plugin is loaded at a time.
struct Recorder {
	Recorder() {
		ModuleFactory::setRegistrationObserver([this](std::string_view brand, std::string_view module_slug) {
			recorded.push_back({std::string{brand}, std::string{module_slug}});
		});
	}

	~Recorder() {
		ModuleFactory::setRegistrationObserver({});
	}

	Recorder(Recorder const &) = delete;
	Recorder &operator=(Recorder const &) = delete;

	std::vector<Registration> const &registrations() const {
		return recorded;
	}

private:
	std::vector<Registration> recorded;
};

} // namespace MetaModule::PluginRegistrationCheck
