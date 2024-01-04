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

} // namespace MetaModule
