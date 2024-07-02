#pragma once

#include <span>
#include <cstdint>
#include <optional>
#include <patch_file/patch_storage.hh>

namespace MetaModule::WifiInterface
{
	void init(PatchStorage*);

	void run();
	void start();
	void stop();

	void handle_received_frame(uint8_t, std::span<uint8_t>);

	void send_heartbeat();
	using IPAddress_t = std::array<uint8_t,4>;

	std::optional<IPAddress_t> getCurrentIP();
};