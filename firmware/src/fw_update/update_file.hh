#pragma once
#include "util/static_string.hh"
#include <cstdint>
#include <string>
#include <vector>
#include <optional>

namespace MetaModule
{

enum class UpdateType { App, Wifi};

struct UpdateFile {
	UpdateType type;
	std::string filename;
	uint32_t filesize = 0;
	std::optional<StaticString<32>> md5;
	uint32_t address;
};

struct UpdateManifest {
	uint32_t version{};
	std::vector<UpdateFile> files;
};

} // namespace MetaModule
