#pragma once
#include "core_intercom/intercore_message.hh"
#include "drivers/inter_core_comm.hh"
#include "fat_file_io.hh"
#include "firmware_ram_loader.hh"
#include "util/poll_change.hh"
#include "util/static_string.hh"
#include <cstring>
#include <optional>

namespace MetaModule
{

struct FirmwareFileFinder {
	using InterCoreComm = mdrivlib::InterCoreComm<mdrivlib::ICCCoreType::Responder, IntercoreStorageMessage>;
	using enum IntercoreStorageMessage::MessageType;

	FirmwareFileFinder(FatFileIO &sdcard_fileio, FatFileIO &usb_fileio)
		: sdcard_{sdcard_fileio}
		, usbdrive_{usb_fileio} {
		sd_changes_.reset();
		usb_changes_.reset();
	}

	void handle_message(IntercoreStorageMessage &message) {

		if (message.message_type == RequestFirmwareFile) {
			scan_all_for_manifest();
			message.message_type = None;
		}

		if (message.message_type == RequestLoadFileToRam) {
			pr_dbg("M4: got RequestLoadFileToRam\n");
			load_file(message);
			message.message_type = None;
		}

		poll_media_change();
	}

	void send_pending_message(InterCoreComm &comm) {
		if (pending_send_message.message_type != None) {
			if (comm.send_message(pending_send_message))
				pending_send_message.message_type = None;
		}
	}

private:
	void poll_media_change() {
		sd_changes_.poll(HAL_GetTick(), [this] { return sdcard_.is_mounted(); });
		usb_changes_.poll(HAL_GetTick(), [this] { return usbdrive_.is_mounted(); });
	}

	void scan_all_for_manifest() {
		pr_dbg("M4: scanning all volumes for firmware manifest files (metamodule*.json)\n");

		std::optional<Volume> fw_file_vol{};

		if (usbdrive_.is_mounted()) {
			if (find_manifest(usbdrive_))
				fw_file_vol = Volume::USB;
		}

		// Files found on USB take precedence over SD Card
		if (!fw_file_vol && sdcard_.is_mounted()) {
			if (find_manifest(sdcard_))
				fw_file_vol = Volume::SDCard;
		}

		if (fw_file_vol) {
			pending_send_message.message_type = FirmwareFileFound;
			pending_send_message.filename.copy(found_filename);
			pending_send_message.bytes_read = found_filesize;
			pending_send_message.vol_id = fw_file_vol.value();

		} else {
			pending_send_message.message_type = FirmwareFileNotFound;
		}
	}

	bool find_manifest(FatFileIO &fileio) {
		found_filename.copy("");

		bool ok = fileio.foreach_file_with_ext(
			".json", [this](const std::string_view filename, uint32_t tm, uint32_t filesize) {
				pr_trace("M4: Checking file %.255s\n", filename.data());

				if (filename.starts_with("metamodule") && filesize > 30) {
					found_filename.copy(filename);
					found_filesize = filesize;
					pr_dbg("M4: Found manifest file: %s (%u B)\n", found_filename.c_str(), found_filesize);
				}
			});

		if (!ok || found_filename.length() == 0)
			return false;

		return true;
	}

	void load_file(IntercoreStorageMessage &message) {
		FatFileIO *fileio = (message.vol_id == Volume::USB)	   ? &usbdrive_ :
							(message.vol_id == Volume::SDCard) ? &sdcard_ :
																 nullptr;
		bool success = ram_loader.load_to_ram(fileio, message.filename, message.buffer);

		if (success) {
			pr_dbg("M4: Loaded OK. first word is %p: %x\n",
				   message.buffer.data(),
				   *reinterpret_cast<uint32_t *>(message.buffer.data()));
			pending_send_message.message_type = LoadFileToRamSuccess;
		} else {
			pr_dbg("M4: Failed Load\n");
			pending_send_message.message_type = LoadFileToRamFailed;
		}
	}

	FatFileIO &sdcard_;
	FatFileIO &usbdrive_;
	PollChange sd_changes_{1000};
	PollChange usb_changes_{1000};

	IntercoreStorageMessage pending_send_message{.message_type = None};

	StaticString<255> found_filename;
	uint32_t found_filesize;

	FirmwareRamLoader ram_loader;
};

} // namespace MetaModule
