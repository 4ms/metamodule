#pragma once
#include "../src/core_intercom/intercore_message.hh"
#include "dynload/plugin_file_scan.hh"
#include "fat_file_io.hh"
#include "fs/volumes.hh"
#include "fw_update/update_path.hh"
#include "patch_file/host_file_io.hh"
#include "patch_file/patch_dir_list.hh"
#include "patch_file/patch_fileio.hh"
#include "patch_file/patch_location.hh"
#include <cstdint>
#include <string_view>

namespace MetaModule
{

struct SimulatorPatchStorage {

	SimulatorPatchStorage(std::string_view sd_path,
						  std::string_view flash_path,
						  PatchDirList &patch_dir_list_,
						  FatFileIO &ramdisk)
		: sd_hostfs{MetaModule::Volume::SDCard, sd_path}
		, flash_hostfs{MetaModule::Volume::NorFlash, flash_path}
		, ramdisk{ramdisk} {
		PatchFileIO::add_directory(sd_hostfs, patch_dir_list_.volume_root(Volume::SDCard));
		PatchFileIO::add_directory(flash_hostfs, patch_dir_list_.volume_root(Volume::NorFlash));
	}

	HostFileIO sd_hostfs;
	HostFileIO flash_hostfs;
	FatFileIO &ramdisk;
};

struct SimulatorFileStorageComm {

	SimulatorFileStorageComm(SimulatorPatchStorage &patch_storage)
		: storage{patch_storage} {
	}

	[[nodiscard]] bool send_message(const IntercoreStorageMessage &msg) {
		using enum IntercoreStorageMessage::MessageType;

		switch (msg.message_type) {
			case RequestLoadFile: {
				requested_view_patch_loc_ = PatchLocation{msg.filename, msg.vol_id};
				raw_patch_data_ = msg.buffer;
				auto bytes_read = load_patch_file(requested_view_patch_loc_);
				reply = {.message_type = bytes_read ? LoadFileOK : LoadFileFailed,
						 .bytes_read = bytes_read,
						 .vol_id = requested_view_patch_loc_.vol,
						 .filename = requested_view_patch_loc_.filename};
			} break;

			case RequestRefreshPatchList: {
				// TODO: Check if anything changed in hostfs

				reply.message_type = PatchListUnchanged;

				auto *patch_dir_list_ = msg.patch_dir_list;

				if (patch_dir_list_) {
					bool force_sd_refresh =
						msg.force_refresh && (msg.vol_id == Volume::SDCard || msg.vol_id == Volume::MaxVolumes);

					if (refresh_required || force_sd_refresh) {
						patch_dir_list_->clear_patches(Volume::SDCard);
						PatchFileIO::add_directory(storage.sd_hostfs, patch_dir_list_->volume_root(Volume::SDCard));
						reply.message_type = PatchListChanged;
					}

					refresh_required = false;
				}
			} break;

			case RequestFirmwareFile: {
				if (find_manifest(storage.sd_hostfs)) {
					reply.message_type = FirmwareFileFound;
					reply.filename.copy(found_filename);
					reply.bytes_read = found_filesize;
					reply.vol_id = Volume::SDCard;
				} else {
					reply = {FirmwareFileFound};
				}
			} break;

			case StartChecksumCompare: {
				reply = {ChecksumMatch}; //TODO: make it fail sometimes?
			} break;

			case RequestPluginFileList: {
				if (find_plugin_files(msg))
					reply = {PluginFileListOK};
				else
					reply = {PluginFileListFail};
			} break;

			case RequestCopyPluginAssets: {
				storage.ramdisk.mount_disk();
				bool ok = PatchFileIO::deep_copy_dirs(storage.sd_hostfs, storage.ramdisk, msg.filename);
				reply.message_type = ok ? CopyPluginAssetsOK : CopyPluginAssetsFail;
			} break;

			case RequestWriteFile: {
				bool ok = false;
				if (msg.vol_id == Volume::SDCard) {
					ok = storage.sd_hostfs.update_or_create_file(msg.filename, msg.buffer);
				} else if (msg.vol_id == Volume::NorFlash) {
					ok = storage.flash_hostfs.update_or_create_file(msg.filename, msg.buffer);
				}

				if (!ok) {
					pr_err("Error writing file!\n");
					reply = {WriteFileFail};
					return false;
				}
				reply = {WriteFileOK};
				// refresh_required = true;
			} break;

			case RequestDeleteFile: {
				bool ok = false;

				if (msg.vol_id == Volume::SDCard)
					ok = storage.sd_hostfs.delete_file(msg.filename);

				if (msg.vol_id == Volume::NorFlash)
					ok = storage.flash_hostfs.delete_file(msg.filename);

				if (!ok) {
					reply = {DeleteFileFailed};
				} else {
					reply = {DeleteFileSuccess};
				}
			} break;

			case RequestFactoryResetPatches: {
				pr_info("Reset to factory patches = no action. (simulator default patches are read-only)\n");
			} break;

			default:
				break;
		}

		return true;
	}

