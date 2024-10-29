#pragma once
#include <array>
#include <cstdint>
#include <expected>

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

} // namespace MetaModule
