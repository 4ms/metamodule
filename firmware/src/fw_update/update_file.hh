#pragma once
#include <cstdint>
#include <string>

namespace MetaModule
{

enum class UpdateType { App, Wifi, Invalid };

struct UpdateFile {
	UpdateType type;
	std::string filename;
	uint32_t filesize;
	uint32_t md5[4];
};

} // namespace MetaModule
