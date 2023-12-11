#pragma once
#include "flash_loader/flash_loader.hh"
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
					if (file_storage.request_find_firmware_file())
						state = State::Scanning;
				});
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
						display_file_not_found();
					}
					state = State::Idle;

				} else if (message.message_type == FileStorageProxy::FirmwareFileNotFound) {
					pr_dbg("A7: Message received: no fw file found\n");
					display_file_not_found();
					state = State::Idle;

					// } else if (message.message_type == FileStorageProxy::FirmwareFileUnchanged) {
					// 	pr_dbg("A7: Message received: no change in fw file status\n");
					// 	state = State::Idle;
				}

			} break;

			case State::Loading: {
				auto message = file_storage.get_message();

				if (message.message_type == FileStorageProxy::LoadFirmwareToRamSuccess) {
					display_ram_loaded();
					start_flash_writing();
					state = State::Writing;

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

			case State::Writing: {
				status_poll.poll(lv_tick_get(), [] { pr_dbg("Writing Progress...\n"); });
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
		lv_show(ui_SystemMenuUpdateFWBut);
		lv_group_set_editing(group, false);
		lv_group_add_obj(group, ui_SystemMenuUpdateFWBut);
		lv_group_focus_obj(ui_SystemMenuUpdateFWBut);
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
	}

	void display_allocate_failed() {
		lv_obj_set_style_text_color(ui_SystemMenuUpdateMessage, lv_palette_lighten(LV_PALETTE_RED, 1), LV_PART_MAIN);
		lv_label_set_text_fmt(ui_SystemMenuUpdateMessage,
							  "Not enough free RAM to load file (need %u kB). Try rebooting.",
							  int(update_filesize / 1024));
		lv_hide(ui_FWUpdateSpinner);
	}

	void display_flash_write_failed() {
		lv_obj_set_style_text_color(ui_SystemMenuUpdateMessage, lv_palette_lighten(LV_PALETTE_RED, 1), LV_PART_MAIN);
		lv_label_set_text(ui_SystemMenuUpdateMessage, "Could not write to internal Flash.");

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

		auto buffer_span = std::span<char>{ram_buffer.get(), update_filesize};
		if (buffer_span.data() == nullptr) {
			display_allocate_failed();
			state = State::Failed;
		}

		lv_hide(ui_SystemMenuUpdateFWBut);

		// Keep trying to send message
		while (!file_storage.request_load_file(update_filename, update_file_vol, buffer_span)) {
			auto time = lv_tick_get();
			while ((lv_tick_get() - time) < 20)
				;
		}

		lv_label_set_text_fmt(ui_SystemMenuUpdateMessage,
							  "Loading update file %s (%u kB)... Please wait\n",
							  update_filename.data(),
							  int(update_filesize / 1024));
		lv_show(ui_FWUpdateSpinner);
		state = State::Loading;
	}

	void start_flash_writing() {
		lv_show(ui_FWUpdateSpinner);

		auto file_data = std::span<uint8_t>{reinterpret_cast<uint8_t *>(ram_buffer.get()), update_filesize};
		unsigned bytes_written = 0;
		int bytes_remaining = file_data.size();

		FlashLoader flash;

		if (!flash.check_flash_chip()) {
			display_flash_write_failed();
			state = State::Failed;
		}

		uint32_t flash_base_addr = 0x80000;

		uint32_t cur_addr = flash_base_addr;
		std::span<uint8_t> cur_sector{file_data.subspan(0, 4096)};

		while (bytes_remaining > 0) {
			lv_label_set_text_fmt(ui_SystemMenuUpdateMessage,
								  "Writing update file to flash: %.2f of %.2f kB... DO NOT POWER OFF",
								  (bytes_written / 1024.f),
								  (file_data.size() / 1024.f));

			if (!flash.write_sectors(cur_addr, cur_sector)) {
				display_flash_write_failed();
				state = State::Failed;
				break;
			}
			cur_addr += 4096;
			bytes_written += 4096;
			bytes_remaining -= 4096;
			cur_sector = cur_sector.subspan(4096, std::min(4096, bytes_remaining));
		}
	}

	FileStorageProxy &file_storage;
	PatchPlayLoader &patch_playloader;

	lv_group_t *group;
	lv_obj_t *tabs = nullptr;

	ConfirmPopup confirm_popup;

	std::string update_filename = "";
	uint32_t update_filesize = 0;
	Volume update_file_vol;

	PollEvent media_poll{2000};
	PollEvent status_poll{200};

	enum class State { Idle, Scanning, Loading, Writing, Failed } state = State::Idle;

	std::unique_ptr<char[]> ram_buffer;
};
} // namespace MetaModule