	IntercoreStorageMessage get_new_message() {
		auto r = reply;
		reply = {.message_type = IntercoreStorageMessage::None};
		return r;
	}

private:
	uint32_t load_patch_file(PatchLocation const &loc) {

		bool ok = false;

		if (loc.vol == Volume::SDCard) {
			std::cout << "Trying to load " << loc.filename.c_str() << " from SD Card\n";
			ok = PatchFileIO::read_file(raw_patch_data_, storage.sd_hostfs, loc.filename);
		}

		else if (loc.vol == Volume::NorFlash)
		{
			std::cout << "Trying to load " << loc.filename.c_str() << " from NorFlash\n";
			ok = PatchFileIO::read_file(raw_patch_data_, storage.flash_hostfs, loc.filename);
		}

		//TODO: add USB when we have a usb fileio
		// if (vol == Volume::USB)
		// ok = PatchFileIO::read_file(raw_patch, usbpatchfs_, filename);

		if (!ok) {
			std::cout << "Could not load patch " << loc.filename << " on vol " << (int)loc.vol << "\n";
			return 0;
		}

		// view_patch_loc_ = loc;
		std::cout << "Read patch id " << loc.filename << " " << raw_patch_data_.size_bytes() << " bytes\n";
		return raw_patch_data_.size_bytes();
	}

	bool find_manifest(FileIoC auto &fileio) {
		found_filename.copy(UpdateFileManifestFilename);

		std::vector<char> buffer(16 * 1024);
		auto bytes_read = fileio.read_file(std::string_view(found_filename), buffer);
		if (bytes_read > 0) {
			found_filesize = bytes_read;
			pr_dbg("Found manifest file: %s (%u B)\n", found_filename.c_str(), found_filesize);
			return true;
		}
		return false;
	}

	bool find_plugin_files(const IntercoreStorageMessage &message) {
		message.plugin_file_list->clear();

		bool hostfs_ok = false;
		hostfs_ok = scan_volume(storage.sd_hostfs, *message.plugin_file_list, PluginDirName);
		hostfs_ok |= scan_volume(storage.sd_hostfs, *message.plugin_file_list, "/");

		bool defaultpatchfs_ok = false;
		defaultpatchfs_ok = scan_volume(storage.flash_hostfs, *message.plugin_file_list, PluginDirName);
		defaultpatchfs_ok |= scan_volume(storage.flash_hostfs, *message.plugin_file_list, "/");

		return (hostfs_ok || defaultpatchfs_ok);
	}

private:
	SimulatorPatchStorage &storage;
	PatchLocation requested_view_patch_loc_;

	StaticString<255> found_filename;
	uint32_t found_filesize = 0;

	bool refresh_required = true;

	std::span<char> raw_patch_data_;

	IntercoreStorageMessage reply{.message_type = IntercoreStorageMessage::None};
};

using FileStorageComm = SimulatorFileStorageComm;

} // namespace MetaModule
