#pragma once
#include "core_intercom/intercore_message.hh"
#include "drivers/inter_core_comm.hh"
#include "wifi_interface.hh"
#include <optional>

namespace MetaModule
{

struct WifiAppRequestHandler {

	using enum IntercoreStorageMessage::MessageType;

	std::optional<IntercoreStorageMessage> handle_message(const IntercoreStorageMessage &message) {

		if (message.message_type == RequestWifiIP) {
			return get_ip(message.buffer);
		}

		return std::nullopt;
	}

private:
	IntercoreStorageMessage get_ip(std::span<char> buffer) {
#ifdef ENABLE_WIFI_BRIDGE

		auto addr = WifiInterface::getCurrentIP();

		if (addr.has_value()) {
			buffer[0] = (*addr)[0];
			buffer[1] = (*addr)[1];
			buffer[2] = (*addr)[2];
			buffer[3] = (*addr)[3];
			return IntercoreStorageMessage{.message_type = WifiIPSuccess};

		} else {
			return {.message_type = WifiIPFailed};
		}

#endif
	}
};

} // namespace MetaModule
