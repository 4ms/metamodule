#pragma once
#include "plugin/Plugin.hpp"
#include <cstdint>
#include <span>
#include <vector>

struct DynLoader {

	DynLoader(std::span<uint8_t> elf_file_data, std::vector<uint8_t> &code_buffer) {
	}

	std::string load() {
		printf("Plugin was loaded and symbols resolved\n");
		return "";
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
