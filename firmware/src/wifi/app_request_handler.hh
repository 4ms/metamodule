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

#ifdef ENABLE_WIFI_BRIDGE
		if (message.message_type == RequestWifiIP) {
			IntercoreStorageMessage result;

			if (auto endpoint = WifiInterface::getCurrentIP(); endpoint) {
				WifiEndpoint epToSend;
				std::copy(endpoint->ip.begin(), endpoint->ip.end(), epToSend.ip.begin());
				epToSend.port = endpoint->port;

				result.wifi_ip_result = epToSend;
				result.message_type = WifiIPSuccess;
			} else {
				switch (endpoint.error()) {
					case WifiInterface::ErrorCode_t::NO_ANSWER:
						result.wifi_ip_result = std::unexpected(WifiIPError::NO_MODULE_CONNECTED);
						result.message_type = WifiIPSuccess;
						break;
					case WifiInterface::ErrorCode_t::NO_IP:
						result.wifi_ip_result = std::unexpected(WifiIPError::NO_IP);
						result.message_type = WifiIPSuccess;
						break;
					default:
						result.message_type = WifiIPFailed;
						break;
				}
			}

			return result;
		}
#endif
		return std::nullopt;
	}
};

} // namespace MetaModule
