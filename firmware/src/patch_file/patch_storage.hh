#pragma once
#include "conf/qspi_flash_conf.hh"
#include "conf/sdcard_conf.hh"
#include "core_intercom/patch_icc_message.hh"
#include "drivers/inter_core_comm.hh"
#include "drivers/qspi_flash_driver.hh"
#include "fs/fatfs/fat_file_io.hh"
#include "fs/fatfs/ramdisk_ops.hh"
#include "fs/fatfs/sdcard_ops.hh"
#include "fs/littlefs/norflash_lfs.hh"
#include "fs/volumes.hh"
#include "patch_file/patch_fileio.hh"
#include "poll_change.hh"
#include "pr_dbg.hh"

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

	const std::span<char> &raw_patch_buffer_;

	PatchFileList &filelist_;

public:
	PatchStorage(std::span<char> &raw_patch_buffer,
				 PatchFileList &filelist,
				 FatFileIO &sdcard_fileio,
				 FatFileIO &usb_fileio,
				 bool reset_to_factory_patches = false)
		: sdcard_{sdcard_fileio}
		, usbdrive_{usb_fileio}
		, raw_patch_buffer_{raw_patch_buffer}
		, filelist_{filelist} {

		// NOR Flash: if it's unformatted, put default patches there
		auto status = norflash_.initialize();
		if (status == LfsFileIO::Status::NewlyFormatted || reset_to_factory_patches) {
			norflash_.reformat();
			PatchFileIO::create_default_patches(norflash_);
		}

		// Populate Patch List from all media present
		patch_list_.clear_patches(Volume::NorFlash);
		PatchFileIO::add_all_to_patchlist(norflash_, patch_list_);
		filelist_.norflash = patch_list_.get_patchfile_list(Volume::NorFlash);

		sdcard_.mount_disk();
		if (sdcard_.is_mounted()) {
			patch_list_.clear_patches(Volume::SDCard);
			PatchFileIO::add_all_to_patchlist(sdcard_, patch_list_);
			sd_changes_.reset();
		}
		filelist_.sdcard = patch_list_.get_patchfile_list(Volume::SDCard);

		usbdrive_.mount_disk();
		if (usbdrive_.is_mounted()) {
			patch_list_.clear_patches(Volume::USB);
			PatchFileIO::add_all_to_patchlist(usbdrive_, patch_list_);
			usb_changes_.reset();
		}
		filelist_.usb = patch_list_.get_patchfile_list(Volume::USB);

		poll_media_change();
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

			if (sd_changes_.take_change()) {
				patch_list_.clear_patches(Volume::SDCard);
				if (sdcard_.is_mounted())
					rescan_sdcard();
				filelist_.sdcard = patch_list_.get_patchfile_list(Volume::SDCard);

				pending_send_message.message_type = PatchListChanged;
			}

			if (usb_changes_.take_change()) {
				patch_list_.clear_patches(Volume::USB);
				if (usbdrive_.is_mounted())
					rescan_usbdrive();
				filelist_.usb = patch_list_.get_patchfile_list(Volume::USB);

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
				auto bytes_read = load_patch_file(message.vol_id, message.patch_id);
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
		sd_changes_.poll(HAL_GetTick(), sdcard_.is_mounted());
		usb_changes_.poll(HAL_GetTick(), usbdrive_.is_mounted());
	}

	void rescan_sdcard() {
		pr_trace("Updating patchlist from SD Card.\n");
		PatchFileIO::add_all_to_patchlist(sdcard_, patch_list_);
		pr_trace(
			"SD Patchlist updated. filelist data: %p, size: %d.\n", filelist_.sdcard.data(), filelist_.sdcard.size());
	}

	void rescan_usbdrive() {
		pr_trace("Updating patchlist from USB Drive.\n");
		PatchFileIO::add_all_to_patchlist(usbdrive_, patch_list_);
		pr_trace("USB Patchlist updated. filelist data: %p, size: %d.\n", filelist_.usb.data(), filelist_.usb.size());
	}

	uint32_t load_patch_file(Volume vol, uint32_t patch_id) {
		auto filename = patch_list_.get_patch_filename(vol, patch_id);
		pr_dbg("load_patch_file() patch_id=%d vol=%d name=%.31s\n", patch_id, (uint32_t)vol, filename.data());

		bool ok = false;
		std::span<char> raw_patch = raw_patch_buffer_;
		switch (vol) {
			case Volume::NorFlash:
				ok = PatchFileIO::read_file(raw_patch, norflash_, filename);
				break;
			case Volume::SDCard:
				ok = PatchFileIO::read_file(raw_patch, sdcard_, filename);
				break;
			case Volume::USB:
				ok = PatchFileIO::read_file(raw_patch, usbdrive_, filename);
				break;
			default:
				break;
		}

		if (!ok) {
			pr_warn("Could not load patch id %d\n", patch_id);
			return 0;
		}

		pr_dbg("Read patch id %d, %d bytes\n", patch_id, raw_patch.size_bytes());
		return raw_patch.size_bytes();
	}
};

} // namespace MetaModule
