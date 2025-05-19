#pragma once
#include "../src/core_intercom/intercore_message.hh"
#include "dynload/plugin_file_scan.hh"
#include "fs/fatfs/fat_file_io.hh"
#include "fs/helpers.hh"
#include "fs/volumes.hh"
#include "fw_update/update_path.hh"
#include "host_file_io.hh"
#include "patch_file/patch_dir_list.hh"
#include "patch_file/patch_fileio.hh"
#include "patch_file/patch_location.hh"
#include <cstdint>
#include <string>
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
		sd_root = sd_path;
		flash_root = flash_path;
	}

	static std::string convert_path_to_host(std::string_view path) {
		if (path.starts_with("sdc:/")) {
			return sd_root + std::string(path.substr(5));

		} else if (path.starts_with("nor:/")) {
			return flash_root + std::string(path.substr(5));

		} else {
			return std::string(path);
		}
	}

	static std::string convert_path_to_mm(std::string_view path) {
		if (path.starts_with(sd_root)) {
			return "sdc:/" + std::string(path.substr(sd_root.length()));

		} else if (path.starts_with(flash_root)) {
			return "nor:/" + std::string(path.substr(sd_root.length()));

		} else {
			return std::string(path);
		}
	}

	HostFileIO sd_hostfs;
	HostFileIO flash_hostfs;
	FatFileIO &ramdisk;

	static inline std::string sd_root;
	static inline std::string flash_root;
};

struct SimulatorFileStorageComm {

	SimulatorFileStorageComm(SimulatorPatchStorage &patch_storage)
		: storage{patch_storage} {
	}

	[[nodiscard]] bool send_message(const IntercoreStorageMessage &msg) {
		try {

			using enum IntercoreStorageMessage::MessageType;

			switch (msg.message_type) {
				case RequestLoadFile: {
					requested_view_patch_loc_ = PatchLocation{msg.filename, msg.vol_id};
					raw_patch_data_ = msg.buffer;
					uint32_t timestamp;
					auto bytes_read = load_patch_file(requested_view_patch_loc_, &timestamp);
					reply = {
						.message_type = bytes_read ? LoadFileOK : LoadFileFailed,
						.bytes_read = bytes_read,
						.vol_id = requested_view_patch_loc_.vol,
						.filename = requested_view_patch_loc_.filename,
						.timestamp = timestamp,
					};
				} break;

				case RequestRefreshPatchList: {
					// TODO: Check if anything changed in hostfs

					reply.message_type = PatchListUnchanged;

					auto *patch_dir_list_ = msg.patch_dir_list;

					if (patch_dir_list_) {
						if (refresh_required) {
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
					uint32_t timestamp = 0;

					if (msg.vol_id == Volume::SDCard) {
						ok = storage.sd_hostfs.update_or_create_file(msg.filename, msg.buffer);
						timestamp = storage.sd_hostfs.get_file_timestamp(msg.filename);
					} else if (msg.vol_id == Volume::NorFlash) {
						ok = storage.flash_hostfs.update_or_create_file(msg.filename, msg.buffer);
						timestamp = storage.flash_hostfs.get_file_timestamp(msg.filename);
					}

					if (!ok || timestamp == 0) {
						pr_err("Error writing file!\n");
						reply = {WriteFileFail};
						return false;
					}

					reply = {.message_type = WriteFileOK,
							 .length = (uint32_t)msg.buffer.size_bytes(),
							 .timestamp = timestamp};
					refresh_required = true;
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

				case RequestFactoryReset: {
					pr_info("Factory reset = no action\n");
				} break;

				case RequestReloadDefaultPatches: {
					pr_info("Reset to factory patches = no action. (simulator default patches are read-only)\n");
				} break;

				case RequestFileInfo: {
					reply = {FileInfoFailed};

					if (msg.vol_id == Volume::SDCard) {
						reply.length = storage.sd_hostfs.get_file_size(msg.filename);
						reply.timestamp = storage.sd_hostfs.get_file_timestamp(msg.filename);
						reply.message_type = FileInfoSuccess;
					}

					if (msg.vol_id == Volume::NorFlash) {
						reply.length = storage.flash_hostfs.get_file_size(msg.filename);
						reply.timestamp = storage.flash_hostfs.get_file_timestamp(msg.filename);
						reply.message_type = FileInfoSuccess;
					}

				} break;

				case RequestDirEntries: {
					reply = {DirEntriesFailed};

					auto path = msg.filename;
					auto exts = msg.dest_filename;
					auto *dir_tree = msg.dir_entries;
					dir_tree->files.clear();
					dir_tree->dirs.clear();

					if (msg.vol_id == Volume::MaxVolumes) {
						if (storage.sd_hostfs.is_mounted()) {
							dir_tree->dirs.push_back("SD Card:");
						}
						reply.message_type = DirEntriesSuccess;

					} else if (msg.vol_id == Volume::SDCard) {
						if (storage.sd_hostfs.is_mounted()) {
							get_dir_entries(storage.sd_hostfs, path, exts, dir_tree);
							reply.message_type = DirEntriesSuccess;
						}
					}

				} break;

				default:
					break;
			}

			return true;

		} catch (const std::filesystem::filesystem_error &e) {
			std::cout << "Error: " << e.what() << std::endl;
			return true;
		}
	}

	IntercoreStorageMessage get_new_message() {
		auto r = reply;
		reply = {.message_type = IntercoreStorageMessage::None};
		return r;
	}

private:
	uint32_t load_patch_file(PatchLocation const &loc, uint32_t *timestamp) {

		bool ok = false;

		if (loc.vol == Volume::SDCard) {
			std::cout << "Trying to load " << loc.filename.c_str() << " from SD Card\n";
			ok = PatchFileIO::read_file(raw_patch_data_, storage.sd_hostfs, loc.filename, timestamp);
		}

		else if (loc.vol == Volume::NorFlash)
		{
			std::cout << "Trying to load " << loc.filename.c_str() << " from NorFlash\n";
			ok = PatchFileIO::read_file(raw_patch_data_, storage.flash_hostfs, loc.filename, timestamp);
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
