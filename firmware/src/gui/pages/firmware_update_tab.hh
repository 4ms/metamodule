#pragma once
#include "fw_update/updater.hh"
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
		, tabs(lv_tabview_get_tab_btns(ui_SystemMenuTabView))
		, updater{patch_storage} {

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
						pr_trace("\nA7: send message request_firmware_file\n");
						if (file_storage.request_find_firmware_file())
							state = State::Scanning;
					});
				}
			} break;

			case State::Scanning: {
				auto message = file_storage.get_message();

				if (message.message_type == FileStorageProxy::FirmwareFileFound) {
					pr_trace("A7: Message received: manifest file found: %.255s\n", message.filename.data());
					if (manifest_filename = std::string{message.filename.data()}; manifest_filename.length()) {
						manifest_file_vol = message.vol_id;
						manifest_filesize = message.bytes_read;
						display_manifest_found();
					} else {
						pr_trace("Filename empty, skipping\n");
						display_file_not_found();
					}
					state = State::Idle;

				} else if (message.message_type == FileStorageProxy::FirmwareFileNotFound) {
					pr_trace("A7: Message received: no manifest file found\n");
					display_file_not_found();
					state = State::Idle;
				}

			} break;

			case State::Updating: {
				auto status = updater.process();

				if (status.state == FirmwareUpdater::Error) {
					display_update_failed(status.error_message);
					state = State::Failed;

				} else if (status.state == FirmwareUpdater::LoadingFileToRAM or status.state == FirmwareUpdater::StartLoadingFileToRam) {
					display_progress("Loading to RAM", status.file_size, status.file_size);

				} else if (status.state == FirmwareUpdater::Verifying or status.state == FirmwareUpdater::StartVerify) {
					display_progress("Comparing with target area", status.file_size, status.bytes_completed);

				} else if (status.state == FirmwareUpdater::Writing or status.state == FirmwareUpdater::StartWriting) {
					display_progress("Writing file", status.file_size, status.bytes_completed);

				} else if (status.state == FirmwareUpdater::Success) {
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
						page->start_fw_update();
					}
				},
				"This will take a few minutes and cannot be interrupted. \n"
				"You must keep the unit powered on for the entire procedure.",
				"Update");
		}
	}

	void start_fw_update() {
		patch_playloader.stop_audio();
		// Pause long enough for audio to stop. TODO: query patch_playloader
		auto time = lv_tick_get();
		while ((lv_tick_get() - time) < 100)
			;

		if (!updater.start(manifest_filename, manifest_file_vol, manifest_filesize)) {
			display_update_failed("Could not load manifest file\n");
			state = State::Failed;
		} else {
			display_reading_manifest();
		}
	}

	void display_reading_manifest() {
		lv_label_set_text_fmt(ui_SystemMenuUpdateMessage,
							  "Reading update file %s (%u kB)... Please wait\n",
							  manifest_filename.data(),
							  int(manifest_filesize / 1024));
		lv_show(ui_FWUpdateSpinner);
		lv_hide(ui_SystemMenUpdateProgressBar);
		lv_hide(ui_SystemMenuUpdateFWBut);
		state = State::Updating;
	}

	void display_manifest_found() {
		lv_obj_set_style_text_color(ui_SystemMenuUpdateMessage, lv_palette_lighten(LV_PALETTE_GREEN, 1), LV_PART_MAIN);
		lv_label_set_text_fmt(ui_SystemMenuUpdateMessage,
							  "Firmware update file found on %s: %s, %u bytes",
							  manifest_file_vol == Volume::USB ? "USB" : "SD",
							  manifest_filename.c_str(),
							  (unsigned)manifest_filesize);

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

	void display_update_failed(std::string_view message) {
		lv_obj_set_style_text_color(ui_SystemMenuUpdateMessage, lv_palette_lighten(LV_PALETTE_RED, 1), LV_PART_MAIN);
		lv_label_set_text_fmt(
			ui_SystemMenuUpdateMessage, "Updating firmware failed!\n%.*s", (int)message.length(), message.data());
		lv_hide(ui_FWUpdateSpinner);
		lv_hide(ui_SystemMenUpdateProgressBar);
	}

	void display_success() {
		lv_obj_set_style_text_color(ui_SystemMenuUpdateMessage, lv_palette_lighten(LV_PALETTE_GREEN, 1), LV_PART_MAIN);
		lv_label_set_text(ui_SystemMenuUpdateMessage, "Success! Firmware has been updated. Power off and back on now");

		lv_hide(ui_FWUpdateSpinner);
		lv_hide(ui_SystemMenUpdateProgressBar);
	}

	void display_progress(std::string_view message, int file_size, int bytes_completed) {
		if (file_size > 0 && bytes_completed < file_size) {
			lv_label_set_text_fmt(ui_SystemMenuUpdateMessage,
								  "%.*s:\n%u of %u kB\nDO NOT POWER OFF",
								  (int)message.size(),
								  message.data(),
								  unsigned((bytes_completed) / 1024),
								  unsigned(file_size / 1024));

			int percent = 100 * (bytes_completed) / file_size;
			lv_hide(ui_FWUpdateSpinner);
			lv_show(ui_SystemMenUpdateProgressBar);
			lv_bar_set_value(ui_SystemMenUpdateProgressBar, percent, LV_ANIM_ON);
		} else {
			lv_show(ui_FWUpdateSpinner);
			lv_hide(ui_SystemMenUpdateProgressBar);
			lv_label_set_text_fmt(
				ui_SystemMenuUpdateMessage, "%.*s:\nDO NOT POWER OFF", (int)message.size(), message.data());
		}
	}

	FileStorageProxy &file_storage;
	PatchPlayLoader &patch_playloader;

	lv_group_t *group = nullptr;
	lv_obj_t *tabs = nullptr;

	ConfirmPopup confirm_popup;

	std::string manifest_filename = "";
	Volume manifest_file_vol = Volume::USB;

	uint32_t manifest_filesize = 0;

	FirmwareUpdater updater;

	PollEvent<uint32_t> media_poll{2000};

	enum class State { Idle, Scanning, Updating, Failed, Success } state = State::Idle;
};
} // namespace MetaModule
