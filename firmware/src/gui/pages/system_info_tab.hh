#pragma once
#include "drivers/cache.hh"
#include "git_version.h"
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/system_menu_tab_base.hh"
#include "gui/slsexport/meta5/ui.h"
#include "patch_file/file_storage_proxy.hh"
#include <malloc.h>

namespace MetaModule
{

struct InfoTab : SystemMenuTab {

	InfoTab(FileStorageProxy &storage)
		: storage{storage} {
		lv_label_set_text(ui_SystemMenuExpanders, "No wifi module found");
	}

	void prepare_focus(lv_group_t *group) override {
		this->group = group;

		std::string_view fw_version = GIT_FIRMWARE_VERSION_TAG;
		if (fw_version.starts_with("firmware-"))
			fw_version.remove_prefix(9);

		struct mallinfo mi = mallinfo();
		pr_info("arena    (total space allocated from system): %zu\n", mi.arena);
		pr_info("ordblks  (number of non-inuse chunks) %zu\n", mi.ordblks);
		pr_info("smblks   (unused -- always zero) %zu\n", mi.smblks);
		pr_info("hblks    (number of mmapped regions) %zu\n", mi.hblks);
		pr_info("hblkhd   (total space in mmapped regions) %zu\n", mi.hblkhd);
		pr_info("uordblks (total allocated space) %zu\n", mi.uordblks);
		pr_info("fordblks (total non-inuse space) %zu\n", mi.fordblks);
		pr_info("keepcost (top-most, releasable (via malloc_trim) space */ %zu\n", mi.keepcost);

		lv_label_set_text_fmt(ui_SystemMenuFWversion,
							  "Firmware version: %s\nMemory (kB): %zu/%zu (%2f%%)",
							  fw_version.data(),
							  mi.uordblks / 1024,
							  mi.arena / 1024,
							  float(100 * mi.uordblks / mi.arena));

		wifi_ip_state = WifiIPState::Idle;
	}

	void update() override {
		update_wifi_ip();
	}

	void update_wifi_ip() {
		switch (wifi_ip_state) {

			case WifiIPState::Idle: {
				uint32_t now = lv_tick_get();
				if (now - last_check_wifi_ip_tm > 1000) { //poll media once per second

					last_check_wifi_ip_tm = now;

					if (storage.request_wifi_ip()) {
						wifi_ip_state = WifiIPState::Requested;
					}
				}
			} break;

			case WifiIPState::Requested: {
				auto message = storage.get_message();

				if (message.message_type == FileStorageProxy::WifiIPSuccess) {

					lv_show(ui_SystemMenuExpanders);

					if (message.wifi_ip_result) {

						auto &newEndpoint = *message.wifi_ip_result;

						pr_trace("Got Wifi IP: %u.%u.%u.%u:%U\n",
								 newEndpoint.ip[0],
								 newEndpoint.ip[1],
								 newEndpoint.ip[2],
								 newEndpoint.ip[3],
								 newEndpoint.port);

						if (newEndpoint.port != 80) {
							// only display port when it is non-default
							lv_label_set_text_fmt(ui_SystemMenuExpanders,
												  "Wifi: http://%u.%u.%u.%u:%u",
												  newEndpoint.ip[0],
												  newEndpoint.ip[1],
												  newEndpoint.ip[2],
												  newEndpoint.ip[3],
												  newEndpoint.port);
						} else {
							lv_label_set_text_fmt(ui_SystemMenuExpanders,
												  "Wifi: http://%u.%u.%u.%u",
												  newEndpoint.ip[0],
												  newEndpoint.ip[1],
												  newEndpoint.ip[2],
												  newEndpoint.ip[3]);
						}

					} else {

						switch (message.wifi_ip_result.error()) {

							case IntercoreStorageMessage::WifiIPError::NO_MODULE_CONNECTED:
								lv_label_set_text(ui_SystemMenuExpanders, "No wifi module found");
								break;

							case IntercoreStorageMessage::WifiIPError::NO_IP:
								lv_label_set_text(ui_SystemMenuExpanders,
												  "Wifi module not connected\n to a wifi network");
								break;
						}
					}

					wifi_ip_state = WifiIPState::Idle;

				} else if (message.message_type == FileStorageProxy::WifiIPFailed) {
					lv_show(ui_SystemMenuExpanders);
					lv_label_set_text(ui_SystemMenuExpanders, "Wifi module: Internal Error");

					wifi_ip_state = WifiIPState::Idle;
				}

			} break;
		}
	}

private:
	FileStorageProxy &storage;
	lv_group_t *group = nullptr;

	enum WifiIPState { Idle, Requested } wifi_ip_state = WifiIPState::Idle;
	uint32_t last_check_wifi_ip_tm = 0;
};
} // namespace MetaModule
