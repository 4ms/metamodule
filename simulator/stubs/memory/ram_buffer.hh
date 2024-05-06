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

class OneTimeArenaAllocator {
public:
	OneTimeArenaAllocator(std::span<uint8_t> arena_)
		: arena(arena_)
		, offset(0) {
	}

	uint8_t *allocate(std::size_t size) {
		auto bytesRemaining = arena.size() - offset;
		if (bytesRemaining > size) {
			auto result = &arena[offset];
			offset += size;

			return result;
		} else {
			return nullptr;
		}
	}

	void reset() {
		offset = 0;
	}

private:
	std::span<uint8_t> arena;
	std::size_t offset;
};

} // namespace MetaModule
