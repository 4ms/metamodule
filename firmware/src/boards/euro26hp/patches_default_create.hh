#pragma once
#include "console/pr_dbg.hh"
#include "fs/fileio_t.hh"
#include "patches_default.hh"
#include <cstdint>

namespace MetaModule
{

struct DefaultPatchList {

	static bool create_default_patches(FileIoC auto &fileio) {
		for (uint32_t i = 0; i < DefaultPatches::num_patches(); i++) {
			const auto filename = DefaultPatches::get_filename(i);
			auto patch = DefaultPatches::get_patch(i);

			pr_trace("Creating default patch file: %s\n", filename.c_str());

			// Remove trailing null terminator that we get from storing default patches as strings
			if (patch.back() == '\0')
				patch = patch.subspan(0, patch.size() - 1);

			if (!fileio.update_or_create_file(filename, patch)) {
				pr_err("Error: failed to write %d. Aborted creating default patches to flash\n", filename.c_str());
				return false;
			}
		}
		return true;
	}
};

} // namespace MetaModule
