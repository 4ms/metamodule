#pragma once
#include <array>
#include <cstdint>
#include <span>

namespace MetaModule
{

// non-cachable RAM buffer for loading files
inline std::span<uint8_t> get_ram_buffer() {
	static std::array<uint8_t, 1024 * 1024 * 16> buffer;
	return buffer;
}

} // namespace MetaModule
