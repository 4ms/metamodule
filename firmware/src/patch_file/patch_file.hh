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
};

} // namespace MetaModule
