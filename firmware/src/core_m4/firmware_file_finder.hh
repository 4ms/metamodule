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
	using InterCoreComm2 = mdrivlib::InterCoreComm<mdrivlib::ICCCoreType::Responder, IntercoreStorageMessage>;
	using enum IntercoreStorageMessage::MessageType;

	FirmwareFileFinder(FatFileIO &sdcard_fileio, FatFileIO &usb_fileio)
		: sdcard_{sdcard_fileio}
		, usbdrive_{usb_fileio} {
		sd_changes_.reset();
		usb_changes_.reset();
	}

	void handle_message(IntercoreStorageMessage &message) {

		if (message.message_type == RequestFirmwareFile) {
			find_firmware_file();
			message.message_type = None;
		}

		if (message.message_type == RequestLoadFirmwareToRam) {
			load_firmware_file(message);
			message.message_type = None;
		}

		poll_media_change();
	}

	void send_pending_message(InterCoreComm2 &comm) {
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

	void find_firmware_file() {
		printf("M4 scanning for firmware files\n");

		std::optional<Volume> fw_file_vol{};

		bool media_changed = false;
		if (usb_changes_.take_change() || sd_changes_.take_change()) {
			media_changed = true;

			if (usbdrive_.is_mounted()) {
				if (scan(usbdrive_))
					fw_file_vol = Volume::USB;
			}

			// Files found on USB take precedence over SD Card
			if (!fw_file_vol && sdcard_.is_mounted()) {
				if (scan(sdcard_))
					fw_file_vol = Volume::SDCard;
			}
		}

		if (fw_file_vol) {
			pending_send_message.message_type = FirmwareFileFound;
			pending_send_message.filename.copy(found_filename);
			pending_send_message.bytes_read = found_filesize;
			pending_send_message.vol_id = fw_file_vol.value();

		} else if (media_changed) {
			pending_send_message.message_type = FirmwareFileNotFound;

		} else {
			pending_send_message.message_type = FirmwareFileUnchanged;
		}
	}

	bool scan(FatFileIO &fileio) {
		found_filename.copy("");

		bool ok = fileio.foreach_file_with_ext(
			".uimg", [&fileio, this](const std::string_view filename, uint32_t tm, uint32_t filesize) {
				pr_dbg("M4: Check file %.255s\n", filename.data());

				if (!filename.starts_with("metamodule-fw-"))
					return;

				if (filesize < 100 * 1024)
					return;

				constexpr uint32_t UIMG_MAGIC = 0x56190527;
				std::array<char, sizeof(UIMG_MAGIC)> buf;

				auto bytes_read = fileio.read_file(filename, buf);
				if (bytes_read != sizeof(UIMG_MAGIC)) {
					pr_err("Error reading file %.255s\n", filename.data());
					return;
				}

				auto magic = *reinterpret_cast<uint32_t *>(buf.data());
				if (magic == UIMG_MAGIC) {
					found_filename.copy(filename);
					found_filesize = filesize;
					pr_dbg("M4: Found uimg file: %s (%u B)\n", found_filename.c_str(), found_filesize);
				} else
					pr_dbg("M4: Wrong magic: 0x%08x\n", magic);
			});

		if (!ok || found_filename[0] == '\0')
			return false;

		return true;
	}

	void load_firmware_file(IntercoreStorageMessage &message) {
		FatFileIO *fileio = (message.vol_id == Volume::USB)	   ? &usbdrive_ :
							(message.vol_id == Volume::SDCard) ? &sdcard_ :
																 nullptr;
		bool success = ram_loader.load_to_ram(fileio, message.filename, message.buffer);
		if (success) {
			pending_send_message.message_type = LoadFirmwareToRamSuccess;
			pending_send_message.buffer = message.buffer;
		} else {
			pending_send_message.message_type = LoadFirmwareToRamFailed;
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
