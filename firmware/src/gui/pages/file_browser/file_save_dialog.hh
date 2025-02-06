#pragma once
#include "fs/helpers.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/patch_selector_sidebar.hh"
#include "gui/slsexport/meta5/ui.h"
#include "patch_file/file_storage_proxy.hh"

namespace MetaModule
{

struct FileSaveDialog {

	FileSaveDialog(FileStorageProxy &patch_storage, PatchSelectorSubdirPanel &subdir_panel)
		: patch_storage{patch_storage}
		, subdir_panel{subdir_panel}
		, group(lv_group_create()) {

		lv_group_add_obj(group, ui_SaveDialogFilename);
		lv_group_add_obj(group, ui_SaveDialogDir);
		lv_group_add_obj(group, ui_SaveDialogCancelBut);
		lv_group_add_obj(group, ui_SaveDialogSaveBut);

		lv_obj_add_event_cb(ui_SaveDialogFilename, click_filename_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_SaveDialogDir, click_location_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_SaveDialogCancelBut, cancel_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_SaveDialogSaveBut, save_cb, LV_EVENT_CLICKED, this);

		lv_hide(ui_SaveDialogCont);
		lv_obj_set_parent(ui_SaveDialogCont, lv_layer_top());
	}

	void update() {
		if (mode == Mode::EditDir) {

			//TODO: this state logic should be in PatchSelectorSubdirPanel
			// and let the caller decide what to do on success (besides populate)
			switch (refresh_state) {
				case RefreshState::Idle: {
					//periodically check if patchlist needs updating:
					uint32_t now = lv_tick_get();
					if (now - last_refresh_check_tm > 1000) {
						last_refresh_check_tm = now;
						refresh_state = RefreshState::TryingToRequestPatchList;
					}
				} break;

				case RefreshState::TryingToRequestPatchList:
					if (patch_storage.request_patchlist()) {
						refresh_state = RefreshState::RequestedPatchList;
						// show_spinner();
					}
					break;

				case RefreshState::RequestedPatchList: {
					auto message = patch_storage.get_message().message_type;
					if (message == FileStorageProxy::PatchListChanged) {
						refresh_state = RefreshState::ReloadingPatchList;

					} else if (message == FileStorageProxy::PatchListUnchanged) {
						// hide_spinner();
						refresh_state = RefreshState::Idle;
					}
				} break;

				case RefreshState::ReloadingPatchList:
					subdir_panel.populate(patch_storage.get_patch_list());
					subdir_panel.hide_recent_files();
					// hide_spinner();
					subdir_panel.focus();
					refresh_state = RefreshState::Idle;
					break;
			}
		}
	}

	void show(Volume vol,
			  std::string_view fullpath,
			  std::string_view ext,
			  lv_group_t *parent_group,
			  std::function<void(Volume, std::string_view)> action) {
		this->vcv_save_action = {};
		this->save_action = action;
		show(vol, fullpath, ext);
		base_group = parent_group;
	}

	void show(std::string_view fullpath, std::string_view ext, std::function<void(char *)> action) {
		this->vcv_save_action = action;
		this->save_action = {};
		auto [path, vol] = split_volume(fullpath);
		show(vol, fullpath, ext);
	}

	void hide() {
		if (mode == Mode::EditDir) {
			hide_subdir_panel();
		}

		if (mode == Mode::EditName) {
			hide_keyboard();
		}

		if (mode == Mode::Idle) {
			lv_hide(ui_SaveDialogCont);
			lv_group_activate(base_group);
		}
		mode = Mode::Hidden;
	}

	bool is_visible() {
		return mode != Mode::Hidden;
	}

	void back_event() {
		if (mode == Mode::Idle) {
			lv_hide(ui_SaveDialogCont);
			lv_group_activate(base_group);
			mode = Mode::Hidden;

		} else if (mode == Mode::EditDir) {
			hide_subdir_panel();

		} else if (mode == Mode::EditName) {
			hide_keyboard();
		}
	}

private:
	void show(Volume vol, std::string_view fullpath, std::string_view ext) {

		if (mode == Mode::Hidden) {

			file_vol = vol;
			// Default Volume:
			if (file_vol == Volume::RamDisk)
				file_vol = Volume::NorFlash;

			auto slashpos = fullpath.find_last_of('/');
			if (slashpos != std::string_view::npos) {
				file_path = fullpath.substr(0, slashpos);
				file_name = fullpath.substr(slashpos + 1);
			} else {
				file_path = "";
				file_name = std::string{fullpath};
			}

			file_ext = ext;
			strip_ext();

			lv_label_set_text(ui_SaveDialogFilenameDotyml, ext.data());

			update_dir_label();

			lv_show(ui_SaveDialogCont);
			lv_show(ui_SaveDialogRightCont);

			subdir_panel.set_parent(ui_SaveDialogLeftCont, 0);

			lv_hide(ui_SaveDialogLeftCont);
			lv_hide(ui_Keyboard);

			base_group = lv_indev_get_act()->group;
			lv_group_activate(group);
			lv_group_focus_obj(ui_SaveDialogFilename);
			lv_group_set_editing(group, false);

			mode = Mode::Idle;
			is_renaming = false;
		}
	}

