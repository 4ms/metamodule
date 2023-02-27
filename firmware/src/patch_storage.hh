#pragma once

#include "conf/qspi_flash_conf.hh"
#include "conf/sdcard_conf.hh"
#include "fatfs/fat_file_io.hh"
#include "fatfs/ramdisk_ops.hh"
#include "fatfs/sdcard_ops.hh"
#include "inter_core_comm.hh"
#include "littlefs/norflash_lfs.hh"
#include "patch_fileio.hh"
#include "qspi_flash_driver.hh"
#include "util/edge_detector.hh"
#include "volumes.hh"

// - Ship with some patches on NORFlash
// - Scan for patches on USB-C thumb drive and SD Card
// - Don't use RAMDisk USB
// - In Patch View, user can click "Save" or "copy" and give the patch a name and destination (including NORFlash)
// - In Patch List, patches show their location

namespace MetaModule
{
// PatchStorage manages all patch filesystems <--> PatchList
class PatchStorage {

	SDCardOps<SDCardConf> sdcard_ops_;
	FatFileIO sdcard_{&sdcard_ops_, Volume::SDCard};
	EdgeDetector sdcard_mounted_;
	bool sdcard_needs_rescan_ = true;
	// bool sdcard_mounted_ = false;

	uint32_t last_poll_tm_;

	mdrivlib::QSpiFlash flash_{qspi_patchflash_conf};
	LfsFileIO norflash_{flash_};

	FatFileIO &usbdrive_;
	EdgeDetector usbdrive_mounted_;
	bool usbdrive_needs_rescan_ = true;

	using InterCoreComm2 = InterCoreComm<ICCCoreType::Responder>;
	using enum InterCoreCommMessage::MessageType;
	InterCoreComm2 comm_;
	InterCoreCommMessage pending_send_message{.message_type = None};

	PatchList patch_list_;

	const std::span<char> &raw_patch_buffer_;

	PatchFileList &filelist_;

public:
	PatchStorage(std::span<char> &raw_patch_buffer,
				 volatile InterCoreCommMessage &shared_message,
				 PatchFileList &filelist,
				 FatFileIO &usb_fileio,
				 bool reset_to_factory_patches = false)
		: usbdrive_{usb_fileio}
		, comm_{shared_message}
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
			sdcard_needs_rescan_ = true;
		}
		filelist_.sdcard = patch_list_.get_patchfile_list(Volume::SDCard);

		usbdrive_.mount_disk();
		if (usbdrive_.is_mounted()) {
			patch_list_.clear_patches(Volume::USB);
			PatchFileIO::add_all_to_patchlist(usbdrive_, patch_list_);
			usbdrive_needs_rescan_ = true;
		}
		filelist_.usb = patch_list_.get_patchfile_list(Volume::USB);

		poll_media_change();
	}

	void handle_messages() {
		if (pending_send_message.message_type != None) {
			// Keep trying to send message until suceeds
			// TODO: why would this fail? The answer informs us how to handle this situation
			if (comm_.send_message(pending_send_message))
				pending_send_message.message_type = None;
		}

		auto message = comm_.get_new_message();

		if (message.message_type == RequestRefreshPatchList) {
			if (sdcard_needs_rescan_) {
				patch_list_.clear_patches(Volume::SDCard);
				if (sdcard_.is_mounted())
					rescan_sdcard();
				filelist_.sdcard = patch_list_.get_patchfile_list(Volume::SDCard);
			}
			if (usbdrive_needs_rescan_) {
				patch_list_.clear_patches(Volume::USB);
				if (usbdrive_.is_mounted())
					rescan_usbdrive();
				filelist_.usb = patch_list_.get_patchfile_list(Volume::USB);
			}

			if (sdcard_needs_rescan_ | usbdrive_needs_rescan_) {
				sdcard_needs_rescan_ = false;
				usbdrive_needs_rescan_ = false;
				pending_send_message.message_type = PatchListChanged;
			} else
				pending_send_message.message_type = PatchListUnchanged;
		}

		if (message.message_type == RequestPatchData) {
			pending_send_message.message_type = PatchDataLoadFail;
			pending_send_message.patch_id = message.patch_id;
			pending_send_message.vol_id = message.vol_id;
			pending_send_message.bytes_read = 0;

			if (message.patch_id < patch_list_.num_patches() && message.vol_id < (uint32_t)Volume::MaxVolumes) {
				auto bytes_read = load_patch_file((Volume)message.vol_id, message.patch_id);
				if (bytes_read) {
					pending_send_message.message_type = PatchDataLoaded;
					pending_send_message.bytes_read = bytes_read;
				}
			}
		}

		uint32_t now = HAL_GetTick();
		if (now - last_poll_tm_ > 2000) { //poll media once per second
			last_poll_tm_ = now;
			poll_media_change();
			// printf_("SD Card mounted: %d\n", sdcard.is_mounted());
			// printf_("USB Drive mounted: %d\n", usbdrive.is_mounted());
		}
	}

private:
	void poll_media_change() {
		sdcard_mounted_.update(sdcard_.is_mounted());
		if (sdcard_mounted_.changed())
			sdcard_needs_rescan_ = true;

		usbdrive_mounted_.update(usbdrive_.is_mounted());
		if (usbdrive_mounted_.changed())
			usbdrive_needs_rescan_ = true;
	}

	void rescan_sdcard() {
		printf_("Updating patchlist from SD Card.\n");
		PatchFileIO::add_all_to_patchlist(sdcard_, patch_list_);
		printf_(
			"SD Patchlist updated. filelist data: %p, size: %d.\n", filelist_.sdcard.data(), filelist_.sdcard.size());
	}

	void rescan_usbdrive() {
		printf_("Updating patchlist from USB Drive.\n");
		PatchFileIO::add_all_to_patchlist(usbdrive_, patch_list_);
		printf_("USB Patchlist updated. filelist data: %p, size: %d.\n", filelist_.usb.data(), filelist_.usb.size());
	}

	// std::optional<uint32_t> find_by_name(std::string_view &patchname) const {
	// 	return patch_list_.find_by_name(patchname);
	// }

	uint32_t load_patch_file(Volume vol, uint32_t patch_id) {
		auto filename = patch_list_.get_patch_filename(vol, patch_id);
		printf("load_patch_file() patch_id=%d vol=%d name=%.31s\n", patch_id, vol, filename.data());

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
			printf_("Could not load patch id %d\n", patch_id);
			return 0;
		}

		printf_("Read patch id %d, %d bytes\n", patch_id, raw_patch.size_bytes());
		return raw_patch.size_bytes();
	}
};

} // namespace MetaModule
