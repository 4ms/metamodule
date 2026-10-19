#pragma once
#include <cstdint>
#include <span>

namespace MetaModule
{

namespace StaticBuffers
{
// In shared memory (src/core_a35/static_buffers.cc), since the M33 reads files into it
extern std::span<uint8_t> fw_buffer;
} // namespace StaticBuffers

// MP2 version of src/memory/ram_buffer.hh: the non-cacheable buffer for loading files.
// (MP1 uses its FW buffer region)
inline std::span<uint8_t> get_ram_buffer() {
	return StaticBuffers::fw_buffer;
}

} // namespace MetaModule
