#pragma once
#include <cstdint>
#include <span>
#include <vector>

struct DynLoader {

	DynLoader(std::span<uint8_t> elf_file_data, std::vector<uint8_t> &code_buffer) {
	}

	bool load() {
		return false;
	}

	template<typename PluginInitFunc>
	PluginInitFunc *find_init_func() {
		return nullptr;
	}
};
