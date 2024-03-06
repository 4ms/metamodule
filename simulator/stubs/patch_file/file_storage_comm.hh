#pragma once
#include "../src/core_intercom/intercore_message.hh"
#include "fs/volumes.hh"
#include "patch_file/patch_dir_list.hh"
#include "patch_file/patch_fileio.hh"
#include "patch_file/patch_location.hh"
#include "stubs/patch_file/default_patch_io.hh"
#include "stubs/patch_file/host_file_io.hh"
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
			case RequestPatchData:
				requested_view_patch_loc_ = PatchLocation{msg.filename, msg.vol_id};
				raw_patch_data_ = msg.buffer;
				msg_state_ = MsgState::ViewPatchRequested;
				break;

			case RequestRefreshPatchList:
				msg_state_ = MsgState::PatchListRequested;
				break;

			case RequestFirmwareFile:
				msg_state_ = MsgState::FirmwareUpdateFileRequested;
				break;

			case RequestLoadFileToRam:
				msg_state_ = MsgState::FirmwareFileLoadRequested;
				break;

			case RequestWritePatchData: {
				msg_state_ = MsgState::WritePatchFileRequested;
				if (!storage.hostfs_.update_or_create_file(msg.filename, msg.buffer)) {
					pr_err("Error writing file!\n");
					return false;
				}
				refresh_required = true;
			} break;

			case RequestFactoryResetPatches:
				pr_info("Reset to factory patches = no action. (simulator default patches are read-only)\n");
				break;

			default:
				break;
		}

		return true;
	}

	IntercoreStorageMessage get_new_message() {
		if (msg_state_ == MsgState::ViewPatchRequested) {
			msg_state_ = MsgState::Idle;

			auto bytes_read = load_patch_file(requested_view_patch_loc_);
			if (bytes_read)
				return {.message_type = PatchDataLoaded,
						.bytes_read = bytes_read,
						.vol_id = requested_view_patch_loc_.vol,
						.filename = requested_view_patch_loc_.filename};
			else
				return {.message_type = PatchDataLoadFail,
						.bytes_read = 0,
						.vol_id = requested_view_patch_loc_.vol,
						.filename = requested_view_patch_loc_.filename};
		}

		if (msg_state_ == MsgState::PatchListRequested) {
			msg_state_ = MsgState::Idle;

			// TODO: Refresh from all fs, see if anything changed
			if (refresh_required) {
				refresh_required = false;
				return {PatchListChanged};
			} else {
				return {PatchListUnchanged};
			}
		}

		if (msg_state_ == MsgState::FirmwareUpdateFileRequested) {
			msg_state_ = MsgState::Idle;
			mock_file_found_ctr++;

			if ((mock_file_found_ctr % 8) < 4)
				return {
					.message_type = FirmwareFileFound,
					.bytes_read = mock_file_found_ctr + mock_firmware_file_size,
					.vol_id = Volume::SDCard,
					.filename = "metamodule-fw.json",
				};
			else
				return {FirmwareFileNotFound};
		}

		if (msg_state_ == MsgState::FirmwareFileLoadRequested) {
			if (mock_file_found_ctr++ > 50) {
				msg_state_ = MsgState::Idle;
				return {LoadFileToRamSuccess};
			}
		}

		return {};
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

	SimulatorPatchStorage &storage;
	PatchLocation requested_view_patch_loc_;

	unsigned mock_file_found_ctr = 0;
	unsigned mock_firmware_file_size = 513;

	bool refresh_required = true;

	std::span<char> raw_patch_data_;

	enum class MsgState {
		Idle,
		ViewPatchRequested,
		PatchListRequested,
		FirmwareUpdateFileRequested,
		FirmwareFileLoadRequested,
		WritePatchFileRequested,
	} msg_state_ = MsgState::Idle;
};

using FileStorageComm = SimulatorFileStorageComm;

} // namespace MetaModule
