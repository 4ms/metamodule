#pragma once
#include "util/static_string.hh"
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace MetaModule
{

enum class UpdateType { App, Wifi };

struct UpdateFile {
	UpdateType type;
	std::string filename;
	uint32_t filesize = 0;
	std::optional<uint32_t> uncompressed_size;
	std::optional<StaticString<32>> md5;
	uint32_t address;
	std::string name;
};

struct UpdateManifest {
	uint32_t version{};
	std::vector<UpdateFile> files;
};

} // namespace MetaModule
