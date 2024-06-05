#pragma once
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/patch_selector_sidebar.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/styles.hh"
#include "lvgl.h"
#include "patch_play/patch_playloader.hh"

namespace MetaModule
{

struct SaveDialog {

	SaveDialog(FileStorageProxy &patch_storage)
		: patch_storage{patch_storage}
		, group(lv_group_create()) {

		lv_group_add_obj(group, ui_SaveDialogFilename);
		lv_group_add_obj(group, ui_SaveDialogDir);

		lv_obj_add_event_cb(ui_SaveDialogFilename, click_filename_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_SaveDialogDir, click_location_cb, LV_EVENT_CLICKED, this);

		lv_hide(ui_SaveDialogCont);
	}

	void prepare_focus(lv_group_t *parent_group) {
		base_group = parent_group;
	}

	void show() {
		if (state == State::Hidden) {
			auto path = std::string{PatchDirList::get_vol_name(patch_storage.get_view_patch_vol())};
			auto filename = std::string_view{patch_storage.get_view_patch_filename()};

			auto slashpos = filename.find_last_of('/');
			if (slashpos != std::string_view::npos) {
				path.append(filename.substr(0, slashpos));
				filename = filename.substr(slashpos + 1);
			}
			lv_textarea_set_text(ui_SaveDialogFilename, filename.data());
			lv_label_set_text(ui_SaveDialogDir, path.c_str());

			lv_show(ui_SaveDialogCont);
			lv_show(ui_SaveDialogRightCont);

			subdir_panel.set_parent(ui_SaveDialogLeftCont, 0);

			lv_hide(ui_SaveDialogLeftCont);
			lv_hide(ui_SaveAsKeyboard);

			auto indev = lv_indev_get_next(nullptr);
			if (indev && group)
				lv_indev_set_group(indev, group);
			lv_group_focus_obj(ui_SaveDialogFilename);
			lv_group_set_editing(group, false);

			state = State::Idle;
		}
	}

	void show_keyboard() {
		state = State::EditDir;
		lv_show(ui_SaveAsKeyboard);
	}

	void hide_keyboard() {
		lv_hide(ui_SaveAsKeyboard);
	}

	void show_subdir_panel() {
		state = State::EditDir;
		lv_show(ui_SaveDialogLeftCont);

		// subdir_panel.populate(group, patch_storage.get_patch_list());
		subdir_panel.focus();

		subdir_panel.focus_cb = [this](PatchDir *dir, lv_obj_t *target) {
			pr_dbg("SaveDialog: show_subdir_panel\n");
			auto parent = lv_obj_get_parent(target);

			Volume this_vol{};

			for (auto [vol, vol_cont] : zip(PatchDirList::vols, subdir_panel.vol_conts)) {
				if (parent == vol_cont) {
					this_vol = vol;
					break;
				}
			}
			pr_dbg("SaveDialog focus %d\n", this_vol);

			// for (auto [i, entry] : enumerate(roller_item_infos)) {
			// 	if (entry.path == dir->name && entry.vol == this_vol) {
			// 		lv_roller_set_selected(ui_PatchListRoller, i + 1, LV_ANIM_ON);
			// 		break;
			// 	}
			// }
		};

		subdir_panel.click_cb = [this]() {
			pr_dbg("SaveDialog click\n");
			hide_subdir_panel();
		};

		EntryInfo no_patch{.kind = {}, .vol = Volume::RamDisk, .name = patch_storage.get_view_patch_filename()};
		subdir_panel.refresh(no_patch);
	}

	void hide_subdir_panel() {
		lv_hide(ui_SaveDialogLeftCont);
	}

	bool is_visible() {
		return state != State::Hidden;
	}

	void hide() {
		if (state == State::Idle) {
			pr_dbg("hide(); idle->hidden\n");
			lv_hide(ui_SaveDialogCont);
			auto indev = lv_indev_get_next(nullptr);
			if (indev && base_group)
				lv_indev_set_group(indev, base_group);
			state = State::Hidden;

		} else if (state == State::EditDir) {
			pr_dbg("hide(); editdir->idle\n");
			hide_subdir_panel();
			state = State::Idle;

		} else if (state == State::EditName) {
			pr_dbg("hide(); editname->idle\n");
			hide_keyboard();
			state = State::Idle;
		}
	}

private:
	static void click_filename_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<SaveDialog *>(event->user_data);
		page->show_keyboard();
	}

	static void click_location_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<SaveDialog *>(event->user_data);
		page->show_subdir_panel();
	}

	FileStorageProxy &patch_storage;

	PatchSelectorSubdirPanel subdir_panel;
	std::vector<EntryInfo> subdir_panel_patches;

	lv_group_t *group;
	lv_group_t *base_group = nullptr;
	enum class State { Hidden, Idle, EditDir, EditName } state = State::Hidden;
};

} // namespace MetaModule
