#pragma once
#include "metamodule-plugin-sdk/version.hh"
#include "plugin/Plugin.hpp"
// #include <chrono>
#include <cstdint>
#include <optional>
#include <span>
// #include <thread>
#include <vector>

struct DynLoader {

	DynLoader(std::span<uint8_t> elf_file_data, std::vector<uint8_t> &code_buffer) {
	}

	std::string load() {
		// using namespace std::chrono_literals;
		// std::this_thread::sleep_for(2000ms);
		printf("Plugin was loaded and symbols resolved\n");
		return "";
	}

	std::optional<MetaModule::Version> get_sdk_version() {
		// using namespace std::chrono_literals;
		// std::this_thread::sleep_for(1000ms);
		printf("Pretending plugin has same version as firmware\n");
		return MetaModule::sdk_version();
	}

	template<typename PluginInitFunc>
	PluginInitFunc *find_init_func() {
		return init_plugin;
	}

	static void init_plugin(rack::plugin::Plugin *) {
		printf("Plugin init_plugin was called\n");
		//TODO: push a rack::Model to the Plugin
		return;
	}
};
