#pragma once
#include "ld.h"
#include <cstdint>
#include <span>

namespace MetaModule
{

// non-cachable RAM buffer for loading files
inline std::span<uint8_t> get_ram_buffer() {
	return {reinterpret_cast<uint8_t *>(_FWBUFFER), FWBUFFER_SZ};
}

} // namespace MetaModule
