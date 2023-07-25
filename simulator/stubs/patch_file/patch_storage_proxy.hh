#pragma once
#include "fs/volumes.hh"
#include "patch/patch_data.hh"
#include "patch_file/patch_file.hh"
#include "patch_file/patch_fileio.hh"
#include "patch_file/patches_default.hh"
#include "patch_file/patchlist.hh"
#include "shared/patch_convert/yaml_to_patch.hh"
#include "stubs/patch_file/host_file_io.hh"
#include <cstdint>
#include <filesystem>

namespace MetaModule
{

struct InterCoreCommMessage {
	enum MessageType : uint32_t {
		None,

		RequestRefreshPatchList,
		PatchListChanged,
		PatchListUnchanged,

		RequestPatchData,
		PatchDataLoadFail,
		PatchDataLoaded,

		NumRequests,
	};
	MessageType message_type;
	uint32_t bytes_read;
	uint32_t patch_id;
	uint32_t vol_id;
};

// This is a mock for firmware's PatchStorage and PatchStorageProxy classes
// It reads from a directory on the host filesystem
class PatchStorageProxy {

public:
	using enum InterCoreCommMessage::MessageType;

	PatchStorageProxy(std::string_view path)
		: hostfs{MetaModule::Volume::NorFlash, path} {
		PatchFileIO::add_all_to_patchlist(hostfs, patch_list_);
	}

	[[nodiscard]] bool request_viewpatch(Volume vol, uint32_t patch_id) {
		requested_view_patch_id_ = patch_id;
		requested_view_patch_vol_ = vol;
		msg_state_ = MsgState::ViewPatchRequested;
		return true;
	}

	bool parse_view_patch(uint32_t bytes_read) {
		std::span<char> file_data = raw_patch.subspan(0, bytes_read);
		if (!yaml_raw_to_patch(file_data, view_patch_))
			return false;

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

	InterCoreCommMessage get_message() {
		if (msg_state_ == MsgState::ViewPatchRequested) {
			msg_state_ = MsgState::Idle;

			if (requested_view_patch_id_ < remote_patch_list_.norflash.size()) {
				auto bytes_read = load_patch_file(requested_view_patch_vol_, requested_view_patch_id_);
				if (bytes_read)
					return {PatchDataLoaded, bytes_read, requested_view_patch_id_, (uint32_t)requested_view_patch_vol_};
			}

			// Something when wrong:
			return {PatchDataLoadFail, 0, requested_view_patch_id_, (uint32_t)requested_view_patch_vol_};
		}

		if (msg_state_ == MsgState::PatchListRequested) {
			msg_state_ = MsgState::Idle;

			// Populate "norflash" the first time it's requested
			if (remote_patch_list_.norflash.size() == 0) {
				remote_patch_list_.norflash = patch_list_.get_patchfile_list(MetaModule::Volume::NorFlash);
				return {PatchListChanged, 0, 0, 0};
			}
			return {PatchListUnchanged, 0, 0, 0};
		}

		return {};
	}

	[[nodiscard]] bool request_patchlist() {
		msg_state_ = MsgState::PatchListRequested;
		return true;
	}

	PatchFileList &get_patch_list() {
		printf("Patchlist got\n");
		return remote_patch_list_;
	}

	uint32_t load_patch_file(Volume vol, uint32_t patch_id) {
		auto filename = patch_list_.get_patch_filename(vol, patch_id);

		raw_patch = raw_patch_buffer_;

		bool ok = false;
		if (vol == Volume::NorFlash)
			ok = PatchFileIO::read_file(raw_patch, hostfs, filename);

		if (!ok) {
			printf("Could not load patch id %d\n", patch_id);
			return 0;
		}

		printf("Read patch id %d, %zu bytes\n", patch_id, raw_patch.size_bytes());
		return raw_patch.size_bytes();
	}

private:
	PatchFileList remote_patch_list_;
	HostFileIO hostfs;
	PatchList patch_list_;

	std::array<char, 65536> raw_patch_buffer_;
	std::span<char> raw_patch;

	PatchData view_patch_;
	uint32_t requested_view_patch_id_ = 0;
	Volume requested_view_patch_vol_;
	uint32_t view_patch_id_ = 0;
	Volume view_patch_vol_ = Volume::NorFlash;

	enum class MsgState { Idle, ViewPatchRequested, PatchListRequested } msg_state_ = MsgState::Idle;
};
} // namespace MetaModule
