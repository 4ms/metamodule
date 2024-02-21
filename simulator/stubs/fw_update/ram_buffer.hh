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

inline std::span<uint8_t> get_ram_buffer_client() {
	return get_ram_buffer().first(5 * 1024 * 1024);
}

inline std::span<uint8_t> get_ram_buffer_server() {
	return get_ram_buffer().last(get_ram_buffer().size() - 5 * 1024 * 1024);
}

} // namespace MetaModule
