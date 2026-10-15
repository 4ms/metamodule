#pragma once
#include <array>
#include <cstdint>
#include <expected>
#include <type_traits>

namespace MetaModule
{

enum WifiIPError : uint8_t {
	NO_MODULE_CONNECTED,
	NO_IP,
	INTERNAL_ERROR,
};

struct WifiEndpoint {
	std::array<uint8_t, 4> ip;
	uint16_t port;
};

using WifiIPResult = std::expected<WifiEndpoint, WifiIPError>;

// Fixed-layout stand-in for WifiIPResult in structs that cross the core
// boundary (std::expected is neither trivially copyable nor ABI-pinned).
// Converts implicitly to/from WifiIPResult so call sites are unchanged.
struct InterCoreWifiIPResult {
	WifiEndpoint endpoint{};
	WifiIPError error{};
	uint8_t has_endpoint{}; // 1 = endpoint valid, 0 = error valid

	InterCoreWifiIPResult() = default;

	InterCoreWifiIPResult(const WifiIPResult &r) {
		*this = r;
	}

	InterCoreWifiIPResult &operator=(const WifiIPResult &r) {
		if (r.has_value()) {
			endpoint = *r;
			error = {};
			has_endpoint = 1;
		} else {
			endpoint = {};
			error = r.error();
			has_endpoint = 0;
		}
		return *this;
	}

	operator WifiIPResult() const {
		if (has_endpoint)
			return endpoint;
		return std::unexpected(error);
	}
};

static_assert(sizeof(InterCoreWifiIPResult) == 8);
static_assert(std::is_trivially_copyable_v<InterCoreWifiIPResult>);

} // namespace MetaModule
