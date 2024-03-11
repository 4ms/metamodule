#pragma once
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

		return raw_image;
	}
};

} // namespace MetaModule
