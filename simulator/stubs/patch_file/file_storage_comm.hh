#pragma once
#include "../src/core_intercom/intercore_message.hh"
#include "fs/fileio_t.hh"
#include "fs/volumes.hh"
#include "fw_update/update_path.hh"
#include "patch_file/default_patch_io.hh"
#include "patch_file/host_file_io.hh"
#include "patch_file/patch_dir_list.hh"
#include "patch_file/patch_fileio.hh"
#include "patch_file/patch_location.hh"
#include <cstdint>

namespace MetaModule
{

struct SimulatorPatchStorage {
	SimulatorPatchStorage(std::string_view path, PatchDirList &patch_dir_list_)
		: hostfs_{MetaModule::Volume::SDCard, path}
		, defaultpatchfs_{MetaModule::Volume::NorFlash} {
		PatchFileIO::add_directory(hostfs_, patch_dir_list_.volume_root(Volume::SDCard));
		PatchFileIO::add_directory(defaultpatchfs_, patch_dir_list_.volume_root(Volume::NorFlash));
	}

	HostFileIO hostfs_;
	DefaultPatchFileIO defaultpatchfs_;
};

struct SimulatorFileStorageComm {
	using enum IntercoreStorageMessage::MessageType;
	using MessageT = IntercoreStorageMessage;

	SimulatorFileStorageComm(SimulatorPatchStorage &patch_storage)
		: storage{patch_storage} {
	}

	[[nodiscard]] bool send_message(const MessageT &msg) {
		switch (msg.message_type) {
			case RequestPatchData: {
				requested_view_patch_loc_ = PatchLocation{msg.filename, msg.vol_id};
				raw_patch_data_ = msg.buffer;
				auto bytes_read = load_patch_file(requested_view_patch_loc_);
				reply = {.message_type = bytes_read ? PatchDataLoaded : PatchDataLoadFail,
						 .bytes_read = bytes_read,
						 .vol_id = requested_view_patch_loc_.vol,
						 .filename = requested_view_patch_loc_.filename};
			} break;

			case RequestRefreshPatchList: {
				// TODO: Refresh from all fs, see if anything changed
				if (refresh_required) {
					refresh_required = false;
					reply = {PatchListChanged};
				} else {
					reply = {PatchListUnchanged};
				}
			} break;

			case RequestFirmwareFile: {
				if (find_manifest(storage.hostfs_)) {
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

			case RequestLoadFileToRam: {
				if (storage.hostfs_.read_file(msg.filename, msg.buffer))
					reply = {LoadFileToRamSuccess};
				else
					reply = {LoadFileToRamFailed};
			} break;

			case RequestWritePatchData: {
				if (!storage.hostfs_.update_or_create_file(msg.filename, msg.buffer)) {
					pr_err("Error writing file!\n");
					reply = {PatchDataWriteFail};
					return false;
				}
				reply = {PatchDataWriteOK};
				refresh_required = true;
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

		if (loc.vol == Volume::SDCard)
			ok = PatchFileIO::read_file(raw_patch_data_, storage.hostfs_, loc.filename);

		if (loc.vol == Volume::NorFlash)
			ok = PatchFileIO::read_file(raw_patch_data_, storage.defaultpatchfs_, loc.filename);

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
