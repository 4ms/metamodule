#pragma once
#include "fs/dir_entry_kind.hh"
#include "fs/volumes.hh"
#include "patch_file/patches_default.hh"
#include "pr_dbg.hh"
#include <cstring>
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

	bool foreach_dir_entry(const std::string_view path, auto action) {
		auto num_patches = DefaultPatches::num_patches();

		for (unsigned i = 0; i < num_patches; i++) {
			auto filename = DefaultPatches::get_filename(i);
			auto filedata = DefaultPatches::get_patch(i);
			action(std::string_view{filename}, 0, filedata.size_bytes(), DirEntryKind::File);
		}

		return true;
	}

	uint64_t read_file(std::string_view filename, std::span<char> buffer, size_t offset = 0) {
		uint64_t sz = 0;
		auto num_patches = DefaultPatches::num_patches();

		if (offset != 0) {
			pr_err("DefaultPatchFileIO::read_file does not support reading partial files\n");
			return 0;
		}

		for (unsigned i = 0; i < num_patches; i++) {
			if (filename.starts_with("/"))
				filename = filename.substr(1);

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
