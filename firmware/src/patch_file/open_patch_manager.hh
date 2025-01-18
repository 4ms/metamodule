#pragma once
#include "core_intercom/intercore_message.hh"
#include "patch-serial/yaml_to_patch.hh"
#include "patch/patch_data.hh"
#include "patch_file/open_patches.hh"
#include "patch_file/patch_location.hh"
#include "pr_dbg.hh"

namespace MetaModule
{

class OpenPatchManager {

public:
	using enum IntercoreStorageMessage::MessageType;

	// Parses and opens the loaded patch, and sets the view patch to point to it
	// Removes existing patch with same name/vol if one exists
	bool open_patch(std::span<char> file_data, PatchLocation const &patch_loc, uint32_t timestamp) {
		bool patch_is_playing = false;

		OpenPatch *patch{};

		// open_patches_.dump_open_patches();

		if (auto existing_patch = open_patches_.find(patch_loc)) {
			if (existing_patch == playing_patch_)
				patch_is_playing = true;

			pr_dbg("Open patch found already, will replace the patch data: is_playing=%d\n", patch_is_playing);
			patch = existing_patch;

		} else {
			pr_dbg("Adding new patch '%s' on vol:%d\n", patch_loc.filename.data(), patch_loc.vol);
			patch = open_patches_.emplace_back(patch_loc);
		}

		patch->timestamp = timestamp;
		patch->filesize = file_data.size();
		patch->modification_count = 0;

		if (!yaml_raw_to_patch(file_data, patch->patch)) {
			pr_err("Failed to parse\n");
			open_patches_.remove_last();

			if (patch_is_playing)
				playing_patch_ = nullptr;

			return false;
		}

		// Handle patches saved by legacy firmware with empty knob sets
		patch->patch.trim_empty_knobsets();
		// Handle legacy use of midi poly num
		patch->patch.update_midi_poly_num();

		return true;
	}

	// Makes room for a opening a patch.
	// Closes unmodified patches if needed.
	// Returns false if can't make room.
	bool have_space_to_open_patch(unsigned max_patches) {
		auto first = open_patches_.begin();

		int num_to_remove = (open_patches_.size() >= max_patches) ? open_patches_.size() - max_patches : 0;

		while (num_to_remove > 0) {

			first = std::find_if(first, open_patches_.end(), [this](auto &entry) {
				return &entry != view_patch_ && &entry != playing_patch_ && entry.modification_count == 0;
			});

			if (first == open_patches_.end()) {
				return false;
			} else {
				open_patches_.remove(first);
				num_to_remove--;
			}
		}

		return true;
	}

	OpenPatch *find_open_patch(PatchLocation const &patch_loc) {
		return open_patches_.find(patch_loc);
	}

	void start_viewing(OpenPatch *patch) {
		if (patch)
			view_patch_ = patch;
	}

	void start_viewing(PatchLocation const &patch_loc) {
		if (auto new_patch = find_open_patch(patch_loc)) {
			view_patch_ = new_patch;
		}
	}

	//
	// playing_patch: (copy of) patch currently playing in the audio thread
	//
	PatchData *get_playing_patch() {
		if (playing_patch_) {
			if (open_patches_.exists(playing_patch_)) {
				return &playing_patch_->patch;
			} else {
				pr_err("Playing patch not null and not found in open patches!\n");
				return nullptr;
			}
		} else {
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

	PatchLocation get_view_patch_loc() {
		if (view_patch_)
			return view_patch_->loc;
		else {
			return {"", Volume::MaxVolumes};
		}
	}

	PatchLocation get_playing_patch_loc() {
		if (playing_patch_)
			return playing_patch_->loc;
		else {
			return {"", Volume::MaxVolumes};
		}
	}

	std::string_view get_view_patch_filename() {
		return get_view_patch_loc().filename;
	}

	Volume get_view_patch_vol() {
		return get_view_patch_loc().vol;
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

	void reset_view_patch_modification_count() {
		view_patch_->modification_count = 0;
	}

	unsigned get_view_patch_modification_count() {
		return view_patch_ ? view_patch_->modification_count : 0;
	}

	unsigned get_playing_patch_modification_count() {
		return playing_patch_ ? playing_patch_->modification_count : 0;
	}

	uint32_t get_modification_count(PatchLocation const &patch_loc) {
		if (auto patch = find_open_patch(patch_loc))
			return patch->modification_count;
		else
			return 0;
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
		if (view_patch_->loc_hash == PatchLocHash{filepath, vol}) {
			pr_warn("Can't duplicate a patch onto itself\n");
			return false;
		}

		if (auto openpatch = open_patches_.find(PatchLocHash{filepath, vol})) {
			if (openpatch->modification_count > 0) {
				pr_err("Can't overwrite an open and modified patch: %.*s\n", filepath.size(), filepath.data());
				return false;
			} else {
				close_open_patch(openpatch);
			}
		}

		// Create a new patch
		OpenPatch *new_patch = open_patches_.emplace_back({filepath, vol});

		// Copy the currently viewed patch into it
		new_patch->patch = view_patch_->patch;
		new_patch->timestamp = view_patch_->timestamp; //TODO: update timestamp?
		new_patch->filesize = view_patch_->filesize;

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

	void close_open_patch(OpenPatch *patch) {
		if (patch == playing_patch_)
			close_playing_patch();
		else if (patch == view_patch_)
			close_view_patch();
		else {
			if (!open_patches_.remove(patch->loc_hash)) {
				pr_err("Tried to close patch, but it's not found\n");
			}
		}
	}

	void close_playing_patch() {
		if (open_patches_.remove(playing_patch_->loc_hash)) {
			if (playing_patch_ == view_patch_) {
				view_patch_ = nullptr;
			}
			playing_patch_ = nullptr;
		} else {
			pr_err("Tried to delete playing patch, but it's not found\n");
		}
	}

	OpenPatchList const &get_open_patch_list() {
		return open_patches_;
	}

private:
	OpenPatch *view_patch_ = nullptr;
	OpenPatch *playing_patch_ = nullptr;
	OpenPatchList open_patches_;
};
} // namespace MetaModule
