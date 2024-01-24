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

	std::optional<IntercoreStorageMessage> handle_message(const IntercoreStorageMessage &message) {

		if (message.message_type == RequestFirmwareFile) {
			return scan_all_for_manifest();
		}

		if (message.message_type == RequestLoadFileToRam) {
			pr_trace("M4: got RequestLoadFileToRam\n");
			return load_file(message);
		}

		poll_media_change();

		return std::nullopt;
	}

private:
	void poll_media_change() {
		sd_changes_.poll(HAL_GetTick(), [this] { return sdcard_.is_mounted(); });
		usb_changes_.poll(HAL_GetTick(), [this] { return usbdrive_.is_mounted(); });
	}

	IntercoreStorageMessage scan_all_for_manifest() {
		pr_trace("M4: scanning all volumes for firmware manifest files (metamodule*.json)\n");

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
			IntercoreStorageMessage result {
				.message_type = FirmwareFileFound,
				.bytes_read = found_filesize,
				.vol_id = fw_file_vol.value(),
			};

			result.filename.copy(found_filename);

			return result;

		} else {
			return {.message_type = FirmwareFileNotFound};
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
					pr_trace("M4: Found manifest file: %s (%u B)\n", found_filename.c_str(), found_filesize);
				}
			});

		if (!ok || found_filename.length() == 0)
			return false;

		return true;
	}

	IntercoreStorageMessage load_file(const IntercoreStorageMessage &message) {
		FatFileIO *fileio = (message.vol_id == Volume::USB)	   ? &usbdrive_ :
							(message.vol_id == Volume::SDCard) ? &sdcard_ :
																 nullptr;
		bool success = ram_loader.load_to_ram(fileio, message.filename, message.buffer);

		if (success) {
			pr_trace("M4: Loaded OK.\n");
			return {.message_type = LoadFileToRamSuccess};
		} else {
			pr_err("M4: Failed Load\n");
			return {.message_type = LoadFileToRamFailed};
		}
	}

	FatFileIO &sdcard_;
	FatFileIO &usbdrive_;
	PollChange sd_changes_{1000};
	PollChange usb_changes_{1000};

	StaticString<255> found_filename;
	uint32_t found_filesize = 0;

	FirmwareRamLoader ram_loader;
};

} // namespace MetaModule
