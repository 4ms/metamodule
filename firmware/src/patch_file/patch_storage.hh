#pragma once
#include "conf/qspi_flash_conf.hh"
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
#include "patch_file/patch_listio.hh"
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
	bool patch_list_changed_ = false;
	bool patch_list_changed_wifi_ = false;

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

		refresh_patch_list();
	}

	void reload_default_patches() {
		norflash_.reformat();
		PatchFileIO::create_default_patches(norflash_);
	}

	bool write_file(Volume vol, std::string_view filename, std::span<const char> data) {
		bool success = false;

		if (vol == Volume::USB) {
			success = PatchFileIO::write_file(data, usbdrive_, filename);

		} else if (vol == Volume::SDCard) {
			success = PatchFileIO::write_file(data, sdcard_, filename);

		} else if (vol == Volume::NorFlash) {
			success = PatchFileIO::write_file(data, norflash_, filename);
		}

		if (success) {
			add_or_replace_file(vol, filename, {data.data(), 64});
		}
		return success;
	}

	bool write_file(Volume vol, std::string_view filename, std::span<const uint8_t> data) {
		return write_file(vol, filename, {(const char *)data.data(), data.size()});
	}

	std::optional<IntercoreStorageMessage> handle_message(const IntercoreStorageMessage &message) {

		if (message.message_type == RequestRefreshPatchList) {

			using VolEvent = IntercoreStorageMessage::VolEvent;

			IntercoreStorageMessage result{
				.message_type = PatchListUnchanged,
				.USBEvent = VolEvent::None,
				.SDEvent = VolEvent::None,
				.NorFlashEvent = VolEvent::None,
			};

			if (patch_list_changed_) {

				// pr_dbg("M4: Copying Patch dir list %p => %p\n", &patch_dir_list_, message.patch_dir_list);

				// Make a copy
				// *(message.patch_dir_list) = patch_dir_list_;
				message.patch_dir_list->clear_patches(Volume::USB);
				message.patch_dir_list->clear_patches(Volume::SDCard);
				message.patch_dir_list->clear_patches(Volume::NorFlash);

				for (auto i = 0u; auto m : patch_dir_list_.mounted)
					message.patch_dir_list->mounted[i++] = m;

				for (auto i = 0u; auto const &volroot : patch_dir_list_.vol_root) {
					auto &dstroot = message.patch_dir_list->vol_root[i++];
					dstroot.name = volroot.name;
					// pr_dbg("Vol: %s\n", dstroot.name.c_str());

					for (auto const &file : volroot.files) {
						dstroot.files.emplace_back(
							file.filename, file.filesize, file.timestamp, file.patchname, file.link_vol);
						// pr_dbg("%s\n", dstroot.files.back().filename.c_str());
					}

					for (auto &dir : volroot.dirs) {
						auto &dstdir = dstroot.dirs.emplace_back();
						dstdir.name = dir.name;
						// pr_dbg("Dir: %s\n", dstdir.name.c_str());

						for (auto const &file : dir.files) {
							dstdir.files.emplace_back(
								file.filename, file.filesize, file.timestamp, file.patchname, file.link_vol);
							// pr_dbg("  %s\n", dstdir.files.back().filename.c_str());
						}
					}
				}

				// pr_dbg("M4: Done\n");

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
				auto bytes_read = load_file(message.buffer, message.vol_id, message.filename);
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
				auto wrote_ok = write_file(message.vol_id, message.filename, message.buffer);
				if (wrote_ok) {
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

		bool sd_mounted_changed = sd_changes_.take_change();
		if (sd_mounted_changed) {
			patch_dir_list_.clear_patches(Volume::SDCard);

			if (sdcard_.is_mounted()) {
				PatchFileIO::add_directory(sdcard_, patch_dir_list_.volume_root(Volume::SDCard));
				patch_dir_list_.mark_mounted(Volume::SDCard, true);
			} else {
				patch_dir_list_.mark_mounted(Volume::SDCard, false);
			}

			patch_list_changed_ = true;
			patch_list_changed_wifi_ = true;
		}

		bool usb_mounted_changed = usb_changes_.take_change();
		if (usb_mounted_changed) {
			patch_dir_list_.clear_patches(Volume::USB);

			if (usbdrive_.is_mounted()) {
				PatchFileIO::add_directory(usbdrive_, patch_dir_list_.volume_root(Volume::USB));
				patch_dir_list_.mark_mounted(Volume::USB, true);
			} else {
				patch_dir_list_.mark_mounted(Volume::USB, false);
			}
			patch_list_changed_ = true;
			patch_list_changed_wifi_ = true;
		}

		bool norflash_mounted_changed = norflash_changes_.take_change();
		if (norflash_mounted_changed) {
			patch_dir_list_.mark_mounted(Volume::NorFlash, true);
			patch_dir_list_.clear_patches(Volume::NorFlash);

			PatchFileIO::add_directory(norflash_, patch_dir_list_.volume_root(Volume::NorFlash));
			// if (norflash_changed)
			// 	result.NorFlashEvent = VolEvent::Mounted;

			patch_list_changed_ = true;
			patch_list_changed_wifi_ = true;
		}
	}

private:
	void add_or_replace_file(Volume vol, std::string_view filename, std::string_view header) {
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
		PatchListIO::add_file(patch_dir_list_, vol, filename, patchname, filesize, timestamp);

		patch_list_changed_ = true;
		patch_list_changed_wifi_ = true;
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
			PatchListIO::remove_file(patch_dir_list_, vol, filename);

			patch_list_changed_ = true;
			patch_list_changed_wifi_ = true;
		}

		return success;
	}
};

} // namespace MetaModule
