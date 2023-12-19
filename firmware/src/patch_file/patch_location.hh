#pragma once
#include "fs/volumes.hh"
#include <cstdint>

namespace MetaModule
{

struct PatchLocation {
	uint32_t index{0};
	Volume vol{};

	bool operator==(PatchLocation const &other) const {
		return index == other.index && vol == other.vol;
	}
};

} // namespace MetaModule
