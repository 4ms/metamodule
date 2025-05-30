#pragma once
#include "fs/volumes.hh"
#include "patch/module_type_slug.hh"
#include <cstdint>
#include <optional>
#include <string>
#include <string_view>

namespace MetaModule
{
struct PatchFile {
	std::string filename;
	uint32_t filesize;
	uint32_t timestamp;
	PatchName patchname;
	std::optional<Volume> link_vol;

	PatchFile(std::string_view filename,
			  uint32_t filesize,
			  uint32_t timestamp,
			  std::string_view patchname,
			  std::optional<Volume> link_vol = std::nullopt)
		: filename{filename}
		, filesize{filesize}
		, timestamp{timestamp}
		, patchname{patchname}
		, link_vol{link_vol} {
	}
};

} // namespace MetaModule
