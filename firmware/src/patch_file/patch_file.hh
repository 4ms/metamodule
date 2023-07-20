#pragma once
#include "util/static_string.hh"
#include <span>
#include <string>

namespace MetaModule
{
struct PatchFile {
	std::string filename;
	uint32_t filesize;
	uint32_t timestamp;
	StaticString<31> patchname;
};

struct PatchFileList {
	std::span<const PatchFile> usb;
	std::span<const PatchFile> sdcard;
	std::span<const PatchFile> norflash;
};

} // namespace MetaModule
