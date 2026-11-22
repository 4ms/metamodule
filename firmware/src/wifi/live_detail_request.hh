#pragma once
#include <cstdint>

namespace MetaModule
{

// Tracks whether a Wi-Fi client still wants per-module load measurements.
// Each request bumps a counter; the measurement stays on until no new request
// has arrived for TimeoutMs, so it turns itself off when the client goes away.
class LiveDetailRequest {
public:
	static constexpr uint32_t TimeoutMs = 3000;

	bool update(uint32_t request_count, uint32_t now_ms) {
		if (request_count != last_count) {
			last_count = request_count;
			last_request_ms = now_ms;
			active = true;
		} else if (active && (now_ms - last_request_ms) > TimeoutMs) {
			active = false;
		}
		return active;
	}

private:
	uint32_t last_count = 0;
	uint32_t last_request_ms = 0;
	bool active = false;
};

} // namespace MetaModule
