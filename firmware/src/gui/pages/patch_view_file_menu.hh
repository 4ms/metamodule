#pragma once
#include "gui/styles.hh"
#include "lvgl.h"
// #include "page_list.hh"
// #include "patch/patch_data.hh"
// #include <vector>
#include "gui/slsexport/meta5/ui.h"
#include "patch_file/file_storage_proxy.hh"

namespace MetaModule
{

struct PatchViewFileMenu {

	PatchViewFileMenu(FileStorageProxy &patch_storage)
		: patch_storage{patch_storage}
		, group(lv_group_create()) {

		lv_obj_add_event_cb(ui_AddButton, menu_button_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_PatchFileMenuCloseButton, menu_button_cb, LV_EVENT_CLICKED, this);

		lv_group_add_obj(group, ui_PatchFileMenuCloseButton);
		lv_group_add_obj(group, ui_PatchFileSaveBut);
		lv_group_add_obj(group, ui_PatchFileDuplicateBut);
		lv_group_add_obj(group, ui_PatchFileRevertBut);
		lv_group_add_obj(group, ui_PatchFileDeleteBut);

		lv_obj_set_x(ui_PatchFileMenu, 140);
	}

	void prepare_focus(lv_group_t *parent_group) {
		base_group = group;
	}

	void hide() {
		if (visible) {
			Dropup_Animation(ui_PatchFileMenu, 0);
			auto indev = lv_indev_get_next(nullptr);
			if (indev && base_group)
				lv_indev_set_group(indev, base_group);
			visible = false;
		}
	}

	void show() {
		if (!visible) {
			Dropdown_Animation(ui_PatchFileMenu, 0);
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

		page->patch_storage.write_patch("testpatch.yml");
	}

	FileStorageProxy &patch_storage;
	lv_group_t *group;
	lv_group_t *base_group = nullptr;
	bool visible = false;
};

} // namespace MetaModule
