#pragma once
#include "util/static_string.hh"
#include "volumes.hh"
#include <span>

namespace MetaModule
{
struct PatchFile {
	std::string filename;
	uint32_t filesize;
	uint32_t timestamp;
	StaticString<31> patchname;
};

// using PatchFileList = std::array<std::span<PatchFile>, static_cast<unsigned>(Volume::MaxVolumes)>;
struct PatchFileList {
	std::span<const PatchFile> usb;
	std::span<const PatchFile> sdcard;
	std::span<const PatchFile> norflash;
};

} // namespace MetaModule
