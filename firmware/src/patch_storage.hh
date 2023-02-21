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
#include "shared_memory.hh"
#include "volumes.hh"

// - Ship with some patches on NORFlash
// - Scan for patches on USB-C thumb drive and SD Card
// - Don't use RAMDisk USB
// - In Patch View, user can click "Save" or "copy" and give the patch a name and destination (including NORFlash)
// - In Patch List, patches show their location

// TODO: we currently do all SD Card accesses in the UI thread... would be better to do it in main thread?
// UI could send a request (patch_storage.request_load_view_patch(id)) then poll (patch_list.is_view_patch_ready())

// PatchStorage could live 100% on M4? Not ViewPatch, just PatchList and FileIOs
// -- use array, not vector for patch_list (replace clear() and push_back()) -- instead of erase_if(), use a separate array for each Volume
// -- points of contact to A7 would be:
// 		-- PatchSelPage scans patch_list: requests a lock, then scan the patch_list, releases lock
//		-- UI thread calls poll_media_change() periodically
//		-- UI thread calls rescan_sdcard/USBdevice() when needed
//      -- on boot --> playloader calls patch_list.find_by_name() [could busy wait, or scan list itself]
//      -- on boot and on select new patch --> PatchFileIO::load_patch_data() should be passed a raw buffer, not PatchData&. Then A7 will convert to yaml
// We'd need a PatchStorage proxy to live on A7 and communicate with M4

// OR UI thread could spawn PatchStorage::rescan_sdcard() onto Core 2, and that's all the heavy lifting needed
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

	// RamDiskOps ramdisk_ops{StaticBuffers::virtdrive};
	// FatFileIO ramdisk{&ramdisk_ops, Volume::RamDisk};

	using InterCoreComm2 = InterCoreComm<ICCNum::Core2>;
	using enum InterCoreComm2::Message;
	InterCoreComm2 comm_;
	InterCoreComm2::Message pending_send_message = None;

	uint32_t view_patch_id_;
	PatchData view_patch_;

	PatchList patch_list_;

public:
	PatchStorage(bool reset_to_factory_patches = false) {
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
		sdcard_needs_rescan_ = false;

		//if (usb_drive_mounted)
		//	PatchFileIO::add_all_to_patchlist(usbdrive, patch_list_);

		auto filelist = patch_list_.get_patchfile_list();
		SharedMemory::write_address_of(&filelist, SharedMemory::PatchListLocation);
	}

	void handle_messages() {
		if (pending_send_message != None) {
			// Keep trying to send message until suceeds
			// TODO: why would this fail? The answer informs us how to handle this situation
			if (comm_.send_message(pending_send_message))
				pending_send_message = None;
		}

		auto message = comm_.get_last_message();
		if (message == RequestRefreshPatchList) {
			pending_send_message = PatchListUnchanged;
			if (sdcard_needs_rescan_) {
				poll_media_change();
				rescan_sdcard();
				sdcard_needs_rescan_ = false;
				pending_send_message = PatchListChanged;
			}
			// if (usb_needs_rescan_) ...
		}

		uint32_t now = HAL_GetTick();
		if (now - last_poll_tm_ > 1000) { //poll media once per second
			last_poll_tm_ = now;
			poll_media_change();
		}
	}

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
		patch_list_.mark_modified();
		printf_("Patchlist updated.\n");
	}

	void load_view_patch(std::string_view &patchname) {
		if (auto id = patch_list_.find_by_name(patchname))
			load_view_patch(id.value());
	}

	std::optional<uint32_t> find_by_name(std::string_view &patchname) {
		return patch_list_.find_by_name(patchname);
	}

	void load_view_patch(uint32_t patch_id) {
		bool ok = false;
		auto filename = patch_list_.get_patch_filename(patch_id);
		printf("load_view_patch %d %.31s\n", patch_id, filename.data());

		auto load_patch_data = [&](auto &fileio) -> bool {
			return PatchFileIO::load_patch_data(view_patch_, fileio, filename);
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
			return;
		}

		view_patch_id_ = patch_id;
	}

	uint32_t get_view_patch_id() {
		return view_patch_id_;
	}

	PatchData &get_view_patch() {
		return view_patch_;
	}

	void update_norflash_from_ramdisk() {
		// patch_list.lock();
		printf_("NOR Flash writeback begun.\r\n");

		// ramdisk.unmount_disk();

		// Must invalidate the cache because M4 wrote to it???
		// SystemCache::invalidate_dcache_by_range(StaticBuffers::virtdrive.virtdrive,
		// 										sizeof(StaticBuffers::virtdrive.virtdrive));
		// if (PatchFileIO::copy_patches_from_to(ramdisk, norflash, PatchFileIO::FileFilter::NewerTimestamp)) {
		// 	printf_("NOR Flash writeback done. Refreshing patch list.\r\n");
		// 	// PatchFileIO::overwrite_patchlist(ramdisk, patch_list);
		// 	patch_list.mark_modified();
		// } else {
		// 	printf_("NOR Flash writeback failed!\r\n");
		// }
		// // patch_list.unlock();
		printf_("RamDisk Available to M4\n");
	}
};

} // namespace MetaModule
