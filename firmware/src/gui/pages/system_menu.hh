#pragma once
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/base.hh"
#include "gui/pages/confirm_popup.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/meta5/ui.h"

namespace MetaModule
{

struct SystemMenuPage : PageBase {
	SystemMenuPage(PatchInfo info)
		: PageBase{info, PageId::SystemMenu}
		, tabs(lv_tabview_get_tab_btns(ui_SystemMenuTabView)) {

		init_bg(ui_SystemMenu);

		lv_group_remove_all_objs(group);
		lv_group_add_obj(group, tabs);
		lv_group_set_editing(group, true);

		lv_obj_add_event_cb(tabs, tab_cb, LV_EVENT_VALUE_CHANGED, this);

		lv_obj_add_event_cb(ui_SystemMenuUpdateFWBut, updatebut_cb, LV_EVENT_CLICKED, this);
		confirm_popup.init(ui_SystemMenu, group);
	}

	void prepare_focus() final {
		lv_group_focus_obj(tabs);
		lv_group_set_editing(group, true);
		lv_obj_add_state(ui_SystemMenuUpdateFWBut, LV_STATE_DISABLED);
	}

	void update() final {
		if (metaparams.meta_buttons[0].is_just_released()) {
			if (confirm_popup.is_visible()) {
				confirm_popup.hide();
			} else {
				page_list.request_last_page();
			}
		}

		switch (state) {
			case State::Idle: {
				uint32_t now = lv_tick_get();
				if (now - last_refresh_check_tm > 2000) { //poll media once per second
					printf("Scanning...");
					last_refresh_check_tm = now;
					if (patch_storage.request_firmware_file())
						state = State::ScanningForUpdates;
				}
			} break;

			case State::ScanningForUpdates: {
				auto message = patch_storage.get_message();

				if (message.message_type == FileStorageProxy::FirmwareFileFound) {
					printf("Message received: fw file found\n");
					update_filename = std::string{message.filename.data()};
					if (update_filename.length()) {
						state = State::UpdateFound;
						update_filesize = message.bytes_read;
						update_file_vol = message.vol_id;
					} else
						state = State::UpdateNotFound;

				} else if (message.message_type == FileStorageProxy::FirmwareFileNotFound) {
					printf("Message received: no fw file found\n");

					state = State::UpdateNotFound;
				}
			} break;

			case State::UpdateFound:
				lv_label_set_text_fmt(ui_SystemMenuUpdateMessage,
									  "Firmware update file found on %s: %s, %u bytes",
									  update_file_vol == Volume::USB ? "USB" : "SD",
									  update_filename.c_str(),
									  update_filesize);
				lv_obj_clear_state(ui_SystemMenuUpdateFWBut, LV_STATE_DISABLED);
				state = State::Idle;
				break;

			case State::UpdateNotFound:
				lv_label_set_text(ui_SystemMenuUpdateMessage,
								  "Insert an SD card or USB drive containing a firmware update file.");
				lv_obj_add_state(ui_SystemMenuUpdateFWBut, LV_STATE_DISABLED);
				state = State::Idle;
				break;

			case State::StartUpdate:
				printf("Start update...\n");
				break;
		}
	}

	void blur() final {
		;
	}

private:
	void update_firmware() {
		if (state == State::UpdateFound)
			state = State::StartUpdate;
		//
		printf("Update firmware would begin here...\n");
	}

	static void tab_cb(lv_event_t *event) {
		auto page = static_cast<SystemMenuPage *>(event->user_data);
		if (!page)
			return;

		uint32_t id = lv_btnmatrix_get_selected_btn(page->tabs);
		pr_dbg("Clicked Tab %d\n", id);

		if (id == 0) {
			lv_group_remove_obj(ui_SystemMenuUpdateFWBut);
		}
		if (id == 1) {
			lv_group_add_obj(page->group, ui_SystemMenuUpdateFWBut);
			lv_group_focus_obj(ui_SystemMenuUpdateFWBut);
			lv_group_set_editing(page->group, false);
		}
	}

	static void updatebut_cb(lv_event_t *event) {
		auto page = static_cast<SystemMenuPage *>(event->user_data);
		if (!page)
			return;

		page->confirm_popup.show(
			[page](bool ok) {
				if (!ok)
					return;
				page->update_firmware();
			},
			"Update");
	}

	ConfirmPopup confirm_popup;
	lv_obj_t *tabs = nullptr;

	uint32_t last_refresh_check_tm = 0;
	std::string update_filename = "";
	uint32_t update_filesize = 0;
	Volume update_file_vol;

	enum class State { Idle, ScanningForUpdates, UpdateFound, UpdateNotFound, StartUpdate } state = State::Idle;
};

} // namespace MetaModule
