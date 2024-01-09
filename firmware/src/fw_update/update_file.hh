#pragma once
#include "util/static_string.hh"
#include <cstdint>
#include <string>
#include <vector>

namespace MetaModule
{

enum class UpdateType { App, WifiFirmware, WifiFilesystem, WifiApp};

struct UpdateFile {
	UpdateType type;
	std::string filename;
	uint32_t filesize = 0;
	StaticString<32> md5{};
};

struct UpdateManifest {
	uint32_t version{};
	std::vector<UpdateFile> files;
};

} // namespace MetaModule
