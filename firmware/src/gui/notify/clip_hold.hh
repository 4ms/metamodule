#pragma once
#include <array>
#include <cstdint>

namespace MetaModule
{

// Per-output hold timers for clip indicators.
// Each set bit in `mask` keeps output i lit until HoldMs after the latest update.
template<unsigned N>
struct ClipHold {
	static_assert(N <= 32, "mask is a uint32_t");
	static constexpr uint32_t HoldMs = 500;

	void update(uint32_t mask, uint32_t now_ms) {
		for (unsigned i = 0; i < N; i++) {
			if (mask & (1u << i)) {
				last_hit[i] = now_ms;
				active[i] = true;
			} else if (active[i] && !is_lit(i, now_ms)) {
				// Retire expired slots so a stale timestamp can't light up again when the tick counter wraps
				active[i] = false;
			}
		}
	}

	bool is_lit(unsigned i, uint32_t now_ms) const {
		if (i >= N || !active[i])
			return false;
		// Unsigned subtraction is wraparound-safe
		return (now_ms - last_hit[i]) < HoldMs;
	}

private:
	std::array<uint32_t, N> last_hit{};
	std::array<bool, N> active{};
};

} // namespace MetaModule
