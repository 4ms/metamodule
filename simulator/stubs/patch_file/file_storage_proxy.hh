#pragma once
#include "../src/core_intercom/intercore_message.hh"
#include "fs/volumes.hh"
#include "patch/patch_data.hh"
#include "patch_file/patch_file.hh"
#include "patch_file/patch_fileio.hh"
#include "patch_file/patch_location.hh"
#include "patch_file/patchlist.hh"
#include "shared/patch_convert/yaml_to_patch.hh"
#include "stubs/patch_file/default_patch_io.hh"
#include "stubs/patch_file/host_file_io.hh"
#include <cstdint>

namespace MetaModule
{

// This is a mock for firmware's PatchStorage and FileStorageProxy classes
// It reads from a directory on the host filesystem and also treats the
// Default patches as a file system
class FileStorageProxy {

public:
	using enum IntercoreStorageMessage::MessageType;

	FileStorageProxy(std::string_view path)
		: hostfs_{MetaModule::Volume::SDCard, path}
		, defaultpatchfs_{MetaModule::Volume::NorFlash} {
		PatchFileIO::add_all_to_patchlist(defaultpatchfs_, patch_list_);
		PatchFileIO::add_all_to_patchlist(hostfs_, patch_list_);
	}

	[[nodiscard]] bool request_viewpatch(PatchLocation patch_loc) {
		requested_view_patch_id_ = patch_loc.index;
		requested_view_patch_vol_ = patch_loc.vol;
		msg_state_ = MsgState::ViewPatchRequested;
		return true;
	}

	bool parse_view_patch(uint32_t bytes_read) {
		std::span<char> file_data = raw_patch.subspan(0, bytes_read);

		// Load into a temporary patch file, so if it fails, view_patch_ is not effected
		// And if ryml fails to deserialize, we aren't left with data from the last patch
		PatchData patch;
		if (!yaml_raw_to_patch(file_data, patch))
			return false;

		view_patch_ = patch;

		view_patch_id_ = requested_view_patch_id_;
		return true;
	}

	PatchData &get_view_patch() {
		return view_patch_;
	}

	uint32_t get_view_patch_id() {
		return view_patch_id_;
	}

	Volume get_view_patch_vol() {
		return view_patch_vol_;
	}

	IntercoreStorageMessage get_message() {

		if (msg_state_ == MsgState::ViewPatchRequested) {
			msg_state_ = MsgState::Idle;

			auto bytes_read = load_patch_file(requested_view_patch_vol_, requested_view_patch_id_);
			if (bytes_read)
				return {PatchDataLoaded, bytes_read, requested_view_patch_id_, {}, requested_view_patch_vol_};
			else
				return {PatchDataLoadFail, 0, requested_view_patch_id_, {}, requested_view_patch_vol_};
		}

		if (msg_state_ == MsgState::PatchListRequested) {
			msg_state_ = MsgState::Idle;

			if (populate_patchlist(remote_patch_list_.norflash, Volume::NorFlash) == PatchListChanged)
				return {PatchListChanged};

			else if (populate_patchlist(remote_patch_list_.sdcard, Volume::SDCard) == PatchListChanged)
				return {PatchListChanged};

			else if (populate_patchlist(remote_patch_list_.usb, Volume::USB) == PatchListChanged)
				return {PatchListChanged};

			return {PatchListUnchanged};
		}

		if (msg_state_ == MsgState::FirmwareUpdateFileRequested) {
			msg_state_ = MsgState::Idle;
			mock_file_found_ctr++;

			if ((mock_file_found_ctr % 8) < 4)
				return {FirmwareFileFound,
						mock_file_found_ctr + mock_firmware_file_size,
						0,
						"metamodule-fw-1.23.45.uimg",
						Volume::USB};
			else
				return {FirmwareFileNotFound};
		}

		if (msg_state_ == MsgState::FirmwareFileLoadRequested) {
			if (mock_file_found_ctr++ > 50) {
				msg_state_ = MsgState::Idle;
				return {LoadFirmwareToRamSuccess};
			}
		}

		return {};
	}

	[[nodiscard]] bool request_patchlist() {
		msg_state_ = MsgState::PatchListRequested;
		return true;
	}

	PatchFileList &get_patch_list() {
		return remote_patch_list_;
	}

	uint32_t load_patch_file(Volume vol, uint32_t patch_id) {
		auto filename = patch_list_.get_patch_filename(vol, patch_id);

		raw_patch = raw_patch_buffer_;

		bool ok = false;

		if (vol == Volume::SDCard)
			ok = PatchFileIO::read_file(raw_patch, hostfs_, filename);

		if (vol == Volume::NorFlash)
			ok = PatchFileIO::read_file(raw_patch, defaultpatchfs_, filename);

		//TODO: add USB when we have a usb fileio
		// if (vol == Volume::USB)
		// ok = PatchFileIO::read_file(raw_patch, usbpatchfs_, filename);

		if (!ok) {
			std::cout << "Could not load patch " << patch_id << " on vol " << (int)vol << "\n";
			return 0;
		}

		view_patch_vol_ = vol;
		std::cout << "Read patch id " << patch_id << " " << raw_patch.size_bytes() << " bytes\n";
		return raw_patch.size_bytes();
	}

	[[nodiscard]] bool request_find_firmware_file() {
		msg_state_ = MsgState::FirmwareUpdateFileRequested;
		return true;
	}

	[[nodiscard]] bool request_load_file(std::string_view filename, Volume vol, std::span<char> buffer) {
		msg_state_ = MsgState::FirmwareFileLoadRequested;
		return true;
	}

private:
	PatchFileList remote_patch_list_;
	PatchList patch_list_;

	HostFileIO hostfs_;
	DefaultPatchFileIO defaultpatchfs_;

	std::array<char, 65536> raw_patch_buffer_;
	std::span<char> raw_patch;

	PatchData view_patch_;
	uint32_t requested_view_patch_id_ = 0;
	Volume requested_view_patch_vol_;
	uint32_t view_patch_id_ = 0;
	Volume view_patch_vol_ = Volume::NorFlash;

	enum class MsgState {
		Idle,
		ViewPatchRequested,
		PatchListRequested,
		FirmwareUpdateFileRequested,
		FirmwareFileLoadRequested,
	} msg_state_ = MsgState::Idle;

	unsigned mock_file_found_ctr = 0;
	unsigned mock_firmware_file_size = 5'123'456;

	IntercoreStorageMessage::MessageType populate_patchlist(std::span<const PatchFile> &list, Volume vol) {
		if (list.size() == 0) {
			list = patch_list_.get_patchfile_list(vol);
			if (list.size() > 0)
				return PatchListChanged;
		}
		return PatchListUnchanged;
	}
};
} // namespace MetaModule
