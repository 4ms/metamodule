#pragma once
#include "core_intercom/intercore_message.hh"
#include "patch/patch_data.hh"
#include "patch_convert/patch_to_yaml.hh"
#include "patch_convert/yaml_to_patch.hh"
#include "patch_file.hh"
#include "patch_file/file_storage_comm.hh"
#include "patch_file/open_patches.hh"
#include "patch_file/patch_location.hh"
#include "pr_dbg.hh"

namespace MetaModule
{

// TODO: separate this into the Proxy (wrappers for calls to comm_.send_message)
// and the open patch managment (view_patch, playing_patch)
class FileStorageProxy {

public:
	using enum IntercoreStorageMessage::MessageType;

	FileStorageProxy(std::span<char> raw_patch_data, FileStorageComm &comm, PatchDirList &patch_dir_list)
		: patch_dir_list_{patch_dir_list}
		, comm_{comm}
		, raw_patch_data_{raw_patch_data} {
	}

	IntercoreStorageMessage get_message() {
		return comm_.get_new_message();
	}

	[[nodiscard]] bool request_load_patch(PatchLocation patch_loc) {
		IntercoreStorageMessage message{
			.message_type = RequestPatchData,
			.vol_id = patch_loc.vol,
			.buffer = raw_patch_data_,
			.filename = patch_loc.filename,
		};
		if (!comm_.send_message(message))
			return false;

		requested_view_patch_loc_ = patch_loc;
		return true;
	}

	bool load_if_open(PatchLocation patch_loc) {
		if (playing_patch_ && (PatchLocHash{patch_loc} == playing_patch_->loc_hash)) {
			view_playing_patch();
			return true;

		} else if (auto openpatch = open_patches_.find(PatchLocHash{patch_loc})) {
			view_patch_ = openpatch;
			return true;

		} else {
			return false;
		}
	}

	// Parses and opens the loaded patch, and sets the view patch to point to it
	bool parse_loaded_patch(uint32_t bytes_read) {
		std::span<char> file_data = raw_patch_data_.subspan(0, bytes_read);

		auto *new_patch = open_patches_.emplace_back(requested_view_patch_loc_);

		pr_trace("\n\n%.*s\n\n", file_data.size(), file_data.data());
		if (!yaml_raw_to_patch(file_data, new_patch->patch)) {
			pr_err("Failed to parse\n");
			open_patches_.remove_last();
			return false;
		}

		//Handle patches saved by legacy firmware with empty knob sets
		new_patch->patch.trim_empty_knobsets();

		view_patch_ = new_patch;

		return true;
	}

	//
	// playing_patch: (copy of) patch currently playing in the audio thread
	//
	PatchData *get_playing_patch() {
		if (playing_patch_)
			return &playing_patch_->patch;
		else {
			return nullptr;
		}
	}

	//
	// viewpatch: (pointer to) patch we are currently viewing in the GUI
	//
	PatchData *get_view_patch() {
		if (view_patch_)
			return &view_patch_->patch;
		else {
			pr_err("Tried to get_view_patch when viewpatch is null.\n");
			return nullptr;
		}
	}

	//
	// Tells FileStorageProxy that the view_patch is now being played
	//
	void play_view_patch() {
		playing_patch_ = view_patch_;
	}

	void view_playing_patch() {
		view_patch_ = playing_patch_;
	}

	std::string_view get_view_patch_filename() {
		if (view_patch_)
			return view_patch_->loc.filename;
		else {
			return "";
		}
	}

	Volume get_view_patch_vol() {
		if (view_patch_)
			return view_patch_->loc.vol;
		else {
			pr_err("Tried to get_view_patch_vol() for null view_patch\n");
			return Volume::MaxVolumes;
		}
	}

	PatchLocHash get_playing_patch_loc_hash() {
		if (playing_patch_)
			return playing_patch_->loc_hash;
		else {
			return PatchLocHash{};
		}
	}

	PatchLocHash get_view_patch_loc_hash() {
		if (view_patch_)
			return view_patch_->loc_hash;
		else {
			return PatchLocHash{};
		}
	}

	void set_patch_filename(std::string_view filename) {
		if (view_patch_)
			view_patch_->loc.filename.copy(filename);
		else
			pr_err("Tried to set_patch_filename() for null view_patch\n");
	}

	void mark_view_patch_modified() {
		view_patch_->modification_count++;
	}

	unsigned get_view_patch_modification_count() {
		return view_patch_->modification_count;
	}

	//
	// patchlist: list of all patches found on all volumes
	//
	[[nodiscard]] bool request_patchlist(std::optional<Volume> force_refresh_vol = std::nullopt) {
		IntercoreStorageMessage message{.message_type = RequestRefreshPatchList, .patch_dir_list = &patch_dir_list_};
		if (force_refresh_vol.has_value()) {
			message.force_refresh = true;
			message.vol_id = force_refresh_vol.value();
		}
		return comm_.send_message(message);
	}

	PatchDirList &get_patch_list() {
		//FIXME: Ensure this is only called when
		//we have access to the shared data. Return a ptr,
		//or return nullptr if we've sent a RequestRefreshPatchList but
		//haven't gotten a reply yet
		return patch_dir_list_;
	}

	// Scan all mounted volumes for firmware update files
	[[nodiscard]] bool request_find_firmware_file() {
		IntercoreStorageMessage message{.message_type = RequestFirmwareFile};
		return comm_.send_message(message);
	}

