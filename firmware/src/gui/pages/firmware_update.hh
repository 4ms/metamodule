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

struct FirmwareUpdateTab {
	FirmwareUpdateTab(FileStorageProxy &patch_storage, PatchPlayLoader &patch_playloader)
		: patch_storage{patch_storage}
		, patch_playloader{patch_playloader}
		, tabs(lv_tabview_get_tab_btns(ui_SystemMenuTabView)) {

		lv_obj_add_event_cb(ui_SystemMenuUpdateFWBut, updatebut_cb, LV_EVENT_CLICKED, this);
		// lv_obj_add_event_cb(ui_SystemMenuUpdateFWBut, updatebut_cb, LV_EVENT_LEAVE, this);
	}

	void prepare_focus(lv_group_t *group) {
		this->group = group;

		state = State::Idle;
		confirm_popup.init(ui_SystemMenu, group);
	}

	bool try_go_back() {
		if (confirm_popup.is_visible()) {
			confirm_popup.hide();
			return false;
		}
		if (state == State::Idle || state == State::Failed)
			return true;
		else
			return false;
	}

	void update() {
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
					pr_dbg("Progress...\n");
					//scan RAM for progress?
					//zero-init ram_buffer before loading.
					//read a word from ram_buffer every 16kB starting at end, going to beginning, until
					//we find a non-zero word
				});
			} break;

			case State::Failed: {
			} break;
		}
	}

private:
	static void updatebut_cb(lv_event_t *event) {
		auto page = static_cast<FirmwareUpdateTab *>(event->user_data);
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
	}

	void display_file_found() {
		lv_obj_set_style_text_color(ui_SystemMenuUpdateMessage, lv_palette_lighten(LV_PALETTE_GREEN, 1), LV_PART_MAIN);
		lv_label_set_text_fmt(ui_SystemMenuUpdateMessage,
							  "Firmware update file found on %s: %s, %u bytes",
							  update_file_vol == Volume::USB ? "USB" : "SD",
							  update_filename.c_str(),
							  (unsigned)update_filesize);
		// lv_obj_clear_state(ui_SystemMenuUpdateFWBut, LV_STATE_DISABLED);
		lv_show(ui_SystemMenuUpdateFWBut);
		lv_group_set_editing(group, false);
		lv_group_add_obj(group, ui_SystemMenuUpdateFWBut);
		lv_group_focus_obj(ui_SystemMenuUpdateFWBut);
	}

	void display_file_not_found() {
		lv_label_set_text(ui_SystemMenuUpdateMessage,
						  "Insert an SD card or USB drive containing a firmware update file.");
		lv_obj_set_style_text_color(ui_SystemMenuUpdateMessage, lv_palette_lighten(LV_PALETTE_RED, 1), LV_PART_MAIN);
		// lv_obj_add_state(ui_SystemMenuUpdateFWBut, LV_STATE_DISABLED);
		lv_hide(ui_SystemMenuUpdateFWBut);
		lv_group_focus_obj(tabs);
		lv_group_set_editing(group, true);
	}

	void display_ram_loaded() {
		lv_obj_set_style_text_color(ui_SystemMenuUpdateMessage, lv_palette_lighten(LV_PALETTE_GREEN, 1), LV_PART_MAIN);
		lv_label_set_text(ui_SystemMenuUpdateMessage,
						  "Writing to Flash. DO NOT POWER DOWN. This may take several minutes");
	}

	void display_ram_load_failed() {
		lv_obj_set_style_text_color(ui_SystemMenuUpdateMessage, lv_palette_lighten(LV_PALETTE_RED, 1), LV_PART_MAIN);
		lv_label_set_text(ui_SystemMenuUpdateMessage, "Loading to RAM failed! Try powering off and back on again.");
		lv_hide(ui_FWUpdateSpinner);
	}

	void display_allocate_failed() {
		lv_obj_set_style_text_color(ui_SystemMenuUpdateMessage, lv_palette_lighten(LV_PALETTE_RED, 1), LV_PART_MAIN);
		lv_label_set_text_fmt(ui_SystemMenuUpdateMessage,
							  "Not enough free RAM to load file (need %u kB). Try rebooting.",
							  update_filesize / 1024);
		lv_hide(ui_FWUpdateSpinner);
	}

	void start_ram_loading() {
		patch_playloader.stop_audio();
		// Pause long enough for audio to stop
		auto time = lv_tick_get();
		while ((lv_tick_get() - time) < 100)
			;

		// Allocate memory for the firmware file
		ram_buffer = std::make_unique_for_overwrite<char[]>(update_filesize);
		char *load_ptr = ram_buffer.get();
		if (load_ptr == nullptr) {
			display_allocate_failed();
			state = State::Failed;
		}

		lv_hide(ui_SystemMenuUpdateFWBut);

		// Keep trying to send message
		while (!patch_storage.request_load_fw_to_ram(update_filename, update_file_vol, load_ptr))
			;

		lv_label_set_text_fmt(ui_SystemMenuUpdateMessage,
							  "Loading update file %s (%u kB)... Please wait\n",
							  update_filename.data(),
							  update_filesize / 1024);
		lv_show(ui_FWUpdateSpinner);
		state = State::Updating;
	}

	void start_flash_loading() {
		// TODO: Nor Flash Loader: copy ram_buffer to NORFlash at 0x70008000
	}

	FileStorageProxy &patch_storage;
	PatchPlayLoader &patch_playloader;

	lv_group_t *group;
	lv_obj_t *tabs = nullptr;

	ConfirmPopup confirm_popup;

	std::string update_filename = "";
	uint32_t update_filesize = 0;
	Volume update_file_vol;

	PollEvent media_poll{2000};
	PollEvent status_poll{200};

	enum class State { Idle, Scanning, Updating, Failed } state = State::Idle;

	std::unique_ptr<char[]> ram_buffer;
};
} // namespace MetaModule
