#pragma once
#include "core_intercom/intercore_message.hh"
#include "patch-serial/patch_to_yaml.hh"
#include "patch-serial/yaml_to_patch.hh"
#include "patch/patch_data.hh"
#include "patch_file.hh"
#include "patch_file/file_storage_comm.hh"
#include "patch_file/open_patches.hh"
#include "patch_file/patch_location.hh"
#include "pr_dbg.hh"

namespace MetaModule
{

class OpenPatchManager {

public:
	using enum IntercoreStorageMessage::MessageType;

	// If the given patch loc is an open patch, set view_patch to it
	bool load_if_open(PatchLocation patch_loc) {
		if (playing_patch_ && (PatchLocHash{patch_loc} == playing_patch_->loc_hash)) {
			if (playing_patch_->force_reload == false) {
				view_playing_patch();
				return true;
			} else {
				pr_trace("Reload playing patch from disk\n");
				return false;
			}

		} else if (auto openpatch = open_patches_.find(PatchLocHash{patch_loc})) {
			if (openpatch->force_reload == false) {
				view_patch_ = openpatch;
				return true;
			} else {
				pr_trace("Reload patch from disk\n");
				return false;
			}

		} else {
			return false;
		}
	}

	// Makes room for a opening a patch.
	// Closes unmodified patches if needed.
	// Returns false if can't make room.
	bool limit_open_patches(unsigned max_patches) {
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

	// Flag all unmodified patches on vol that they need to be re-loaded from disk
	// the next time the user opens the patch
	void mark_patches_force_reload(Volume vol) {
		for (auto &patch : open_patches_) {
			if (patch.loc.vol == vol && patch.modification_count == 0)
				patch.force_reload = true;
		}
	}

	// Clears the force-reload flag on all open patches with given volume
	void mark_patches_no_reload(Volume vol) {
		for (auto &patch : open_patches_) {
			if (patch.loc.vol == vol)
				patch.force_reload = false;
		}
	}

	// Parses and opens the loaded patch, and sets the view patch to point to it
	bool open_patch(std::span<char> file_data, PatchLocation const &patch_loc) {

		if (open_patches_.find(patch_loc)) {
			open_patches_.remove(patch_loc);
		}

		auto *new_patch = open_patches_.emplace_back(patch_loc);

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
		if (playing_patch_) {
			if (open_patches_.exists(playing_patch_)) {
				pr_dbg("Playing patch exists\n");
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

	void reset_view_patch_modification_count() {
		view_patch_->modification_count = 0;
	}

	unsigned get_view_patch_modification_count() {
		return view_patch_->modification_count;
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

	void update_view_patch_module_states(std::vector<ModuleInitState> const &states) {
		if (view_patch_)
			view_patch_->patch.module_states = states; //copy
		else
			pr_err("Error: tried to update_view_patch_module_states on a null view_patch\n");
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
