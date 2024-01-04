#pragma once
#include "conf/qspi_flash_conf.hh"
#include "conf/sdcard_conf.hh"
#include "core_intercom/intercore_message.hh"
#include "drivers/inter_core_comm.hh"
#include "drivers/qspi_flash_driver.hh"
#include "fs/fatfs/fat_file_io.hh"
#include "fs/fatfs/ramdisk_ops.hh"
#include "fs/fatfs/sdcard_ops.hh"
#include "fs/littlefs/norflash_lfs.hh"
#include "fs/volumes.hh"
#include "patch_file/patch_fileio.hh"
#include "pr_dbg.hh"
#include "util/poll_change.hh"

namespace MetaModule
{

// PatchStorage manages all patch filesystems <--> PatchList
class PatchStorage {

	FatFileIO &sdcard_;
	PollChange sd_changes_{1000};

	mdrivlib::QSpiFlash flash_{qspi_patchflash_conf};
	LfsFileIO norflash_{flash_};

	FatFileIO &usbdrive_;
	PollChange usb_changes_{1000};

	PollChange norflash_changes_{1000};

	using InterCoreComm2 = mdrivlib::InterCoreComm<mdrivlib::ICCCoreType::Responder, IntercoreStorageMessage>;
	using enum IntercoreStorageMessage::MessageType;
	IntercoreStorageMessage pending_send_message{.message_type = None};

public:
	PatchStorage(FatFileIO &sdcard_fileio, FatFileIO &usb_fileio)
		: sdcard_{sdcard_fileio}
		, usbdrive_{usb_fileio} {

		// NOR Flash: if it's unformatted, put default patches there
		auto status = norflash_.initialize();
		if (status == LfsFileIO::Status::NewlyFormatted) {
			reload_default_patches();
		}

		// Populate norflash the first time we request it
		norflash_changes_.reset();
		poll_media_change();
	}

	void reload_default_patches() {
		norflash_.reformat();
		PatchFileIO::create_default_patches(norflash_);
	}
	bool write_patch_file(Volume vol, std::string_view filename, std::span<const char> data) {
		if (vol == Volume::USB) {
			auto success = PatchFileIO::write_file(data, usbdrive_, filename);
			if (success) {
				usb_changes_.reset();
			}
			return success;

		} else if (vol == Volume::SDCard) {
			auto success = PatchFileIO::write_file(data, sdcard_, filename);
			if (success) {
				sd_changes_.reset();
			}
			return success;

		} else if (vol == Volume::NorFlash) {
			auto success = PatchFileIO::write_file(data, norflash_, filename);
			if (success) {
				norflash_changes_.reset();
			}
			return success;
		} else {
			return false;
		}
	}

	bool write_patch_file(Volume vol, std::string_view filename, std::span<const uint8_t> data) {
		return write_patch_file(vol, filename, {(const char *)data.data(), data.size()});
	}


	void send_pending_message(InterCoreComm2 &comm) {
		if (pending_send_message.message_type != None) {
			// Keep trying to send message until suceeds
			if (comm.send_message(pending_send_message))
				pending_send_message.message_type = None;
		}
	}

	void handle_message(IntercoreStorageMessage &message) {
		if (message.message_type == RequestRefreshPatchList) {
			pending_send_message.message_type = PatchListUnchanged;

			auto *patch_dir_list_ = message.patch_dir_list;

			if (patch_dir_list_) {

				if (sd_changes_.take_change()) {
					printf("sd update\n");
					patch_dir_list_->clear_patches(Volume::SDCard);

					if (sdcard_.is_mounted())
						PatchFileIO::add_directory(sdcard_, patch_dir_list_->volume_root(Volume::SDCard));

					pending_send_message.message_type = PatchListChanged;
				}

				if (usb_changes_.take_change()) {
					printf("usb update\n");
					patch_dir_list_->clear_patches(Volume::USB);

					if (usbdrive_.is_mounted())
						PatchFileIO::add_directory(usbdrive_, patch_dir_list_->volume_root(Volume::USB));

					pending_send_message.message_type = PatchListChanged;
				}

				if (norflash_changes_.take_change()) {
					patch_dir_list_->clear_patches(Volume::NorFlash);

					PatchFileIO::add_directory(norflash_, patch_dir_list_->volume_root(Volume::NorFlash));

					pending_send_message.message_type = PatchListChanged;
				}
			}

			message.message_type = None; //mark as handled
		}

		if (message.message_type == RequestPatchData) {
			pending_send_message.message_type = PatchDataLoadFail;
			pending_send_message.filename = message.filename;
			pending_send_message.vol_id = message.vol_id;
			pending_send_message.bytes_read = 0;

			if ((uint32_t)message.vol_id < (uint32_t)Volume::MaxVolumes) {
				auto bytes_read = load_patch_file(message.buffer, message.vol_id, message.filename);
				if (bytes_read) {
					pending_send_message.message_type = PatchDataLoaded;
					pending_send_message.bytes_read = bytes_read;
				}
			}
			message.message_type = None; //mark as handled
		}

		poll_media_change();
	}

private:
	void poll_media_change() {
		sd_changes_.poll(HAL_GetTick(), [this] { return sdcard_.is_mounted(); });
		usb_changes_.poll(HAL_GetTick(), [this] { return usbdrive_.is_mounted(); });
	}

	uint32_t load_patch_file(std::span<char> buffer, Volume vol, std::string_view filename) {

		bool ok = false;
		switch (vol) {
			case Volume::NorFlash:
				ok = PatchFileIO::read_file(buffer, norflash_, filename);
				break;
			case Volume::SDCard:
				ok = PatchFileIO::read_file(buffer, sdcard_, filename);
				break;
			case Volume::USB:
				ok = PatchFileIO::read_file(buffer, usbdrive_, filename);
				break;
			default:
				break;
		}

		if (!ok) {
			pr_warn("Could not load patch id %.*s\n", (int)filename.size(), filename.data());
			return 0;
		}

		pr_dbg("Read patch %.*s, %d bytes\n", (int)filename.size(), filename.data(), buffer.size_bytes());
		return buffer.size_bytes();
	}
};

} // namespace MetaModule
