#pragma once
#include "dynload/loaded_plugin.hh"
#include "metamodule-plugin-sdk/version.hh"
#include "plugin/Plugin.hpp"
#include <cstdint>
#include <optional>
#include <span>

// STUB: stands in for src/dynload/dynloader.hh, which loads MP1's 32-bit ARM plugin ELFs.
// MP2 can't run those: it needs AArch64 plugins (and a loader for them). Until then, plugins
// "load" but register no modules (same as the simulator's stub).
struct DynLoader {

	template<typename BufferT>
	DynLoader(std::span<uint8_t> elf_file_data, BufferT &code_buffer) {
	}

	std::string load() {
		return "Plugins are not supported on MP2 yet";
	}

	std::optional<MetaModule::Version> get_sdk_version() {
		return MetaModule::sdk_version();
	}

	MetaModule::PluginFiniArray fini_array() const {
		return {};
	}

	template<typename PluginInitFunc>
	PluginInitFunc *find_init_func() {
		return init_plugin;
	}

	static void init_plugin(rack::plugin::Plugin *) {
	}
};
