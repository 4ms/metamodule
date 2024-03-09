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

			raw_image.resize(sz);
			ifs.read(raw_image.data(), sz);
			ifs.close();
			printf("Raw image is %zu, first byte is %x\n", raw_image.size(), raw_image[0]);
		} else
			printf("Error %s not opened\n", image_path.data());
	}

	void release() {
		raw_image.clear();
		raw_image.shrink_to_fit();
	}
};

} // namespace MetaModule
