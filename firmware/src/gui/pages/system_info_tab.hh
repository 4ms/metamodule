#pragma once
#include "drivers/cache.hh"
#include "git_version.h"
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/system_menu_tab_base.hh"
#include "gui/slsexport/meta5/ui.h"
#include "memory/ram_buffer.hh"
#include "patch_file/file_storage_proxy.hh"
#include "util/monotonic_allocator.hh"

namespace MetaModule
{

struct InfoTab : SystemMenuTab {

	InfoTab(FileStorageProxy &storage)
		: storage{storage}
		, allocator{get_ram_buffer()} {
	}

	void prepare_focus(lv_group_t *group) override {
		this->group = group;

		std::string_view fw_version = GIT_FIRMWARE_VERSION_TAG;
		if (fw_version.starts_with("firmware-"))
			fw_version.remove_prefix(9);

		lv_label_set_text_fmt(ui_SystemMenuFWversion, "Firmware version: %s", fw_version.data());

		allocator.reset();
		if (auto mem_ptr = allocator.allocate(sizeof(IpAddr)); mem_ptr) {
			wifi_ip_ptr = new (mem_ptr) IpAddr;
			wifi_ip_state = WifiIPState::Idle;
		} else
			wifi_ip_state = WifiIPState::NoMemory;
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

					if (storage.request_wifi_ip(*wifi_ip_ptr)) {
						wifi_ip_state = WifiIPState::Requested;
					}
				}
			} break;

			case WifiIPState::Requested: {
				auto message = storage.get_message().message_type;

				if (message == FileStorageProxy::WifiIPSuccess) {
					auto &wifi_ip = *wifi_ip_ptr;

					pr_trace("Got Wifi IP: %u %u %u %u\n", wifi_ip[0], wifi_ip[1], wifi_ip[2], wifi_ip[3]);

					lv_show(ui_SystemMenuExpanders);
					lv_label_set_text_fmt(
						ui_SystemMenuExpanders, "Wifi IP: %u.%u.%u.%u", wifi_ip[0], wifi_ip[1], wifi_ip[2], wifi_ip[3]);

					wifi_ip_state = WifiIPState::Idle;

				} else if (message == FileStorageProxy::WifiIPFailed) {
					lv_show(ui_SystemMenuExpanders);
					lv_label_set_text(ui_SystemMenuExpanders, "Wifi not connected");

					wifi_ip_state = WifiIPState::Idle;
				}

			} break;

			case WifiIPState::NoMemory: {
			} break;
		}
	}

private:
	FileStorageProxy &storage;
	lv_group_t *group = nullptr;

	enum WifiIPState { Idle, Requested, NoMemory } wifi_ip_state = WifiIPState::Idle;
	uint32_t last_check_wifi_ip_tm = 0;

	using IpAddr = std::array<char, 4>;
	IpAddr *wifi_ip_ptr = nullptr;

	MonotonicAllocator allocator;
};
} // namespace MetaModule
