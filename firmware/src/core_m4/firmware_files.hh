#pragma once
#include "core_intercom/intercore_message.hh"
#include "drivers/inter_core_comm.hh"
#include "fat_file_io.hh"
#include "poll_change.hh"
#include "util/static_string.hh"
#include <cstring>
#include <optional>

namespace MetaModule
{

struct FirmwareFileFinder {
	using InterCoreComm2 = mdrivlib::InterCoreComm<mdrivlib::ICCCoreType::Responder, IntercoreStorageMessage>;
	using enum IntercoreStorageMessage::MessageType;

	FirmwareFileFinder(std::span<char> &raw_buffer, FatFileIO &sdcard_fileio, FatFileIO &usb_fileio)
		: sdcard_{sdcard_fileio}
		, usbdrive_{usb_fileio} // , read_buffer_{raw_buffer}
	{
		sd_changes_.reset();
		usb_changes_.reset();
	}

	void handle_message(IntercoreStorageMessage &message) {

		if (message.message_type == RequestFirmwareFile) {
			printf("M4 will scan for firmware files\n");

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

			message.message_type = None;
		}

		// Check for changes in media plugged/unplugged even when there are no messages (i.e. GUI page is not making requests)
		// That way, when a GUI page is loaded that starts making requests, we'll automatically scan() if and only if
		// something was plugged/unplugged recently
		poll_media_change();
	}

	void send_pending_message(InterCoreComm2 &comm) {
		if (pending_send_message.message_type != None) {
			// Keep trying to send message until succeeds
			if (comm.send_message(pending_send_message))
				pending_send_message.message_type = None;
		}
	}

private:
	void poll_media_change() {
		sd_changes_.poll(HAL_GetTick(), [this] { return sdcard_.is_mounted(); });
		usb_changes_.poll(HAL_GetTick(), [this] { return usbdrive_.is_mounted(); });
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

	FatFileIO &sdcard_;
	FatFileIO &usbdrive_;
	PollChange sd_changes_{1000};
	PollChange usb_changes_{1000};

	// const std::span<char> &read_buffer_;

	IntercoreStorageMessage pending_send_message{.message_type = None};

	StaticString<255> found_filename;
	uint32_t found_filesize;
};

} // namespace MetaModule
