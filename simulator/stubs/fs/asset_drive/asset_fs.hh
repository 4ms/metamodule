#pragma once
#include "fs/asset_drive/uimg_header.hh"
#include "pr_dbg.hh"
#include <fstream>
#include <string_view>
#include <vector>

namespace MetaModule
{

struct AssetFS {
	std::string image_path;

	AssetFS(std::string_view image_path)
		: image_path{image_path} {
	}

	std::vector<char> read_image() {
		std::vector<char> raw_image;

		std::ifstream ifs(image_path, std::ios::in);

		if (ifs.is_open()) {
			// Find file size, minus header
			ifs.seekg(0, std::ios::end);
			uint64_t sz = ifs.tellg();
			sz -= sizeof(Uimg::image_header);
			ifs.seekg(0, std::ios::beg);

			// Verify uimg header
			Uimg::image_header header;
			ifs.read(reinterpret_cast<char *>(&header), sizeof(header));

			if (Uimg::be32_to_cpu(header.ih_magic) == Uimg::IH_MAGIC) {
				raw_image.resize(sz);
				ifs.read(raw_image.data(), sz);
				ifs.close();
				printf("Raw image is %zu, first byte is %x\n", raw_image.size(), raw_image[0]);
			} else
				pr_err("No uimg magic word found, not a valid uimg header\n");

		} else
			pr_err("Error %s not opened\n", image_path.data());

		return raw_image;
	}
};

} // namespace MetaModule
