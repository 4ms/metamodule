#pragma once
#include "core_intercom/patch_icc_message.hh"
#include "drivers/inter_core_comm.hh"
#include "fat_file_io.hh"
#include <cstring>
#include <optional>

namespace MetaModule
{

struct FirmwareFileFinder {
	using InterCoreComm2 = mdrivlib::InterCoreComm<mdrivlib::ICCCoreType::Responder, IntercoreStorageMessage>;
	using enum IntercoreStorageMessage::MessageType;

	FirmwareFileFinder(std::span<char> &raw_buffer, FatFileIO &sdcard_fileio, FatFileIO &usb_fileio)
		: sdcard_{sdcard_fileio}
		, usb_{usb_fileio}
		, read_buffer_{raw_buffer} {
	}

	// Return optional message that needs to be sent
	void handle_message(IntercoreStorageMessage &message) {
		if (message.message_type == RequestFirmwareFile) {
			printf("M4 will scan for firmware files\n");
			pending_send_message.message_type = FirmwareFileNotFound;
			pending_send_message.patch_id = 0;
			pending_send_message.vol_id = Volume::MaxVolumes;
			pending_send_message.bytes_read = 0;

			if (scan(usb_)) {
				pending_send_message.message_type = FirmwareFileFound;
				pending_send_message.filename = found_filename;
				pending_send_message.vol_id = Volume::USB;
			} else if (scan(sdcard_)) {
				pending_send_message.message_type = FirmwareFileFound;
				pending_send_message.filename = found_filename;
				pending_send_message.vol_id = Volume::SDCard;
			}
			message.message_type = None;
		}
	}

	void send_pending_message(InterCoreComm2 &comm) {
		if (pending_send_message.message_type != None) {
			// Keep trying to send message until suceeds
			if (comm.send_message(pending_send_message))
				pending_send_message.message_type = None;
		}
	}

private:
	bool scan(FatFileIO &fileio) {
		found_filename[0] = '\0';
		bool ok = fileio.foreach_file_with_ext(
			".uimg", [&fileio, this](const std::string_view filename, uint32_t timestamp, uint32_t filesize) {
				pr_dbg("File %.255s\n", filename.data());

				if (filename.starts_with("metamodule-fw-") && filesize > 100 * 1024) {
					constexpr uint32_t UIMG_MAGIC = 0x27051956;
					std::array<char, sizeof(UIMG_MAGIC)> buf;

					auto bytes_read = fileio.read_file(filename, buf);
					if (bytes_read != sizeof(UIMG_MAGIC)) {
						pr_err("Error reading file %.255s\n", filename.data());
						return;
					}

					auto magic = *reinterpret_cast<uint32_t *>(buf.data());
					if (magic == UIMG_MAGIC) {
						pr_dbg("Found uimg file: %.255s\n", filename.data());
						strncpy(found_filename.data(), filename.data(), filename.size());
						return;
					}
				}
			});

		if (!ok || found_filename[0] == '\0')
			return false;

		return true;
	}

	FatFileIO &sdcard_;
	FatFileIO &usb_;

	const std::span<char> &read_buffer_;

	IntercoreStorageMessage pending_send_message{.message_type = None};

	std::array<char, 255> found_filename;
};

} // namespace MetaModule
