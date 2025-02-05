#pragma once
#include "conf/qspi_flash_conf.hh"
#include "core_intercom/intercore_message.hh"
#include "core_intercom/shared_memory.hh"
#include "drivers/qspi_flash_driver.hh"
#include "fs/fatfs/fat_file_io.hh"
#include "fs/fatfs/ramdisk_ops.hh"
#include "fs/helpers.hh"
#include "fs/littlefs/norflash_lfs.hh"
#include "fs/volumes.hh"
#include "patch_file/patch_fileio.hh"
#include "patch_file/patch_list_helper.hh"
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

	PollChange usb_changes_{300};
	PollChange norflash_changes_{300};
	PollChange sd_changes_{300};

	RamDiskOps ramdisk_ops{*SharedMemoryS::ptrs.ramdrive};
	FatFileIO ramdisk_{&ramdisk_ops, Volume::RamDisk};

	using enum IntercoreStorageMessage::MessageType;

	PatchDirList patch_dir_list_;
	PatchListHelper patch_list_helper_;
	bool patch_list_changed_ = false;
	bool patch_list_changed_wifi_ = false;

public:
	PatchStorage(FatFileIO &sdcard_fileio, FatFileIO &usb_fileio)
		: sdcard_{sdcard_fileio}
		, usbdrive_{usb_fileio}
		, patch_list_helper_{patch_dir_list_} {

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

		refresh_patch_list();
	}

	void reload_default_patches() {
		norflash_.reformat();
		PatchFileIO::create_default_patches(norflash_);
	}

	// returns timestamp
	uint32_t write_file(Volume vol, std::string_view filename, std::span<const char> data) {
		bool success = false;

		if (vol == Volume::USB) {
			success = PatchFileIO::write_file(data, usbdrive_, filename);

		} else if (vol == Volume::SDCard) {
			success = PatchFileIO::write_file(data, sdcard_, filename);

		} else if (vol == Volume::NorFlash) {
			success = PatchFileIO::write_file(data, norflash_, filename);
		}

		if (success) {
			return add_or_replace_file(vol, filename, {data.data(), 64});
		}
		return 0;
	}

	// returns timestamp
	uint32_t write_file(Volume vol, std::string_view filename, std::span<const uint8_t> data) {
		return write_file(vol, filename, {(const char *)data.data(), data.size()});
	}

	std::optional<IntercoreStorageMessage> handle_message(const IntercoreStorageMessage &message) {

		if (message.message_type == RequestRefreshPatchList) {

			IntercoreStorageMessage result{.message_type = PatchListUnchanged};

			if (patch_list_changed_) {
				// Make a copy
				patch_list_helper_.copy_patchlist(message.patch_dir_list);

				result.message_type = patch_list_changed_ ? PatchListChanged : PatchListUnchanged;
				patch_list_changed_ = false;
			}
			//TODO: events?
			return result;
		}

		if (message.message_type == RequestLoadFile) {

			IntercoreStorageMessage result{
				.message_type = LoadFileFailed,
				.bytes_read = 0,
				.vol_id = message.vol_id,
				.filename = message.filename,
			};

			if ((uint32_t)message.vol_id < (uint32_t)Volume::MaxVolumes) {
				auto bytes_read = load_file(message.buffer, message.vol_id, message.filename, &result.timestamp);
				if (bytes_read) {
					result.message_type = LoadFileOK;
					result.bytes_read = bytes_read;
				}
			}

			return result;
		}

		if (message.message_type == RequestWriteFile) {
			IntercoreStorageMessage result{.message_type = WriteFileFail};

			if (message.filename.size() > 0 && (uint32_t)message.vol_id < (uint32_t)Volume::MaxVolumes) {
				auto timestamp = write_file(message.vol_id, message.filename, message.buffer);
				if (timestamp != 0) {
					result.length = message.buffer.size();
					result.timestamp = timestamp;
					result.message_type = WriteFileOK;
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

			if (!ramdisk_.unmount_drive())
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

		if (message.message_type == RequestFileInfo) {
			IntercoreStorageMessage result{.message_type = FileInfoFailed};

			if (auto *patchfile = patch_list_helper_.find_fileinfo(message.vol_id, message.filename)) {
				result.timestamp = patchfile->timestamp;
				result.length = patchfile->filesize;
				result.message_type = FileInfoSuccess;
			}

			return result;
		}

		if (message.message_type == RequestDirEntries) {
			IntercoreStorageMessage result{.message_type = DirEntriesFailed};

			auto path = message.filename;
			auto exts = message.dest_filename;
			auto *dir_tree = message.dir_entries;
			dir_tree->files.clear();
			dir_tree->dirs.clear();

			if (message.vol_id == Volume::MaxVolumes) {
				if (sdcard_.is_mounted()) {
					dir_tree->dirs.push_back("SD Card:");
				}
				if (usbdrive_.is_mounted()) {
					dir_tree->dirs.push_back("USB:");
				}

				// Hide Internal. TODO: allow an option to show it?
				// dir_tree->dirs.push_back("Internal:");

				result.message_type = DirEntriesSuccess;

			} else if (message.vol_id == Volume::USB) {
				if (usbdrive_.is_mounted()) {
					get_dir_entries(usbdrive_, path, exts, dir_tree);
					result.message_type = DirEntriesSuccess;
				}

			} else if (message.vol_id == Volume::SDCard) {
				if (sdcard_.is_mounted()) {
					get_dir_entries(sdcard_, path, exts, dir_tree);
					result.message_type = DirEntriesSuccess;
				}

			} else if (message.vol_id == Volume::NorFlash) {
				get_dir_entries(norflash_, path, exts, dir_tree);
				result.message_type = DirEntriesSuccess;
			}

			return result;
		}

		return std::nullopt;
	}

	PatchDirList get_patch_list() {
		return patch_dir_list_;
	}

	bool has_media_changed() {
		auto result = patch_list_changed_wifi_;
		patch_list_changed_wifi_ = false;
		return result;
	}

	// Refreshes patchlist for any volume which was just mounted or unmounted
	void refresh_patch_list() {
		sd_changes_.poll(HAL_GetTick(), [this] { return sdcard_.is_mounted(); });
		usb_changes_.poll(HAL_GetTick(), [this] { return usbdrive_.is_mounted(); });

		auto check_disk = [this](auto &changes, auto &diskio, Volume vol) {
			bool mounted_changed = changes.take_change();
			if (mounted_changed) {
				patch_dir_list_.clear_patches(vol);

				if (diskio.is_mounted()) {
					PatchFileIO::add_directory(diskio, patch_dir_list_.volume_root(vol));
					patch_dir_list_.mark_mounted(vol, true);
				} else {
					patch_dir_list_.mark_mounted(vol, false);
				}

				patch_list_changed_ = true;
				patch_list_changed_wifi_ = true;
			}
		};

		check_disk(sd_changes_, sdcard_, Volume::SDCard);
		check_disk(usb_changes_, usbdrive_, Volume::USB);
		check_disk(norflash_changes_, norflash_, Volume::NorFlash);
	}

private:
	// returns timestamp
	uint32_t add_or_replace_file(Volume vol, std::string_view filename, std::string_view header) {
		uint32_t filesize{};
		uint32_t timestamp{};

		if (vol == Volume::USB) {
			filesize = usbdrive_.get_file_size(filename);
			timestamp = usbdrive_.get_file_timestamp(filename);

		} else if (vol == Volume::SDCard) {
			filesize = sdcard_.get_file_size(filename);
			timestamp = sdcard_.get_file_timestamp(filename);

		} else if (vol == Volume::NorFlash) {
			filesize = norflash_.get_file_size(filename);
			timestamp = norflash_.get_file_timestamp(filename);
		}

		auto patchname = PatchFileIO::extract_patch_name(header);
		patch_list_helper_.add_file(vol, filename, patchname, filesize, timestamp);

		patch_list_changed_ = true;
		patch_list_changed_wifi_ = true;
		return timestamp;
	}

	uint32_t load_file(std::span<char> buffer, Volume vol, std::string_view filename, uint32_t *timestamp) {

		bool ok = false;
		switch (vol) {
			case Volume::NorFlash:
				ok = PatchFileIO::read_file(buffer, norflash_, filename, timestamp);
				break;
			case Volume::SDCard:
				ok = PatchFileIO::read_file(buffer, sdcard_, filename, timestamp);
				break;
			case Volume::USB:
				ok = PatchFileIO::read_file(buffer, usbdrive_, filename, timestamp);
				break;
			default:
				break;
		}

		if (!ok) {
			pr_warn("M4: Could not load file id %.*s\n", (int)filename.size(), filename.data());
			return 0;
		}

		// pr_dbg("M4: Read file %.*s, %d bytes\n", (int)filename.size(), filename.data(), buffer.size_bytes());
		return buffer.size_bytes();
	}

	bool delete_file(Volume vol, std::string_view filename) {
		bool success = false;

		if (vol == Volume::USB) {
			success = usbdrive_.delete_file(filename);

		} else if (vol == Volume::SDCard) {
			success = sdcard_.delete_file(filename);

		} else if (vol == Volume::NorFlash) {
			success = norflash_.delete_file(filename);

		} else {
			pr_err("Invalid volume given to delete_file()\n");
		}

		if (success) {
			patch_list_helper_.remove_file(vol, filename);

			patch_list_changed_ = true;
			patch_list_changed_wifi_ = true;
		}

		return success;
	}
};

} // namespace MetaModule
