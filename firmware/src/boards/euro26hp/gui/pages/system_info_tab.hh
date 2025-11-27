#pragma once
#include "drivers/cache.hh"
#include "git_version.h"
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/system_menu_tab_base.hh"
#include "gui/ui_lvgl/meta5/ui.h"
#include "ld.h"
#include "params/expanders.hh"
#include "params/metaparams.hh"
#include "patch_file/file_storage_proxy.hh"
#include "wifi/detection.hh"
#include <cmath>

#if !defined(SIMULATOR)
#include <malloc.h>
#endif

namespace MetaModule
{

struct InfoTab : SystemMenuTab {

	InfoTab(FileStorageProxy &storage, MetaParams const &metaparams)
		: detect_wifi{storage}
		, metaparams{metaparams} {
		lv_label_set_text(ui_SystemMenuExpanders, "No Wi-Fi module found");
		lv_show(ui_SystemMenuExpanders);
	}

	void prepare_focus(lv_group_t *group) override {
		this->group = group;

		std::string_view fw_version = GIT_FIRMWARE_VERSION_TAG;
		if (fw_version.starts_with("firmware-"))
			fw_version.remove_prefix(9);

		int memory_percent_used = 0;
		size_t memory_used = 1;
		unsigned memory_total = A7_HEAP_SZ / (1024 * 1024);

#if !defined(SIMULATOR)
		struct mallinfo mi = mallinfo();
		pr_info("HEAP_SZ  %zu (total amount linker reserved for A7 heap)\n", A7_HEAP_SZ);
		pr_info("arena    %zu (total space allocated so far via sbrk)\n", mi.arena);
		pr_info("ordblks  %zu (number of non-inuse chunks)\n", mi.ordblks);
		pr_info("hblks    %zu (number of mmapped regions)\n", mi.hblks);
		pr_info("hblkhd   %zu (total space in mmapped regions)\n", mi.hblkhd);
		pr_info("uordblks %zu (total allocated space)\n", mi.uordblks);
		pr_info("fordblks %zu (total non-inuse space)\n", mi.fordblks);
		pr_info("keepcost %zu (top-most, releasable via malloc_trim space)\n", mi.keepcost);

		memory_percent_used = (int)std::round(100.f * (float)mi.uordblks / (float)A7_HEAP_SZ);
		memory_used = mi.uordblks / (1024 * 1024);
#endif

		lv_label_set_text_fmt(ui_SystemMenuFWversion,
							  "Firmware: %s\nRAM: %d%% (%zu/%u MB)",
							  fw_version.data(),
							  memory_percent_used,
							  memory_used,
							  memory_total);

		lv_show(ui_SystemMenuExpanders);

		if (Expanders::get_connected().ext_audio_connected) {
			lv_label_set_text(ui_SystemMenuAudioExpanders, "MetaAIO connected");
		} else {
			lv_label_set_text(ui_SystemMenuAudioExpanders, "MetaAIO not found");
		}
		lv_show(ui_SystemMenuAudioExpanders);

		if (metaparams.button_exp_connected != 0) {
			std::string s;
			s = "MetaButtons found: ";
			if (metaparams.button_exp_connected & 0b0001)
				s += "#1, ";
			if (metaparams.button_exp_connected & 0b0010)
				s += "#2, ";
			if (metaparams.button_exp_connected & 0b0100)
				s += "#3, ";
			if (metaparams.button_exp_connected & 0b1000)
				s += "#4";
			if (s.ends_with(", "))
				s = s.substr(0, s.length() - 2);

			lv_label_set_text(ui_SystemMenuButExpander, s.c_str());
		} else {
			lv_label_set_text(ui_SystemMenuButExpander, "No MetaButtons found");
		}
		lv_show(ui_SystemMenuButExpander);

		detect_wifi.start();
		detect_wifi.new_wifi_status_available(lv_tick_get());

		lv_group_remove_obj(ui_SystemMenuMainModuleCont);
		lv_group_remove_obj(ui_SystemMenuExpandersCont);
		lv_group_add_obj(group, ui_SystemMenuMainModuleCont);
		lv_group_add_obj(group, ui_SystemMenuExpandersCont);
		lv_group_focus_obj(ui_SystemMenuMainModuleCont);

		lv_group_add_obj(group, ui_SystemMenuExpandersCont);

		lv_obj_add_event_cb(ui_SystemMenuMainModuleCont, scroll_cb, LV_EVENT_FOCUSED, nullptr);
		lv_obj_add_event_cb(ui_SystemMenuExpandersCont, scroll_cb, LV_EVENT_FOCUSED, nullptr);

		lv_obj_scroll_to_y(ui_SystemMenuInfoTab, 0, LV_ANIM_ON);
	}

	static void scroll_cb(lv_event_t *event) {
		if (!event)
			return;

		if (event->target == ui_SystemMenuMainModuleCont) {
			lv_obj_scroll_to_y(ui_SystemMenuInfoTab, 0, LV_ANIM_ON);

		} else if (event->target == ui_SystemMenuExpandersCont) {
			lv_obj_scroll_to_y(ui_SystemMenuInfoTab, lv_obj_get_height(ui_SystemInfoCont), LV_ANIM_ON);
		}
	}

	void update() override {
		update_wifi_expander();
	}

	bool is_idle() override {
		return detect_wifi.is_idle();
	}

	void update_wifi_expander() {
#ifdef SIMULATOR
		lv_show(ui_SystemMenuExpanders);
		lv_label_set_text(ui_SystemMenuExpanders, "Wi-Fi: http://192.168.1.23");
		return;
#endif
		if (!detect_wifi.new_wifi_status_available(lv_tick_get())) {
			return;
		}

		lv_show(ui_SystemMenuExpanders);

		if (auto wifi_status = detect_wifi.get_status()) {
			std::string disp;
			disp.resize(36);
			disp = "Wi-Fi: http://" + std::to_string(wifi_status->ip[0]) + "." + std::to_string(wifi_status->ip[1]) +
				   "." + std::to_string(wifi_status->ip[2]) + "." + std::to_string(wifi_status->ip[3]);
			if (wifi_status->port != 80)
				disp += ":" + std::to_string(wifi_status->port);

			lv_label_set_text(ui_SystemMenuExpanders, disp.c_str());

		} else {
			switch (wifi_status.error()) {
				case WifiIPError::NO_MODULE_CONNECTED:
					lv_label_set_text(ui_SystemMenuExpanders, "No Wi-Fi module found");
					break;

				case WifiIPError::NO_IP:
					lv_label_set_text(ui_SystemMenuExpanders, "Wi-Fi module not connected\n to a Wi-Fi network");
					break;

				case WifiIPError::INTERNAL_ERROR:
					lv_label_set_text(ui_SystemMenuExpanders, "Wi-Fi module: Internal Error");
					break;
			}
		}
	}

private:
	lv_group_t *group = nullptr;
	WifiInterface::DetectExpander detect_wifi;
	MetaParams const &metaparams;
};
} // namespace MetaModule
