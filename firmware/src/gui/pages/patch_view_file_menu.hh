#pragma once
#include "gui/helpers/lv_helpers.hh"
#include "gui/notify/queue.hh"
#include "gui/pages/patch_selector_sidebar.hh"
#include "gui/pages/save_dialog.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/styles.hh"
#include "lvgl.h"
#include "patch_play/patch_playloader.hh"

namespace MetaModule
{

struct PatchViewFileMenu {

	PatchViewFileMenu(PatchPlayLoader &play_loader,
					  FileStorageProxy &patch_storage,
					  PatchSelectorSubdirPanel &subdir_panel,
					  NotificationQueue &notify_queue)
		: play_loader{play_loader}
		, patch_storage{patch_storage}
		, notify_queue{notify_queue}
		, save_dialog{patch_storage, play_loader, subdir_panel, notify_queue}
		, group(lv_group_create()) {
		lv_obj_set_parent(ui_PatchFileMenu, lv_layer_top());
		lv_show(ui_PatchFileMenu);
		lv_obj_set_x(ui_PatchFileMenu, 140);

		lv_obj_add_event_cb(ui_SaveButton, menu_button_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_PatchFileMenuCloseButton, menu_button_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_PatchFileSaveBut, savebut_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_PatchFileDuplicateBut, saveas_but_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_PatchFileDeleteBut, delete_but_cb, LV_EVENT_CLICKED, this);

		lv_group_add_obj(group, ui_PatchFileMenuCloseButton);
		lv_group_add_obj(group, ui_PatchFileSaveBut);
		lv_group_add_obj(group, ui_PatchFileDuplicateBut);
		lv_group_add_obj(group, ui_PatchFileRevertBut);
		lv_group_add_obj(group, ui_PatchFileDeleteBut);
	}

	void prepare_focus(lv_group_t *parent_group) {
		base_group = parent_group;
		confirm_popup.init(ui_SaveDialogCont, base_group);
	}

	void back() {
		if (save_dialog.is_visible()) {
			save_dialog.hide();

		} else if (visible) {
			hide();
		}
	}

	void hide() {
		save_dialog.hide();
		hide_menu();
	}

	void hide_menu() {
		if (visible) {
			DropOutToRight_Animation(ui_PatchFileMenu, 0);
			auto indev = lv_indev_get_next(nullptr);
			if (indev && base_group)
				lv_indev_set_group(indev, base_group);
			visible = false;
		}
	}

	void show() {
		if (patch_storage.get_view_patch_vol() == Volume::RamDisk ||
			patch_storage.get_view_patch_vol() == Volume::MaxVolumes)
		{
			// patch has not been saved yet:
			lv_group_focus_obj(ui_PatchFileSaveBut);
			lv_obj_add_state(ui_PatchFileRevertBut, LV_STATE_DISABLED);
			lv_obj_add_state(ui_PatchFileDuplicateBut, LV_STATE_DISABLED);
		} else {
			lv_group_focus_obj(ui_PatchFileSaveBut);
			lv_obj_clear_state(ui_PatchFileRevertBut, LV_STATE_DISABLED);
			lv_obj_clear_state(ui_PatchFileDuplicateBut, LV_STATE_DISABLED);
		}

		// Not implemented yet!
		lv_obj_add_state(ui_PatchFileRevertBut, LV_STATE_DISABLED);
		lv_obj_add_state(ui_PatchFileDeleteBut, LV_STATE_DISABLED);

		if (!visible) {
			DropInFromLeft_Animation(ui_PatchFileMenu, 0);
			auto indev = lv_indev_get_next(nullptr);
			if (indev && group)
				lv_indev_set_group(indev, group);
			visible = true;
		}
	}

	bool is_visible() {
		return save_dialog.is_visible() || visible;
	}

	void update() {
		save_dialog.update();
		process_delete_file();
	}

	void process_delete_file() {
		if (delete_state == DeleteState::TryRequest) {
			if (patch_storage.delete_view_patch() == FileStorageProxy::WriteResult::Success) {
				delete_state = DeleteState::Requested;
			}
		} else if (delete_state == DeleteState::Requested) {
			auto msg = patch_storage.get_message().message_type;
			if (msg == FileStorageProxy::DeleteFileSuccess) {
				filesystem_changed = true;
			} else if (msg == FileStorageProxy::DeleteFileFailed) {
				notify_queue.put({"Error deleting file", Notification::Priority::Error});
			}
		}
	}

	bool did_filesystem_change() {
		bool result = save_dialog.did_save();
		result |= filesystem_changed;
		filesystem_changed = false;
		return result;
	}

private:
	void show_save_dialog() {
		save_dialog.prepare_focus(base_group);

		lv_obj_set_x(ui_PatchFileMenu, 220);
		visible = false;

		save_dialog.show();
	}

	void copy_patchname_to_filename() {
		std::string patchname = patch_storage.get_view_patch()->patch_name;
		patchname.append(".yml");
		patch_storage.set_patch_filename(patchname);
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
			page->filesystem_changed = true;
		}
	}

	static void saveas_but_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<PatchViewFileMenu *>(event->user_data);

		// If the filename has not been set yet, set it to the patchname + .yml
		if (page->patch_storage.get_view_patch_filename().starts_with("Untitled Patch ")) {
			page->copy_patchname_to_filename();
		}
		page->show_save_dialog();
	}

	static void delete_but_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<PatchViewFileMenu *>(event->user_data);

		page->delete_state = DeleteState::TryRequest;
	}

	PatchPlayLoader &play_loader;
	FileStorageProxy &patch_storage;
	NotificationQueue &notify_queue;

	SaveDialog save_dialog;
	ConfirmPopup confirm_popup;

	lv_group_t *group;
	lv_group_t *base_group = nullptr;
	bool visible = false;

	bool filesystem_changed = false;

	enum class DeleteState { Idle, TryRequest, Requested } delete_state = DeleteState::Idle;
};

} // namespace MetaModule
