#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace MetaModule
{

struct MidiPCPatchLoadSettings {
	struct Entry {
		std::string path;
		uint32_t channel{1}; // 1-16, 0 = any/omni
		uint32_t pc{0};      // 0-127
	};

	bool enabled{false};
	std::vector<Entry> entries;

	void make_valid() {
		for (auto &e : entries) {
			if (e.channel > 16)
				e.channel = 0;
			if (e.pc > 127)
				e.pc = 0;
		}
	}
};

} // namespace MetaModule
