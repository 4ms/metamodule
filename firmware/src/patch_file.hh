#pragma once
#include "util/static_string.hh"
#include "volumes.hh"

namespace MetaModule
{
struct PatchFile {
	Volume volume;
	std::string filename;
	uint32_t filesize;
	uint32_t timestamp;
	StaticString<31> patchname;
};

} // namespace MetaModule
