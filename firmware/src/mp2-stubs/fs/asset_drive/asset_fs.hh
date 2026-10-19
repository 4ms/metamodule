#pragma once
#include "fs/asset_drive/uimg_header.hh"
#include "pr_dbg.hh"
#include <cstdint>
#include <cstring>
#include <vector>

extern "C" const char assets_image[];	  // core_a35/assets_image.S
extern "C" const char assets_image_end[]; // core_a35/assets_image.S

namespace MetaModule
{

// STUB: stands in for src/fs/asset_drive/asset_fs.hh, which reads the assets image (module
// faceplates, fonts, etc) from NOR flash. MP2 doesn't have an OSPI flash driver yet, so the
// assets image is embedded in the firmware image instead (core_a35/assets_image.S).
// If there's no valid image, there are no assets: the GUI works, but without module images.
struct AssetFS {
	AssetFS(uint32_t flash_address) {
	}

	std::vector<char> read_image() {
		auto image_size = size_t(assets_image_end - assets_image);
		if (image_size < sizeof(Uimg::image_header)) {
			pr_err("No assets image in the firmware image (see MP2_ASSETS_UIMG in cmake/mp2.cmake)\n");
			return {};
		}

		Uimg::image_header header;
		memcpy(&header, assets_image, sizeof header);

		auto magic = Uimg::be32_to_cpu(header.ih_magic);
		if (magic != Uimg::IH_MAGIC) {
			pr_err("Embedded assets image has no valid uimg header. Magic found = %x\n", magic);
			return {};
		}

		auto tar_image_size = Uimg::be32_to_cpu(header.ih_size);
		if (tar_image_size > image_size - sizeof header) {
			pr_err("Embedded assets image is an invalid size: %u\n", unsigned(tar_image_size));
			return {};
		}

		auto *tar = assets_image + sizeof header;
		return std::vector<char>(tar, tar + tar_image_size);
	}
};

} // namespace MetaModule
