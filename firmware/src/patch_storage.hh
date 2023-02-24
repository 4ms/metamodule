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
	FatFileIO sdcard{&sdcard_ops_, Volume::SDCard};
	bool sdcard_mounted_ = false;
	bool sdcard_needs_rescan_ = true;
	uint32_t last_poll_tm_;

	mdrivlib::QSpiFlash flash_{qspi_patchflash_conf};
	LfsFileIO norflash_{flash_};

	FatFileIO &usbdrive;

	// RamDiskOps ramdisk_ops{StaticBuffers::virtdrive};
	// FatFileIO ramdisk{&ramdisk_ops, Volume::RamDisk};

	using InterCoreComm2 = InterCoreComm<ICCCoreType::Responder>;
	using enum InterCoreCommMessage::MessageType;
	InterCoreComm2 comm_;
	InterCoreCommMessage pending_send_message{.message_type = None};

	PatchList patch_list_;

	const std::span<char> &raw_patch_buffer_;
	std::span<PatchFile> &filelist_;

public:
	PatchStorage(std::span<char> &raw_patch_buffer,
				 volatile InterCoreCommMessage &shared_message,
				 std::span<PatchFile> &filelist,
				 FatFileIO &usb_fileio,
				 bool reset_to_factory_patches = false)
		: usbdrive{usb_fileio}
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
		patch_list_.clear_all_patches();
		PatchFileIO::add_all_to_patchlist(norflash_, patch_list_);

		poll_media_change();
		if (sdcard_mounted_)
			PatchFileIO::add_all_to_patchlist(sdcard, patch_list_);
		filelist = patch_list_.get_patchfile_list();
		sdcard_needs_rescan_ = true;

		//if (usb_drive_mounted)
		PatchFileIO::add_all_to_patchlist(usbdrive, patch_list_);
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
			pending_send_message.message_type = PatchListUnchanged;
			if (sdcard_needs_rescan_) {
				poll_media_change();
				if (sdcard_mounted_)
					rescan_sdcard();
				else
					printf_("SD Card not mounted, can't rescan\n");
				sdcard_needs_rescan_ = false;
				pending_send_message.message_type = PatchListChanged;
			}
			printf_("M4 sending response: %d\n", pending_send_message.message_type);
			// if (usb_needs_rescan_) ...
		}

		if (message.message_type == RequestPatchData) {
			pending_send_message.message_type = PatchDataLoadFail;
			pending_send_message.patch_id = message.patch_id;
			pending_send_message.bytes_read = 0;

			if (message.patch_id < patch_list_.num_patches()) {
				auto bytes_read = load_patch_file(message.patch_id);
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
		}
	}

private:
	void poll_media_change() {
		bool was_sdcard_mounted = sdcard_mounted_;
		uint8_t card_detected;
		auto err = sdcard_ops_.ioctl(MMC_GET_SDSTAT, &card_detected);
		if (err || !card_detected)
			sdcard_mounted_ = false;
		else
			sdcard_mounted_ = true;
		if (was_sdcard_mounted == false && sdcard_mounted_ == true) {
			sdcard_needs_rescan_ = true;
		}
	}

	void rescan_sdcard() {
		printf_("Updating patchlist from SD Card.\n");
		patch_list_.clear_patches_from(Volume::SDCard);
		PatchFileIO::add_all_to_patchlist(sdcard, patch_list_);
		filelist_ = patch_list_.get_patchfile_list();
		printf_("Patchlist updated. filelist data: %p, size: %d.\n", filelist_.data(), filelist_.size());
	}

	// void load_view_patch(std::string_view &patchname) {
	// 	if (auto id = patch_list_.find_by_name(patchname))
	// 		load_view_patch(id.value());
	// }

	std::optional<uint32_t> find_by_name(std::string_view &patchname) const {
		return patch_list_.find_by_name(patchname);
	}

	uint32_t load_patch_file(uint32_t patch_id) {
		bool ok = false;
		auto filename = patch_list_.get_patch_filename(patch_id);
		printf("load_view_patch %d %.31s\n", patch_id, filename.data());
		std::span<char> raw_patch = raw_patch_buffer_;

		auto load_patch_data = [&](auto &fileio) -> bool {
			return PatchFileIO::read_file(raw_patch, fileio, filename);
		};

		switch (patch_list_.get_patch_vol(patch_id)) {
			case Volume::NorFlash:
				ok = load_patch_data(norflash_);
				break;
			case Volume::SDCard:
				ok = load_patch_data(sdcard);
				break;
			case Volume::RamDisk:
				// ok = load_patch_data(ramdisk);
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
