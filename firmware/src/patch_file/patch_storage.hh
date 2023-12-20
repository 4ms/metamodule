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

	using InterCoreComm2 = mdrivlib::InterCoreComm<mdrivlib::ICCCoreType::Responder, IntercoreStorageMessage>;
	using enum IntercoreStorageMessage::MessageType;
	IntercoreStorageMessage pending_send_message{.message_type = None};

	PatchList patch_list_;

public:
	PatchStorage(FatFileIO &sdcard_fileio, FatFileIO &usb_fileio)
		: sdcard_{sdcard_fileio}
		, usbdrive_{usb_fileio} {

		// NOR Flash: if it's unformatted, put default patches there
		auto status = norflash_.initialize();
		if (status == LfsFileIO::Status::NewlyFormatted) {
			reload_default_patches();
		}

		// Populate Patch List from all media present
		patch_list_.clear_patches(Volume::NorFlash);
		PatchFileIO::add_all_to_patchlist(norflash_, patch_list_);

		sdcard_.mount_disk();
		if (sdcard_.is_mounted()) {
			patch_list_.clear_patches(Volume::SDCard);
			PatchFileIO::add_all_to_patchlist(sdcard_, patch_list_);
			sd_changes_.reset();
		}

		usbdrive_.mount_disk();
		if (usbdrive_.is_mounted()) {
			patch_list_.clear_patches(Volume::USB);
			PatchFileIO::add_all_to_patchlist(usbdrive_, patch_list_);
			usb_changes_.reset();
		}

		poll_media_change();
	}

	void reload_default_patches() {
		norflash_.reformat();
		PatchFileIO::create_default_patches(norflash_);
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

			message.patch_file_list->norflash = patch_list_.get_patchfile_list(Volume::NorFlash);

			if (sd_changes_.take_change()) {
				patch_list_.clear_patches(Volume::SDCard);
				if (sdcard_.is_mounted())
					rescan_sdcard();
				message.patch_file_list->sdcard = patch_list_.get_patchfile_list(Volume::SDCard);

				pending_send_message.message_type = PatchListChanged;
			}

			if (usb_changes_.take_change()) {
				patch_list_.clear_patches(Volume::USB);
				if (usbdrive_.is_mounted())
					rescan_usbdrive();
				message.patch_file_list->usb = patch_list_.get_patchfile_list(Volume::USB);

				pending_send_message.message_type = PatchListChanged;
			}

			message.message_type = None; //mark as handled
		}

		if (message.message_type == RequestPatchData) {
			pending_send_message.message_type = PatchDataLoadFail;
			pending_send_message.patch_id = message.patch_id;
			pending_send_message.vol_id = message.vol_id;
			pending_send_message.bytes_read = 0;

			if (message.patch_id < patch_list_.num_patches() && (uint32_t)message.vol_id < (uint32_t)Volume::MaxVolumes)
			{
				auto bytes_read = load_patch_file(message.buffer, message.vol_id, message.patch_id);
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

	void rescan_sdcard() {
		pr_trace("Updating patchlist from SD Card.\n");
		PatchFileIO::add_all_to_patchlist(sdcard_, patch_list_);
	}

	void rescan_usbdrive() {
		pr_trace("Updating patchlist from USB Drive.\n");
		PatchFileIO::add_all_to_patchlist(usbdrive_, patch_list_);
	}

	uint32_t load_patch_file(std::span<char> buffer, Volume vol, uint32_t patch_id) {
		auto filename = patch_list_.get_patch_filename(vol, patch_id);
		pr_dbg("load_patch_file() patch_id=%d vol=%d name=%.31s\n", patch_id, (uint32_t)vol, filename.data());

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
			pr_warn("Could not load patch id %d\n", patch_id);
			return 0;
		}

		pr_dbg("Read patch id %d, %d bytes\n", patch_id, buffer.size_bytes());
		return buffer.size_bytes();
	}
};

} // namespace MetaModule
