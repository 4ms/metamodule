#pragma once
#include "conf/qspi_flash_conf.hh"
#include "conf/sdcard_conf.hh"
#include "core_intercom/intercore_message.hh"
#include "core_intercom/shared_memory.hh"
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
#include <optional>

namespace MetaModule
{

// PatchStorage manages all patch filesystems <--> PatchList
class PatchStorage {

	using PatchVolFileIO = LfsFileIO<PatchVolFlashOffset, PatchVolFlashSize>;

	FatFileIO &sdcard_;

	FatFileIO &usbdrive_;

	mdrivlib::QSpiFlash flash_{qspi_patchflash_conf};
	PatchVolFileIO norflash_{flash_};

	PollChange usb_changes_{1000};
	PollChange norflash_changes_{1000};
	PollChange sd_changes_{1000};

	RamDiskOps ramdisk_ops{*SharedMemoryS::ptrs.ramdrive};
	FatFileIO ramdisk_{&ramdisk_ops, Volume::RamDisk};

	using enum IntercoreStorageMessage::MessageType;

public:
	PatchStorage(FatFileIO &sdcard_fileio, FatFileIO &usb_fileio)
		: sdcard_{sdcard_fileio}
		, usbdrive_{usb_fileio} {

		// NOR Flash: if it's unformatted, put default patches there
		auto status = norflash_.initialize();
		if (status == PatchVolFileIO::Status::LFSError) {
			status = norflash_.reformat();
		}
		if (status == PatchVolFileIO::Status::NewlyFormatted) {
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

	bool write_file(Volume vol, std::string_view filename, std::span<const char> data) {
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

	bool write_file(Volume vol, std::string_view filename, std::span<const uint8_t> data) {
		return write_file(vol, filename, {(const char *)data.data(), data.size()});
	}

	std::optional<IntercoreStorageMessage> handle_message(const IntercoreStorageMessage &message) {

		if (message.message_type == RequestRefreshPatchList) {

			IntercoreStorageMessage result{.message_type = PatchListUnchanged};

			auto *patch_dir_list_ = message.patch_dir_list;

			if (patch_dir_list_) {
				bool force_sd_refresh =
					message.force_refresh && (message.vol_id == Volume::SDCard || message.vol_id == Volume::MaxVolumes);

				bool force_usb_refresh =
					message.force_refresh && (message.vol_id == Volume::USB || message.vol_id == Volume::MaxVolumes);

				bool force_nor_refresh = message.force_refresh &&
										 (message.vol_id == Volume::NorFlash || message.vol_id == Volume::MaxVolumes);

				poll_media_change();

				if (sd_changes_.take_change() || force_sd_refresh) {
					patch_dir_list_->clear_patches(Volume::SDCard);

					if (sdcard_.is_mounted())
						PatchFileIO::add_directory(sdcard_, patch_dir_list_->volume_root(Volume::SDCard));

					result.message_type = PatchListChanged;
				}

				if (usb_changes_.take_change() || force_usb_refresh) {
					patch_dir_list_->clear_patches(Volume::USB);

					if (usbdrive_.is_mounted())
						PatchFileIO::add_directory(usbdrive_, patch_dir_list_->volume_root(Volume::USB));

					result.message_type = PatchListChanged;
				}

				if (norflash_changes_.take_change() || force_nor_refresh) {
					patch_dir_list_->clear_patches(Volume::NorFlash);

					PatchFileIO::add_directory(norflash_, patch_dir_list_->volume_root(Volume::NorFlash));

					result.message_type = PatchListChanged;
				}
			}
			return result;
		}

		if (message.message_type == RequestPatchData) {

			IntercoreStorageMessage result{
				.message_type = PatchDataLoadFail,
				.bytes_read = 0,
				.vol_id = message.vol_id,
				.filename = message.filename,
			};

			if ((uint32_t)message.vol_id < (uint32_t)Volume::MaxVolumes) {
				auto bytes_read = load_file(message.buffer, message.vol_id, message.filename);
				if (bytes_read) {
					result.message_type = PatchDataLoaded;
					result.bytes_read = bytes_read;
				}
			}

			return result;
		}

		if (message.message_type == RequestWritePatchData) {
			IntercoreStorageMessage result{.message_type = PatchDataWriteFail};

			if (message.filename.size() > 0 && (uint32_t)message.vol_id < (uint32_t)Volume::MaxVolumes) {
				auto wrote_ok = write_file(message.vol_id, message.filename, message.buffer);
				if (wrote_ok) {
					result.message_type = PatchDataWriteOK;
				}
			}

			return result;
		}

		if (message.message_type == RequestFactoryResetPatches) {
			IntercoreStorageMessage result{.message_type = FactoryResetPatchesDone};
			reload_default_patches();

			return result;
		}

		if (message.message_type == RequestCopyPluginAssets) {
			IntercoreStorageMessage result{};
			bool ok = false;
			std::string path = message.filename;
			ramdisk_.mount_disk();
			switch (message.vol_id) {
				case Volume::NorFlash:
					ok = PatchFileIO::deep_copy_dirs(norflash_, ramdisk_, path);
					break;
				case Volume::SDCard:
					ok = PatchFileIO::deep_copy_dirs(sdcard_, ramdisk_, path);
					break;
				case Volume::USB:
					ok = PatchFileIO::deep_copy_dirs(usbdrive_, ramdisk_, path);
					break;
				default:
					break;
			}

			if (ramdisk_.unmount_drive())
				pr_dbg("Unmounted ramdisk\n");
			else
				pr_err("Failed to unmount ramdisk\n");

			// ramdisk_.print_dir("/", 4);
			result.message_type = ok ? CopyPluginAssetsOK : CopyPluginAssetsFail;

			return result;
		}

		if (message.message_type == RequestDeleteFile) {
			IntercoreStorageMessage result{.message_type = DeleteFileFailed};

			if (message.filename.size() > 0 && (uint32_t)message.vol_id < (uint32_t)Volume::MaxVolumes) {
				if (delete_file(message.vol_id, message.filename)) {
					result.message_type = DeleteFileSuccess;
				}
			}

			return result;
		}

		return std::nullopt;
	}

	PatchDirList getPatchList() {
		PatchDirList patch_dir_list_;

		if (sdcard_.is_mounted())
			PatchFileIO::add_directory(sdcard_, patch_dir_list_.volume_root(Volume::SDCard));

		if (usbdrive_.is_mounted())
			PatchFileIO::add_directory(usbdrive_, patch_dir_list_.volume_root(Volume::USB));

		PatchFileIO::add_directory(norflash_, patch_dir_list_.volume_root(Volume::NorFlash));

		return patch_dir_list_;
	}

private:
	void poll_media_change() {
		sd_changes_.poll(HAL_GetTick(), [this] { return sdcard_.is_mounted(); });
		usb_changes_.poll(HAL_GetTick(), [this] { return usbdrive_.is_mounted(); });
	}

	uint32_t load_file(std::span<char> buffer, Volume vol, std::string_view filename) {

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

	bool delete_file(Volume vol, std::string_view filename) {
		if (vol == Volume::USB) {
			auto success = usbdrive_.delete_file(filename);
			if (success) {
				usb_changes_.reset();
			}
			return success;

		} else if (vol == Volume::SDCard) {
			auto success = sdcard_.delete_file(filename);
			if (success) {
				sd_changes_.reset();
			}
			return success;

		} else if (vol == Volume::NorFlash) {
			auto success = norflash_.delete_file(filename);
			if (success) {
				norflash_changes_.reset();
			}
			return success;

		} else {
			pr_err("No volume given\n");
			return false;
		}
	}
};

} // namespace MetaModule
