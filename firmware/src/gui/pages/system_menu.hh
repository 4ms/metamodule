#pragma once
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/base.hh"
#include "gui/pages/confirm_popup.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/styles.hh"

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
		// lv_obj_add_event_cb(ui_SystemMenuUpdateFWBut, updatebut_cb, LV_EVENT_LEAVE, this);

		confirm_popup.init(ui_SystemMenu, group);
	}

	void prepare_focus() final {
		lv_group_focus_obj(tabs);
		lv_group_set_editing(group, true);
		lv_obj_add_state(ui_SystemMenuUpdateFWBut, LV_STATE_DISABLED);
		state = State::Idle;
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
				if (now - last_refresh_check_tm > 2000) {
					pr_dbg("\nA7: send message request_firmware_file\n");
					last_refresh_check_tm = now;
					if (patch_storage.request_firmware_file())
						state = State::ScanningForUpdates;
				}
			} break;

			case State::ScanningForUpdates: {

				auto message = patch_storage.get_message();

				if (message.message_type == FileStorageProxy::FirmwareFileFound) {
					pr_dbg("A7: Message received: fw file found: %.255s\n", message.filename.data());

					update_filename = std::string{message.filename.data()};

					if (update_filename.length()) {
						update_file_vol = message.vol_id;
						update_filesize = message.bytes_read;
						state = State::UpdateFound;
					} else {
						pr_dbg("A7: file has blank name\n");
						state = State::UpdateNotFound;
					}

				} else if (message.message_type == FileStorageProxy::FirmwareFileNotFound) {
					pr_dbg("A7: Message received: no fw file found\n");
					state = State::UpdateNotFound;

				} else if (message.message_type == FileStorageProxy::FirmwareFileUnchanged) {
					pr_dbg("A7: Message received: no change in fw file status\n");
					state = State::Idle;
				}
			} break;

			case State::UpdateFound:
				lv_label_set_text_fmt(ui_SystemMenuUpdateMessage,
									  "Firmware update file found on %s: %s, %u bytes",
									  update_file_vol == Volume::USB ? "USB" : "SD",
									  update_filename.c_str(),
									  (unsigned)update_filesize);
				lv_obj_set_style_text_color(
					ui_SystemMenuUpdateMessage, lv_palette_lighten(LV_PALETTE_GREEN, 1), LV_PART_MAIN);
				lv_obj_clear_state(ui_SystemMenuUpdateFWBut, LV_STATE_DISABLED);
				lv_group_set_editing(group, false);
				lv_group_add_obj(group, ui_SystemMenuUpdateFWBut);
				lv_group_focus_obj(ui_SystemMenuUpdateFWBut);
				state = State::Idle;
				break;

			case State::UpdateNotFound:
				lv_label_set_text(ui_SystemMenuUpdateMessage,
								  "Insert an SD card or USB drive containing a firmware update file.");
				lv_obj_set_style_text_color(
					ui_SystemMenuUpdateMessage, lv_palette_lighten(LV_PALETTE_RED, 1), LV_PART_MAIN);
				lv_obj_add_state(ui_SystemMenuUpdateFWBut, LV_STATE_DISABLED);
				lv_group_focus_obj(tabs);
				lv_group_set_editing(group, true);
				state = State::Idle;
				break;

			case State::Updating:

				pr_dbg("Start update...\n");
				break;
		}
	}

	void blur() final {
		;
	}

private:
	void update_firmware() {
		if (state == State::UpdateFound)
			state = State::Updating;

		patch_playloader.stop_audio();
		HAL_Delay(100); //let audio stop in bg

		patch_storage.request_load_fw_to_ram();
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
			lv_obj_add_state(ui_SystemMenuUpdateFWBut, LV_STATE_DISABLED);
		}
	}

	static void updatebut_cb(lv_event_t *event) {
		auto page = static_cast<SystemMenuPage *>(event->user_data);
		if (!page)
			return;

		if (event->code == LV_EVENT_CLICKED) {
			page->confirm_popup.show(
				[page](bool ok) {
					if (!ok)
						return;
					page->update_firmware();
				},
				"This will take a few minutes and cannot be interrupted. You must keep the unit powered on for the "
				"entire "
				"procedure.",
				"Update");
		}

		// if (event->code == LV_EVENT_LEAVE) {
		// 	printf("Defocus\n");
		// 	lv_group_focus_obj(page->tabs);
		// 	lv_group_set_editing(page->group, true);
		// }
	}

	ConfirmPopup confirm_popup;
	lv_obj_t *tabs = nullptr;

	uint32_t last_refresh_check_tm = 0;
	std::string update_filename = "";
	uint32_t update_filesize = 0;
	Volume update_file_vol;

	enum class State { Idle, ScanningForUpdates, UpdateFound, UpdateNotFound, Updating } state = State::Idle;
};

} // namespace MetaModule
