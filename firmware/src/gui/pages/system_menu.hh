#pragma once
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/base.hh"
#include "gui/pages/confirm_popup.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/styles.hh"
#include "util/poll_event.hh"

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
				media_poll.poll(lv_tick_get(), [this] {
					pr_dbg("\nA7: send message request_firmware_file\n");
					if (patch_storage.request_find_firmware_file())
						state = State::Scanning;
				});
			} break;

			case State::Scanning: {
				auto message = patch_storage.get_message();

				if (message.message_type == FileStorageProxy::FirmwareFileFound) {
					pr_dbg("A7: Message received: fw file found: %.255s\n", message.filename.data());
					if (update_filename = std::string{message.filename.data()}; update_filename.length()) {
						update_file_vol = message.vol_id;
						update_filesize = message.bytes_read;
						display_file_found();
					} else {
						display_file_not_found();
					}

				} else if (message.message_type == FileStorageProxy::FirmwareFileNotFound) {
					pr_dbg("A7: Message received: no fw file found\n");
					display_file_not_found();

				} else if (message.message_type == FileStorageProxy::FirmwareFileUnchanged) {
					pr_dbg("A7: Message received: no change in fw file status\n");
				}

				state = State::Idle;
			} break;

			case State::Updating: {
				auto message = patch_storage.get_message();

				if (message.message_type == FileStorageProxy::LoadFirmwareToRamSuccess) {
					display_ram_loaded();
					start_flash_loading();
					state = State::Updating;

				} else if (message.message_type == FileStorageProxy::LoadFirmwareToRamFailed) {
					ram_buffer.reset();
					display_ram_load_failed();
					state = State::Failed;
				}

				status_poll.poll(lv_tick_get(), [] {
					pr_dbg("\nA7: send message request_status\n");
					// patch_storage.request_firmware_load_status();
				});
			} break;
		}
	}

	void blur() final {
		;
	}

private:
	void display_file_found() {
		lv_label_set_text_fmt(ui_SystemMenuUpdateMessage,
							  "Firmware update file found on %s: %s, %u bytes",
							  update_file_vol == Volume::USB ? "USB" : "SD",
							  update_filename.c_str(),
							  (unsigned)update_filesize);
		lv_obj_set_style_text_color(ui_SystemMenuUpdateMessage, lv_palette_lighten(LV_PALETTE_GREEN, 1), LV_PART_MAIN);
		lv_obj_clear_state(ui_SystemMenuUpdateFWBut, LV_STATE_DISABLED);
		lv_group_set_editing(group, false);
		lv_group_add_obj(group, ui_SystemMenuUpdateFWBut);
		lv_group_focus_obj(ui_SystemMenuUpdateFWBut);
	}

	void display_file_not_found() {
		lv_label_set_text(ui_SystemMenuUpdateMessage,
						  "Insert an SD card or USB drive containing a firmware update file.");
		lv_obj_set_style_text_color(ui_SystemMenuUpdateMessage, lv_palette_lighten(LV_PALETTE_RED, 1), LV_PART_MAIN);
		lv_obj_add_state(ui_SystemMenuUpdateFWBut, LV_STATE_DISABLED);
		lv_group_focus_obj(tabs);
		lv_group_set_editing(group, true);
	}

	void display_ram_loaded() {
	}
	void display_ram_load_failed() {
	}
	void display_allocate_failed() {
	}

	void start_ram_loading() {
		patch_playloader.stop_audio();
		// Pause long enough for audio to stop
		auto time = lv_tick_get();
		while ((lv_tick_get() - time) < 100)
			;

		// Allocate memory for the firmware file
		ram_buffer = std::make_unique_for_overwrite<char[]>(update_filesize);
		char *load_address = ram_buffer.get();
		if (load_address == nullptr) {
			display_allocate_failed();
			state = State::Failed;
		}
		pr_dbg("A7 request load %s on vol %d to RAM 0x%p\n", update_filename.data(), update_file_vol, load_address);
		if (patch_storage.request_load_fw_to_ram(update_filename, update_file_vol, load_address)) {
			lv_label_set_text(ui_SystemMenuUpdateMessage, "Updating... Do not power down\n");
			state = State::Updating;
		}
	}

	void start_flash_loading() {
	}

	static void tab_cb(lv_event_t *event) {
		auto page = static_cast<SystemMenuPage *>(event->user_data);
		if (!page)
			return;

		switch (lv_btnmatrix_get_selected_btn(page->tabs)) {
			case Tabs::Status: {
				lv_group_remove_obj(ui_SystemMenuUpdateFWBut);
				break;
			}

			case Tabs::Update: {
				// lv_group_add_obj(page->group, ui_SystemMenuUpdateFWBut);
				// lv_obj_add_state(ui_SystemMenuUpdateFWBut, LV_STATE_DISABLED);
				break;
			}

			case Tabs::Test: {
				break;
			}
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
					page->start_ram_loading();
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

	std::string update_filename = "";
	uint32_t update_filesize = 0;
	Volume update_file_vol;

	PollEvent media_poll{2000};
	PollEvent status_poll{200};

	enum class State { Idle, Scanning, Updating, Failed } state = State::Idle;

	enum Tabs { Status = 0, Update = 1, Test = 2 };

	std::unique_ptr<char[]> ram_buffer;
};

} // namespace MetaModule
