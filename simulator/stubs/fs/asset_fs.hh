#pragma once
#include "patch_file/host_file_io.hh"

namespace MetaModule
{

struct AssetFS {
	std::vector<char> raw_image;

	AssetFS(std::string_view image_path) {
		std::ifstream ifs(image_path, std::ios::in);
		if (ifs.is_open()) {
			// Find file size
			ifs.seekg(0, std::ios::end);
			uint64_t sz = ifs.tellg();

			ifs.seekg(0, std::ios::beg);

			raw_image.reserve(sz);
			ifs.read(raw_image.data(), sz);
			ifs.close();
		}
	}
};

} // namespace MetaModule
