#pragma once

#include <span>
#include <cstdint>

namespace MetaModule
{

struct WifiInterface {
	static void init();

	static void run();

	static void handle_received_frame(std::span<uint8_t>);
	static void send_frame(std::span<uint8_t>);

private:
};
} // namespace MetaModule
