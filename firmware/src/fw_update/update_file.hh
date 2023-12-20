#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace MetaModule
{

enum class UpdateType { App, WifiFirmware, WifiFilesystem, WifiApp, Invalid };

struct UpdateFile {
	UpdateType type = UpdateType::Invalid;
	std::string filename;
	uint32_t filesize = 0;
	uint32_t md5[4]{};

	struct Version {
		uint8_t major = 0;
		uint8_t minor = 0;
		uint8_t revision = 0;
	} version;
};

struct UpdateManifest {
	uint32_t version{};
	std::vector<UpdateFile> files;
};

} // namespace MetaModule
