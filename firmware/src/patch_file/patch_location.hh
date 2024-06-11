#pragma once
#include "fs/volumes.hh"
#include "util/static_string.hh"

namespace MetaModule
{

struct PatchLocation {
	StaticString<255> filename;
	Volume vol{Volume::RamDisk};

	bool operator==(PatchLocation const &that) const = default;
};

struct PatchLocHash {
	uint32_t filehash{};

	PatchLocHash() = default;

	PatchLocHash(PatchLocation const &loc)
		: filehash{hash(loc.filename, loc.vol)} {
	}

	PatchLocHash(std::string_view filename, Volume vol)
		: filehash{hash(filename, vol)} {
	}

	static uint32_t hash(std::string_view fname, Volume vol) {
		uint32_t h = 0x811C9DC5;
		for (auto c : fname)
			h = (h * 0x01000193) ^ c;

		h = (h * 0x01000193) ^ (static_cast<char>(vol) + 1);
		return h;
	}

	bool operator==(PatchLocHash const &that) const = default;
};

} // namespace MetaModule
