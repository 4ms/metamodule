#pragma once
#include "CoreModules/module_type_slug.hh"
#include "util/static_string.hh"
#include <span>
#include <string>

namespace MetaModule
{
struct PatchFile {
	std::string filename;
	uint32_t filesize;
	uint32_t timestamp;
	PatchName patchname;

	PatchFile(std::string_view filename, uint32_t filesize, uint32_t timestamp, std::string_view patchname)
		: filename{filename}
		, filesize{filesize}
		, timestamp{timestamp}
		, patchname{patchname} {
	}
};

} // namespace MetaModule
