#pragma once
#include "fw_update/firmware_flash_loader.hh"
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
		: file_storage{patch_storage}
		, patch_playloader{patch_playloader}
		, tabs(lv_tabview_get_tab_btns(ui_SystemMenuTabView)) {

		lv_hide(ui_SystemMenuUpdateFWBut);
		lv_obj_add_event_cb(ui_SystemMenuUpdateFWBut, updatebut_cb, LV_EVENT_CLICKED, this);
	}

	void prepare_focus(lv_group_t *group) {
		this->group = group;

		state = State::Idle;
		lv_hide(ui_FWUpdateSpinner);
		display_file_not_found();

		confirm_popup.init(ui_SystemMenu, group);
	}

	// Returns true if this pages uses the back event
	bool consume_back_event() {
		if (confirm_popup.is_visible()) {
			confirm_popup.hide();
			return true;
		}
		if (state == State::Idle || state == State::Failed)
			return false;
		else
			return true; //Consume back event: un-interruptable operation in progress
	}

	void update() {
		switch (state) {

			case State::Idle: {
				if (!confirm_popup.is_visible()) {
					media_poll.poll(lv_tick_get(), [this] {
						pr_dbg("\nA7: send message request_firmware_file\n");
						if (file_storage.request_find_firmware_file())
							state = State::Scanning;
					});
				}
			} break;

			case State::Scanning: {
				auto message = file_storage.get_message();

				if (message.message_type == FileStorageProxy::FirmwareFileFound) {
					pr_dbg("A7: Message received: fw file found: %.255s\n", message.filename.data());
					if (update_filename = std::string{message.filename.data()}; update_filename.length()) {
						update_file_vol = message.vol_id;
						update_filesize = message.bytes_read;
						display_file_found();
					} else {
						pr_dbg("Filename empty, skipping\n");
						display_file_not_found();
					}
					state = State::Idle;

				} else if (message.message_type == FileStorageProxy::FirmwareFileNotFound) {
					pr_dbg("A7: Message received: no fw file found\n");
					display_file_not_found();
					state = State::Idle;
				}

			} break;

			case State::Loading: {
				auto message = file_storage.get_message();

				if (message.message_type == FileStorageProxy::LoadFirmwareToRamSuccess) {
					display_ram_loaded();
					if (start_flash_writing())
						state = State::Writing;
					else
						state = State::Failed;

				} else if (message.message_type == FileStorageProxy::LoadFirmwareToRamFailed) {
					display_ram_load_failed();
					state = State::Failed;
				}

			} break;

			case State::Writing: {
				auto [bytes_remaining, err] = flash_writer.load_next_block();

				if (err == FirmwareFlashLoader::Error::Failed) {
					display_flash_write_failed();
					state = State::Failed;

				} else if (bytes_remaining > 0) {
					display_progress(bytes_remaining);

				} else {
					display_success();
					state = State::Success;
				}
			} break;

			case State::Success: {
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
					if (ok) {
						page->start_ram_loading();
						page->state = State::Loading;
					}
				},
				"This will take a few minutes and cannot be interrupted. \n"
				"You must keep the unit powered on for the entire procedure.",
				"Update");
		}
	}

	void start_ram_loading() {
		patch_playloader.stop_audio();
		// Pause long enough for audio to stop. TODO: query patch_playloader
		auto time = lv_tick_get();
		while ((lv_tick_get() - time) < 100)
			;

		auto buffer_span = std::span<char>{reinterpret_cast<char *>(flash_writer.buffer()), update_filesize};

		while (!file_storage.request_load_file(update_filename, update_file_vol, buffer_span)) {
			// Keep trying to send message
			auto time = lv_tick_get();
			while ((lv_tick_get() - time) < 20)
				;
		}

		lv_label_set_text_fmt(ui_SystemMenuUpdateMessage,
							  "Reading update file %s (%u kB)... Please wait\n",
							  update_filename.data(),
							  int(update_filesize / 1024));
		lv_show(ui_FWUpdateSpinner);
		lv_hide(ui_SystemMenUpdateProgressBar);
		lv_hide(ui_SystemMenuUpdateFWBut);
	}

	bool start_flash_writing() {
		if (!flash_writer.verify_image(update_filesize)) {
			display_ram_load_failed();
			return false;
		}

		if (!flash_writer.start()) {
			display_flash_write_failed();
			return false;
		}

		lv_obj_set_style_text_color(ui_SystemMenuUpdateMessage, lv_palette_lighten(LV_PALETTE_GREEN, 1), LV_PART_MAIN);
		lv_hide(ui_FWUpdateSpinner);
		lv_show(ui_SystemMenUpdateProgressBar);
		return true;
	}

	void display_file_found() {
		lv_obj_set_style_text_color(ui_SystemMenuUpdateMessage, lv_palette_lighten(LV_PALETTE_GREEN, 1), LV_PART_MAIN);
		lv_label_set_text_fmt(ui_SystemMenuUpdateMessage,
							  "Firmware update file found on %s: %s, %u bytes",
							  update_file_vol == Volume::USB ? "USB" : "SD",
							  update_filename.c_str(),
							  (unsigned)update_filesize);

		if (lv_obj_has_flag(ui_SystemMenuUpdateFWBut, LV_OBJ_FLAG_HIDDEN)) {
			lv_show(ui_SystemMenuUpdateFWBut);
			lv_group_set_editing(group, false);
			lv_group_add_obj(group, ui_SystemMenuUpdateFWBut);
			lv_group_focus_obj(ui_SystemMenuUpdateFWBut);
		}
	}

	void display_file_not_found() {
		lv_label_set_text(ui_SystemMenuUpdateMessage,
						  "Insert an SD card or USB drive containing a firmware update file.");
		lv_obj_set_style_text_color(ui_SystemMenuUpdateMessage, lv_palette_lighten(LV_PALETTE_RED, 1), LV_PART_MAIN);
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
		lv_hide(ui_SystemMenUpdateProgressBar);
	}

	void display_allocate_failed() {
		lv_obj_set_style_text_color(ui_SystemMenuUpdateMessage, lv_palette_lighten(LV_PALETTE_RED, 1), LV_PART_MAIN);
		lv_label_set_text_fmt(ui_SystemMenuUpdateMessage,
							  "Not enough free RAM to load file (need %u kB). Try rebooting.",
							  int(update_filesize / 1024));
		lv_hide(ui_FWUpdateSpinner);
		lv_hide(ui_SystemMenUpdateProgressBar);
	}

	void display_flash_write_failed() {
		lv_obj_set_style_text_color(ui_SystemMenuUpdateMessage, lv_palette_lighten(LV_PALETTE_RED, 1), LV_PART_MAIN);
		lv_label_set_text(ui_SystemMenuUpdateMessage, "Could not write to internal Flash.");

		lv_hide(ui_FWUpdateSpinner);
		lv_hide(ui_SystemMenUpdateProgressBar);
	}

	void display_success() {
		lv_obj_set_style_text_color(ui_SystemMenuUpdateMessage, lv_palette_lighten(LV_PALETTE_GREEN, 1), LV_PART_MAIN);
		lv_label_set_text(ui_SystemMenuUpdateMessage, "Firmware has been updated! Please power off and back on now");

		lv_hide(ui_FWUpdateSpinner);
		lv_hide(ui_SystemMenUpdateProgressBar);
	}

	void display_progress(int bytes_remaining) {
		lv_label_set_text_fmt(ui_SystemMenuUpdateMessage,
							  "Writing update file to flash:\n%u of %u kB\nDO NOT POWER OFF",
							  unsigned((update_filesize - bytes_remaining) / 1024),
							  unsigned(update_filesize / 1024));

		int percent = 100 * (update_filesize - bytes_remaining) / update_filesize;
		lv_bar_set_value(ui_SystemMenUpdateProgressBar, percent, LV_ANIM_ON);
	}

	FileStorageProxy &file_storage;
	PatchPlayLoader &patch_playloader;

	lv_group_t *group;
	lv_obj_t *tabs = nullptr;

	ConfirmPopup confirm_popup;

	std::string update_filename = "";
	uint32_t update_filesize = 0;
	Volume update_file_vol;

	FirmwareFlashLoader flash_writer;

	PollEvent<uint32_t> media_poll{2000};

	enum class State { Idle, Scanning, Loading, Writing, Failed, Success } state = State::Idle;
};
} // namespace MetaModule
