#pragma once
#include "patch_file/file_storage_proxy.hh"
#include "wifi/wifi_result_t.hh"

namespace MetaModule::WifiInterface
{

struct DetectExpander {

	DetectExpander(FileStorageProxy &storage)
		: storage{storage} {
	}

	void start() {
		wifi_ip_state = WifiIPState::Idle;
	}

	bool new_wifi_status_available(uint32_t now) {
		switch (wifi_ip_state) {

			case WifiIPState::Idle: {
				if (now - last_check_wifi_ip_tm > 1000) { //poll once per second
					last_check_wifi_ip_tm = now;

					if (storage.request_wifi_ip()) {
						wifi_ip_state = WifiIPState::Requested;
					}
				}
			} break;

			case WifiIPState::Requested: {
				auto message = storage.get_message();

				if (message.message_type == FileStorageProxy::WifiIPSuccess) {
					result = message.wifi_ip_result;
					wifi_ip_state = WifiIPState::Idle;

					// Log IP to console:
					if (result) {
						pr_trace("Got Wifi IP: %u.%u.%u.%u:%U\n",
								 result->ip[0],
								 result->ip[1],
								 result->ip[2],
								 result->ip[3],
								 result->port);
					}
					return true;

				} else if (message.message_type == FileStorageProxy::WifiIPFailed) {
					wifi_ip_state = WifiIPState::Idle;
					return true;
				}

			} break;
		}
		return false;
	}

	WifiIPResult get_status() {
		return result;
	}

private:
	FileStorageProxy &storage;

	enum WifiIPState { Idle, Requested } wifi_ip_state = WifiIPState::Idle;

	uint32_t last_check_wifi_ip_tm = 0;

	WifiIPResult result{};
};
} // namespace MetaModule::WifiInterface
