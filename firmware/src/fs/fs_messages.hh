#pragma once

#include "calibrate/calibration_message_handler.hh"
#include "core_intercom/intercore_message.hh"
#include "drivers/inter_core_comm.hh"
#include "dynload/plugin_file_finder.hh"
#include "fs/fatfs/fat_file_io.hh"
#include "fw_update/firmware_file_finder.hh"
#include "fw_update/firmware_writer.hh"
#include "patch_file/patch_storage.hh"
#include "wifi/app_request_handler.hh"

namespace MetaModule
{

struct FilesystemMessages {

	FilesystemMessages(FatFileIO &usb_fileio, FatFileIO &sd_fileio, IntercoreStorageMessage *shared_message)
		: usb_fileio{usb_fileio}
		, sd_fileio{sd_fileio}
		, intercore_comm{*shared_message} {
	}

	void process() {
		patch_storage.refresh_patch_list();

		auto message = intercore_comm.get_new_message();

		if (message.message_type != IntercoreStorageMessage::MessageType::None) {
			auto process_receiver = [this, &message](auto &receiver) {
				if (auto response = receiver.handle_message(message); response) {
					// mark message as handled
					message.message_type = IntercoreStorageMessage::MessageType::None;

					// try to send response infinitely
					while (!intercore_comm.send_message(*response))
						;
				}
			};

			process_receiver(patch_storage);
			process_receiver(firmware_files);
			process_receiver(firmware_writer);
			process_receiver(plugin_files);
			process_receiver(calibration_handler);
			process_receiver(wifi_app_handler);

			if (message.message_type != IntercoreStorageMessage::MessageType::None) {
				pr_err("ICC message of type %u not handled\n", message.message_type);
			}
		}
	}

	void reload_default_patches() {
		patch_storage.reload_default_patches();
	}

	PatchStorage &get_patch_storage() {
		return patch_storage;
	}

private:
	FatFileIO &usb_fileio;
	FatFileIO &sd_fileio;

	mdrivlib::InterCoreComm<mdrivlib::ICCRoleType::Responder, IntercoreStorageMessage> intercore_comm;

	FlashLoader flash_loader;

	PatchStorage patch_storage{sd_fileio, usb_fileio};
	FirmwareFileFinder firmware_files{sd_fileio, usb_fileio};
	FirmwareWriter firmware_writer{sd_fileio, usb_fileio, flash_loader};
	PluginFileFinder plugin_files{sd_fileio, usb_fileio};
	CalibrationMessageHandler calibration_handler{flash_loader};
	WifiAppRequestHandler wifi_app_handler{};
};

} // namespace MetaModule
