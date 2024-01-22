#pragma once
#include "../src/core_intercom/intercore_message.hh"
#include "fs/volumes.hh"
#include "patch/patch_data.hh"
#include "patch_file/patch_dir_list.hh"
#include "patch_file/patch_fileio.hh"
#include "patch_file/patch_location.hh"
#include "shared/patch_convert/patch_to_yaml.hh"
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
		PatchFileIO::add_directory(hostfs_, patch_dir_list_.volume_root(Volume::SDCard));
		PatchFileIO::add_directory(defaultpatchfs_, patch_dir_list_.volume_root(Volume::NorFlash));
	}

	[[nodiscard]] bool request_viewpatch(PatchLocation patch_loc) {
		requested_view_patch_loc_.filename = patch_loc.filename;
		requested_view_patch_loc_.vol = patch_loc.vol;
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

		view_patch_loc_ = requested_view_patch_loc_;
		return true;
	}

	void new_patch() {
		std::string name = "Untitled Patch " + std::to_string((uint8_t)std::rand());
		view_patch_.blank_patch(name);

		name += ".yml";
		view_patch_loc_.filename.copy(name);
		view_patch_loc_.vol = Volume::RamDisk;
	}

	PatchData &get_view_patch() {
		return view_patch_;
	}

	StaticString<255> get_view_patch_filename() {
		return view_patch_loc_.filename;
	}

	Volume get_view_patch_vol() {
		return view_patch_loc_.vol;
	}

	IntercoreStorageMessage get_message() {

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

	[[nodiscard]] bool request_patchlist() {
		msg_state_ = MsgState::PatchListRequested;
		return true;
	}

	PatchDirList &get_patch_list() {
		return patch_dir_list_;
	}

	uint32_t load_patch_file(PatchLocation const &loc) {

		raw_patch = raw_patch_buffer_;

		bool ok = false;

		if (loc.vol == Volume::SDCard)
			ok = PatchFileIO::read_file(raw_patch, hostfs_, loc.filename);

		if (loc.vol == Volume::NorFlash)
			ok = PatchFileIO::read_file(raw_patch, defaultpatchfs_, loc.filename);

		//TODO: add USB when we have a usb fileio
		// if (vol == Volume::USB)
		// ok = PatchFileIO::read_file(raw_patch, usbpatchfs_, filename);

		if (!ok) {
			std::cout << "Could not load patch " << loc.filename << " on vol " << (int)loc.vol << "\n";
			return 0;
		}

		view_patch_loc_ = loc;
		std::cout << "Read patch id " << loc.filename << " " << raw_patch.size_bytes() << " bytes\n";
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

	bool write_patch(std::string_view filename = "") {
		if (filename == "")
			filename = view_patch_loc_.filename;

		std::span<char> file_data = raw_patch_buffer_;

		patch_to_yaml_buffer(view_patch_, file_data);

		msg_state_ = MsgState::WritePatchFileRequested;

		bool ok = hostfs_.update_or_create_file(filename, file_data);

		if (!ok) {
			pr_err("Error writing file!\n");
			return false;
		}

		// printf("size: %zu, %zu\n", file_data.size(), sz);
		// printf("%.*s\n", (int)sz, file_data.data());

		refresh_required = true;
		return true;
	}

private:
	PatchDirList patch_dir_list_;

	HostFileIO hostfs_;
	DefaultPatchFileIO defaultpatchfs_;

	std::array<char, 65536> raw_patch_buffer_;
	std::span<char> raw_patch;

	PatchData view_patch_;

	PatchLocation requested_view_patch_loc_;
	PatchLocation view_patch_loc_;

	enum class MsgState {
		Idle,
		ViewPatchRequested,
		PatchListRequested,
		FirmwareUpdateFileRequested,
		FirmwareFileLoadRequested,
		WritePatchFileRequested,
	} msg_state_ = MsgState::Idle;

	unsigned mock_file_found_ctr = 0;
	unsigned mock_firmware_file_size = 513;

	bool refresh_required = true;

	// IntercoreStorageMessage::MessageType populate_patchlist(std::span<const PatchFile> &list, Volume vol) {
	// 	if (list.size() == 0) {
	// 		list = patch_list_.get_patchfile_list(vol);
	// 		if (list.size() > 0)
	// 			return PatchListChanged;
	// 	}
	// 	return PatchListUnchanged;
	// }
};
} // namespace MetaModule
