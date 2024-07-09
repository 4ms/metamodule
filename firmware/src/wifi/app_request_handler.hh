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
		if (message.message_type == RequestWifiIP)
		{
			IntercoreStorageMessage result;

			if (auto addr = WifiInterface::getCurrentIP(); addr)
			{
				IntercoreStorageMessage::IPAddr_t ip;
				std::copy(addr->begin(), addr->end(), ip.begin());

				result.wifi_ip_result = ip;
				result.message_type = WifiIPSuccess;
			}
			else
			{
				switch (addr.error())
				{
					case WifiInterface::ErrorCode_t::NO_ANSWER:
						result.wifi_ip_result = std::unexpected(IntercoreStorageMessage::WifiIPError::NO_MODULE_CONNECTED);
						result.message_type = WifiIPSuccess;
						break;
					case WifiInterface::ErrorCode_t::NO_IP:
						result.wifi_ip_result = std::unexpected(IntercoreStorageMessage::WifiIPError::NO_IP);
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
