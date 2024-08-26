#include <chrono>
#include <cstdint>

namespace SamplerKit
{
uint32_t get_time() {
	const auto start{std::chrono::steady_clock::now()};
	auto tm = start.time_since_epoch().count() / 1'000'000;
	return tm;
}
} // namespace SamplerKit