	void hide() {
		if (mode == Mode::Idle) {
			lv_hide(ui_SaveDialogCont);
			lv_group_activate(base_group);
			lv_label_set_text(ui_PatchName, patches.get_view_patch_filename().data());
			mode = Mode::Hidden;

		} else if (mode == Mode::EditDir) {
			hide_subdir_panel();

		} else if (mode == Mode::EditName) {
			hide_keyboard();
		}
	}

	void show_keyboard() {
		mode = Mode::EditName;

		lv_obj_add_state(ui_SaveDialogFilename, LV_STATE_USER_1);

		while (lv_obj_remove_event_cb(ui_Keyboard, nullptr))
			;
		lv_obj_add_event_cb(ui_Keyboard, lv_keyboard_def_event_cb, LV_EVENT_VALUE_CHANGED, nullptr);
		lv_obj_add_event_cb(ui_Keyboard, keyboard_cb, LV_EVENT_READY, this);
		lv_obj_add_event_cb(ui_Keyboard, keyboard_cb, LV_EVENT_CANCEL, this);

		lv_show(ui_Keyboard);
		lv_group_add_obj(group, ui_Keyboard);
		lv_group_focus_obj(ui_Keyboard);
		lv_group_set_editing(group, true);
		lv_obj_add_flag(ui_Keyboard, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);

		lv_obj_set_parent(ui_Keyboard, ui_SaveDialogCont);
		lv_obj_set_y(ui_Keyboard, 108);
	}

	void hide_keyboard() {
		mode = Mode::Idle;
		file_name = lv_textarea_get_text(ui_SaveDialogFilename);
		strip_ext();
		lv_textarea_set_text(ui_SaveDialogFilename, file_name.c_str());

		lv_obj_clear_state(ui_SaveDialogFilename, LV_STATE_USER_1);
		lv_group_focus_obj(ui_SaveDialogFilename);
		lv_group_remove_obj(ui_Keyboard);
		lv_hide(ui_Keyboard);
	}

	void show_subdir_panel() {
		mode = Mode::EditDir;

		lv_show(ui_SaveDialogLeftCont);

		subdir_panel.focus();

		subdir_panel.focus_cb = nullptr;

		subdir_panel.click_cb = [this](Volume vol, std::string_view dir) {
			file_path = dir;
			file_vol = vol;
			update_dir_label();
			hide_subdir_panel();
		};

		EntryInfo selected_patch{.kind = DirEntryKind::Dir, .vol = file_vol, .path = file_path};
		subdir_panel.refresh(selected_patch);
		subdir_panel.hide_recent_files();
	}

	void hide_subdir_panel() {
		mode = Mode::Idle;

		lv_hide(ui_SaveDialogLeftCont);
		lv_group_activate(group);
	}

	void update_dir_label() {
		strip_ext();
		lv_textarea_set_text(ui_SaveDialogFilename, file_name.c_str());

		auto displayed_path = std::string{PatchDirList::get_vol_name(file_vol)};
		displayed_path.append(file_path);
		lv_label_set_text(ui_SaveDialogDir, displayed_path.c_str());
	}

	void strip_ext() {
		if (file_name.ends_with(file_ext)) {
			file_name = file_name.substr(0, file_name.length() - file_ext.length());
		}
	}

	static void click_filename_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<FileSaveDialog *>(event->user_data);

		auto kb_hidden = lv_obj_has_flag(ui_Keyboard, LV_OBJ_FLAG_HIDDEN);
		if (kb_hidden) {
			page->show_keyboard();
			lv_keyboard_set_textarea(ui_Keyboard, event->target);
			lv_obj_scroll_to_view_recursive(event->target, LV_ANIM_ON);
		}
	}

	static void click_location_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<FileSaveDialog *>(event->user_data);
		page->show_subdir_panel();
	}

	static void save_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<FileSaveDialog *>(event->user_data);

		page->save();
		page->hide();
	}

	void save() {
		// Ensure file name ends in extension exactly once
		file_name = lv_textarea_get_text(ui_SaveDialogFilename);
		strip_ext();
		file_name.append(file_ext);

		if (save_action) {
			save_action(file_vol, make_full_path(file_path, file_name));
		}

		else if (vcv_save_action)
		{
			// Allocate a char*, because save_action will free() it.
			// (this is a requirement of the Rack API)
			auto path = make_full_path(file_vol, file_path, file_name);
			char *str = strndup(path.data(), path.length());
			vcv_save_action(str);
		}
	}

	static void cancel_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<FileSaveDialog *>(event->user_data);
		page->hide();
	}

	static void keyboard_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<FileSaveDialog *>(event->user_data);

		if (event->code == LV_EVENT_READY || event->code == LV_EVENT_CANCEL) {
			page->hide_keyboard();
		}
	}

	FileStorageProxy &patch_storage;
	PatchSelectorSubdirPanel &subdir_panel;

	Volume file_vol{};
	std::string file_path;
	std::string file_name;
	std::string file_ext;

	lv_group_t *group;
	lv_group_t *base_group = nullptr;
	enum class Mode { Hidden, Idle, EditDir, EditName } mode = Mode::Hidden;

	enum class RefreshState {
		Idle,
		TryingToRequestPatchList,
		RequestedPatchList,
		ReloadingPatchList
	} refresh_state{RefreshState::TryingToRequestPatchList};

	uint32_t last_refresh_check_tm = 0;

	std::function<void(char *)> vcv_save_action;
	std::function<void(Volume, std::string_view)> save_action;
};

} // namespace MetaModule
