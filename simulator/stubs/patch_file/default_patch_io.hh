#pragma once
#include "fs/volumes.hh"
#include "patch_file/patches_default.hh"
#include <iostream>
#include <span>
#include <string_view>

struct DefaultPatchFileIO {
	using Volume = MetaModule::Volume;
	const Volume _vol;

	DefaultPatchFileIO(Volume vol_id)
		: _vol{vol_id} {
	}

	bool foreach_file_with_ext(const std::string_view extension, auto action) {
		auto num_patches = DefaultPatches::num_patches();

		for (unsigned i = 0; i < num_patches; i++) {
			auto filename = DefaultPatches::get_filename(i);
			auto filedata = DefaultPatches::get_patch(i);
			action(filename.c_str(), 0, filedata.size_bytes());
		}

		return true;
	}

	uint64_t read_file(const std::string_view filename, std::span<char> buffer) {
		uint64_t sz = 0;
		auto num_patches = DefaultPatches::num_patches();

		for (unsigned i = 0; i < num_patches; i++) {

			if (DefaultPatches::get_filename(i) == filename) {
				const auto file = DefaultPatches::get_patch(i);
				sz = std::min(file.size_bytes(), buffer.size_bytes());
				std::memcpy(buffer.data(), file.data(), sz);
			}
		}

		return sz;
	}

	bool update_or_create_file(const std::string_view filename, const std::span<const char> data) {
		// Not allowed
		return false;
	}

	bool delete_file(std::string_view filename) {
		// Not allowed
		return false;
	}

	void set_file_timestamp(std::string_view filename, uint32_t timestamp) {
		// Not allowed
	}

	std::string_view volname() {
		return "Default Patches";
	}

	Volume vol_id() {
		return _vol;
	}

	bool is_mounted() {
		return true;
	}
};
