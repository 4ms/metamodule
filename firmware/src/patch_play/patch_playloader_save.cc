#include "patch_play/patch_playloader.hh"
#include "patch_to_yaml.hh"

namespace MetaModule
{

void PatchPlayLoader::request_rename_view_patch(PatchLocation const &loc) {
	old_loc = {patches_.get_view_patch_filename(), patches_.get_view_patch_vol()};
	new_loc = loc;
	rename_state_ = RenameState::RequestSaveNew;
}

Result PatchPlayLoader::save_patch(PatchLocation const &loc) {
	auto view_patch = patches_.get_view_patch();

	if (view_patch && view_patch == patches_.get_playing_patch()) {
		get_module_states();
	}

	std::span<char> filedata = storage_.get_patch_data();
	patch_to_yaml_buffer(*view_patch, filedata);

	auto res = storage_.request_write_file(filedata, loc.vol, loc.filename);

	if (res == FileStorageProxy::WriteResult::Success) {
		should_save_patch_ = false;
		saving_patch_ = true;
		return {true, "Saving..."};

	} else if (res == FileStorageProxy::WriteResult::Busy) {
		// message system is busy, try again next time
		return {true, ""};

	} else {
		// error with filename or volume, do not retry
		should_save_patch_ = false;
		saving_patch_ = false;
		return {false, "File name or volume invalid"};
	}
}

Result PatchPlayLoader::save_patch() {
	return save_patch({patches_.get_view_patch_filename(), patches_.get_view_patch_vol()});
}

Result PatchPlayLoader::check_save_patch_status() {
	auto msg = storage_.get_message();

	if (msg.message_type == FileStorageProxy::WriteFileFail) {
		saving_patch_ = false;
		return {false, "Failed to write patch."};

	} else if (msg.message_type == FileStorageProxy::WriteFileOK) {
		saving_patch_ = false;
		patches_.reset_view_patch_modification_count();
		patches_.set_view_patch_timestamp(msg.timestamp);
		patches_.set_view_patch_filesize(msg.length);
		return {true, "Saved"};

	} else {
		return {true, ""};
	}
}

Result PatchPlayLoader::check_delete_file_status() {
	auto msg = storage_.get_message();

	if (msg.message_type == FileStorageProxy::DeleteFileFailed) {
		return {false, "Failed to remove original patch."};

	} else if (msg.message_type == FileStorageProxy::DeleteFileSuccess) {
		return {true, "Patch Moved"};

	} else {
		return {true, ""};
	}
}

Result PatchPlayLoader::process_renaming() {
	if (rename_state_ == RenameState::RequestSaveNew) {
		auto res = save_patch(new_loc);
		if (saving_patch_) {
			rename_state_ = RenameState::SavingNew;
		}
		return res;
	}

	if (rename_state_ == RenameState::SavingNew) {
		auto res = check_save_patch_status();
		if (saving_patch_ == false) {
			if (res.success) {
				attempts = 0;
				patches_.rename_view_patch_file(new_loc.filename, new_loc.vol);
				rename_state_ = RenameState::RequestDeleteOld;
			} else {
				rename_state_ = RenameState::Idle; //Fail
			}
		}
		return res;
	}

	if (rename_state_ == RenameState::RequestDeleteOld) {
		if (storage_.request_delete_file(old_loc.filename, old_loc.vol)) {
			rename_state_ = RenameState::DeletingOld;
			return {true, ""};
		} else {
			if (attempts++ > 100) {
				rename_state_ = RenameState::Idle;
				return {false, "Failed to request deleting old file"};
			}
		}
	}

	if (rename_state_ == RenameState::DeletingOld) {
		auto res = check_delete_file_status();
		if (res.error_string.length() > 0) {
			rename_state_ = RenameState::Idle;
		}
		return res;
	}

	return {true, ""};
}

} // namespace MetaModule
