#pragma once
#include <array>
#include <cstdint>

namespace MetaModule
{

// Per-output hold timers for clip indicators.
// Each set bit in `mask` keeps output i lit until HoldMs after the latest update.
template<unsigned N>
struct ClipHold {
	static constexpr uint32_t HoldMs = 500;

	void update(uint32_t mask, uint32_t now_ms) {
		for (unsigned i = 0; i < N && i < 32; i++) {
			if (mask & (1u << i)) {
				last_hit[i] = now_ms;
				ever_hit[i] = true;
			}
		}
	}

	bool is_lit(unsigned i, uint32_t now_ms) const {
		if (i >= N || !ever_hit[i])
			return false;
		// Unsigned subtraction is wraparound-safe
		return (now_ms - last_hit[i]) < HoldMs;
	}

private:
	std::array<uint32_t, N> last_hit{};
	std::array<bool, N> ever_hit{};
};

} // namespace MetaModule
