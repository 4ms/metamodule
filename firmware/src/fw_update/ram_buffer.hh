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

inline std::span<uint8_t> get_ram_buffer_client() {
	return get_ram_buffer().first(5 * 1024 * 1024);
}

inline std::span<uint8_t> get_ram_buffer_server() {
	return get_ram_buffer().last(get_ram_buffer().size() - 5 * 1024 * 1024);
}

class OneTimeArenaAllocator
{
public:
	OneTimeArenaAllocator(std::span<uint8_t> arena_) : arena(arena_), offset(0) {}

	uint8_t* allocate(std::size_t size)
	{
		auto bytesRemaining = arena.size() - offset;
		if (bytesRemaining > size)
		{
			auto result = &arena[offset];
			offset += size;

			return result;
		}
		else
		{
			return nullptr;
		}
	}

private:
	std::span<uint8_t> arena;
	std::size_t offset;
};

} // namespace MetaModule
