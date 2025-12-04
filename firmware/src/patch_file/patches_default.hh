#pragma once
#include "util/static_string.hh"
#include <cstdint>
#include <span>

struct DefaultPatches {

	static inline std::array<std::span<const char>, 0> patch_raw_data = {};

	static inline std::array<StaticString<63>, 0> patch_filenames = {};

	static constexpr uint32_t num_patches() {
		return patch_raw_data.size();
	}

	static std::span<const char> get_patch(uint32_t id) {
		if (id >= patch_raw_data.size())
			return {};
		return {patch_raw_data[id].data(), patch_raw_data[id].size_bytes()};
	}

	static auto get_filename(uint32_t id) {
		if (id < patch_filenames.size())
			return patch_filenames[id];
		else {
			StaticString<63> s;
			s._data[0] = ((id / 10) % 10) + '0';
			s._data[1] = (id % 10) + '0';
			s._data[2] = '.';
			s._data[3] = 'y';
			s._data[4] = 'm';
			s._data[5] = 'l';
			s._data[6] = '\0';
			return s;
		}
	}
};
