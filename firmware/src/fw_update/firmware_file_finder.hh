#pragma once
#include "core_intercom/intercore_message.hh"
#include "drivers/inter_core_comm.hh"
#include "fat_file_io.hh"
#include "fw_update/update_path.hh"
#include "util/poll_change.hh"
#include "util/static_string.hh"
#include <cstring>
#include <optional>

namespace MetaModule
{

struct FirmwareFileFinder {
	using InterCoreComm = mdrivlib::InterCoreComm<mdrivlib::ICCRoleType::Responder, IntercoreStorageMessage>;
	using enum IntercoreStorageMessage::MessageType;

	FirmwareFileFinder(FatFileIO &sdcard_fileio, FatFileIO &usb_fileio)
		: sdcard_{sdcard_fileio}
		, usbdrive_{usb_fileio} {
	}

	std::optional<IntercoreStorageMessage> handle_message(const IntercoreStorageMessage &message) {

		if (message.message_type == RequestFirmwareFile) {
			return scan_all_for_manifest();
		}

		return std::nullopt;
	}

private:
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
			IntercoreStorageMessage result{
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
		found_filename.copy(UpdateFileManifestFilename);

		FILINFO info;
		if (fileio.get_fat_filinfo(std::string_view(found_filename), info)) {
			found_filesize = info.fsize;
			return true;
		}
		return false;
	}

	FatFileIO &sdcard_;
	FatFileIO &usbdrive_;

	StaticString<255> found_filename;
	uint32_t found_filesize = 0;
};

} // namespace MetaModule
