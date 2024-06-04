#pragma once
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/patch_selector_sidebar.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/styles.hh"
#include "lvgl.h"
#include "patch_play/patch_playloader.hh"

namespace MetaModule
{

struct PatchViewFileMenu {

	PatchViewFileMenu(PatchPlayLoader &play_loader, FileStorageProxy &patch_storage)
		: play_loader{play_loader}
		, patch_storage{patch_storage}
		, group(lv_group_create()) {
		lv_obj_set_parent(ui_PatchFileMenu, lv_layer_top());
		lv_show(ui_PatchFileMenu);
		lv_obj_set_x(ui_PatchFileMenu, 140);

		lv_obj_add_event_cb(ui_SaveButton, menu_button_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_PatchFileMenuCloseButton, menu_button_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_PatchFileSaveBut, savebut_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_PatchFileDuplicateBut, saveas_but_cb, LV_EVENT_CLICKED, this);

		lv_group_add_obj(group, ui_PatchFileMenuCloseButton);
		lv_group_add_obj(group, ui_PatchFileSaveBut);
		lv_group_add_obj(group, ui_PatchFileDuplicateBut);
		lv_group_add_obj(group, ui_PatchFileRevertBut);
		lv_group_add_obj(group, ui_PatchFileDeleteBut);
	}

	void prepare_focus(lv_group_t *parent_group) {
		base_group = parent_group;
	}

	void hide() {
		if (visible) {
			DropOutToRight_Animation(ui_PatchFileMenu, 0);
			auto indev = lv_indev_get_next(nullptr);
			if (indev && base_group)
				lv_indev_set_group(indev, base_group);
			visible = false;
		}
	}

	void show() {
		if (!visible) {
			DropInFromLeft_Animation(ui_PatchFileMenu, 0);
			auto indev = lv_indev_get_next(nullptr);
			if (indev && group)
				lv_indev_set_group(indev, group);
			visible = true;
		}
	}

	bool is_visible() {
		return visible;
	}

private:
	void show_file_save_dialog() {
		lv_show(ui_SaveDialogCont);
		lv_hide(ui_SaveAsKeyboard);
		subdir_panel.focus();
		subdir_panel.set_parent(ui_SaveDialogCont, 2);
		subdir_panel.focus_cb = [this](PatchDir *dir, lv_obj_t *target) {
			auto parent = lv_obj_get_parent(target);

			Volume this_vol{};

			for (auto [vol, vol_cont] : zip(PatchDirList::vols, subdir_panel.vol_conts)) {
				if (parent == vol_cont) {
					this_vol = vol;
					break;
				}
			}
			pr_dbg("focus %d\n", this_vol);

			// for (auto [i, entry] : enumerate(roller_item_infos)) {
			// 	if (entry.path == dir->name && entry.vol == this_vol) {
			// 		lv_roller_set_selected(ui_PatchListRoller, i + 1, LV_ANIM_ON);
			// 		break;
			// 	}
			// }
		};

		subdir_panel.click_cb = [this]() {
			pr_dbg("click\n");
			// blur_subdir_panel();
		};

		EntryInfo no_patch{.kind = {}, .vol = Volume::RamDisk, .name = patch_storage.get_view_patch_filename()};
		subdir_panel.refresh(no_patch);
	}

	static void menu_button_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<PatchViewFileMenu *>(event->user_data);
		if (page->visible)
			page->hide();
		else
			page->show();
	}

	static void savebut_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<PatchViewFileMenu *>(event->user_data);

		if (page->patch_storage.get_view_patch_vol() == Volume::RamDisk ||
			page->patch_storage.get_view_patch_vol() == Volume::MaxVolumes)
		{
			//Patch is not saved yet, do a save as...
			saveas_but_cb(event);
		} else {
			page->play_loader.request_save_patch();
		}
	}

	static void saveas_but_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<PatchViewFileMenu *>(event->user_data);
		page->show_file_save_dialog();
	}

	PatchPlayLoader &play_loader;
	FileStorageProxy &patch_storage;

	lv_group_t *group;
	lv_group_t *saveas_group;
	lv_group_t *base_group = nullptr;
	bool visible = false;

	PatchSelectorSubdirPanel subdir_panel;
	std::vector<EntryInfo> subdir_panel_patches;
};

} // namespace MetaModule