	// Load a file from filesystem to RAM
	[[nodiscard]] bool request_load_file(std::string_view filename, Volume vol, std::span<char> buffer) {
		IntercoreStorageMessage message{
			.message_type = RequestLoadFileToRam,
			.vol_id = vol,
			.buffer = buffer,
			.filename = filename,
		};
		return comm_.send_message(message);
	}

	[[nodiscard]] bool request_checksum_compare(IntercoreStorageMessage::FlashTarget target,
												StaticString<32> checksum,
												uint32_t address,
												uint32_t length,
												uint32_t *bytes_processed) {
		IntercoreStorageMessage message{
			.message_type = StartChecksumCompare,
			.address = address,
			.length = length,
			.checksum = checksum,
			.bytes_processed = bytes_processed,
			.flashTarget = target,
		};
		return comm_.send_message(message);
	}

	[[nodiscard]] bool request_file_flash(IntercoreStorageMessage::FlashTarget target,
										  std::span<uint8_t> buffer,
										  uint32_t address,
										  uint32_t *bytes_processed) {
		IntercoreStorageMessage message{
			.message_type = StartFlashing,
			.buffer = {(char *)buffer.data(), buffer.size()},
			.address = address,
			.bytes_processed = bytes_processed,
			.flashTarget = target,
		};
		return comm_.send_message(message);
	}

	[[nodiscard]] bool request_delete_file(std::string_view filename, Volume vol) {
		IntercoreStorageMessage message{
			.message_type = RequestDeleteFile,
			.vol_id = vol,
			.filename = filename,
		};
		return comm_.send_message(message);
	}

	void new_patch() {
		std::string name = "Untitled Patch " + std::to_string((uint8_t)std::rand());
		std::string filename = name + ".yml";
		PatchLocation loc{std::string_view{filename}, Volume::RamDisk};
		view_patch_ = open_patches_.emplace_back(loc);
		view_patch_->patch.blank_patch(name);
	}

	void rename_view_patch_file(std::string_view filepath, Volume vol) {
		if (view_patch_) {
			view_patch_->loc.filename.copy(filepath);
			view_patch_->loc.vol = vol;
			view_patch_->loc_hash = PatchLocHash{view_patch_->loc};
		} else {
			pr_err("Attempted to rename patch that's not open\n");
		}
	}

	bool duplicate_view_patch(std::string_view filepath, Volume vol) {
		// Check if filename is already open
		if (open_patches_.find(PatchLocHash{filepath, vol})) {
			pr_err("Can't rename to same name as an already open patch: %.*s\n", filepath.size(), filepath.data());
			return false;
		}

		// Create a new patch
		OpenPatch *new_patch = open_patches_.emplace_back({filepath, vol});

		// Copy the currently viewed patch into it
		new_patch->patch = view_patch_->patch;

		// View the new patch
		view_patch_ = new_patch;

		return true;
	}

	enum class WriteResult { Busy, Success, InvalidVol, InvalidName };

	void close_view_patch() {
		if (open_patches_.remove(view_patch_->loc_hash)) {
			if (playing_patch_ == view_patch_) {
				playing_patch_ = nullptr;
			}
			view_patch_ = nullptr;
		} else {
			pr_err("Tried to delete view patch, but it's not found\n");
		}
	}

	void update_view_patch_module_states(std::vector<ModuleInitState> const &states) {
		if (view_patch_)
			view_patch_->patch.module_states = states; //copy
		else
			pr_err("Error: tried to update_view_patch_module_states on a null view_patch\n");
	}

	WriteResult write_patch(std::string_view filename = "") {
		if (view_patch_) {
			Volume vol = view_patch_->loc.vol;
			if (vol == Volume::RamDisk || vol == Volume::MaxVolumes) {
				pr_err("Error: no valid volume for writing a patch\n");
				return WriteResult::InvalidVol;
			}

			if (filename == "")
				filename = view_patch_->loc.filename;

			std::span<char> file_data = raw_patch_data_;

			patch_to_yaml_buffer(view_patch_->patch, file_data);

			IntercoreStorageMessage message{
				.message_type = RequestWritePatchData,
				.vol_id = vol,
				.buffer = file_data,
				.filename = filename,
			};

			return comm_.send_message(message) ? WriteResult::Success : WriteResult::Busy;

		} else {
			pr_err("Error: cannot write a null patch\n");
			return WriteResult::InvalidName;
		}
	}

	bool request_reset_factory_patches() {
		IntercoreStorageMessage message{
			.message_type = RequestFactoryResetPatches,
		};
		return comm_.send_message(message);
	}

	bool request_plugin_file_list(PluginFileList *plugin_file_list) {
		IntercoreStorageMessage message{
			.message_type = RequestPluginFileList,
			.plugin_file_list = plugin_file_list,
		};
		return comm_.send_message(message);
	}

	bool request_copy_dir_to_ramdisk(Volume vol, std::string_view path) {
		IntercoreStorageMessage message{.message_type = RequestCopyPluginAssets, .vol_id = vol, .filename = path};
		return comm_.send_message(message);
	}

private:
	PatchDirList &patch_dir_list_;

	FileStorageComm &comm_;

	std::span<char> raw_patch_data_;

	PatchData unsaved_patch_;

	OpenPatch *view_patch_ = nullptr;
	OpenPatch *playing_patch_ = nullptr;
	OpenPatchList open_patches_;

	// no need for open_patches.rename_file()

	PatchLocation requested_view_patch_loc_;

	PatchData empty_patch{};
};
} // namespace MetaModule
