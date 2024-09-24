#pragma once
#include "gui/helpers/lv_helpers.hh"
#include "gui/notify/queue.hh"
#include "gui/pages/base.hh"
#include "gui/pages/confirm_popup.hh"
#include "gui/pages/make_cable.hh"
#include "gui/pages/page_list.hh"
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
					  OpenPatchManager &patches,
					  PatchSelectorSubdirPanel &subdir_panel,
					  NotificationQueue &notify_queue,
					  PageList &page_list,
					  GuiState &gui_state)
		: play_loader{play_loader}
		, patch_storage{patch_storage}
		, patches{patches}
		, notify_queue{notify_queue}
		, page_list{page_list}
		, gui_state{gui_state}
		, save_dialog{patch_storage, patches, play_loader, subdir_panel, notify_queue, page_list}
		, group(lv_group_create()) {
		lv_obj_set_parent(ui_PatchFileMenu, lv_layer_top());
		lv_show(ui_PatchFileMenu);
		lv_obj_set_x(ui_PatchFileMenu, 140);

		lv_obj_add_event_cb(ui_SaveButton, menu_button_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_PatchFileMenuCloseButton, menu_button_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_PatchFileSaveBut, savebut_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_PatchFileDuplicateBut, saveas_but_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_PatchFileDeleteBut, delete_but_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_PatchFileRevertBut, revert_but_cb, LV_EVENT_CLICKED, this);

		lv_group_add_obj(group, ui_PatchFileMenuCloseButton);
		lv_group_add_obj(group, ui_PatchFileSaveBut);
		lv_group_add_obj(group, ui_PatchFileDuplicateBut);
		lv_group_add_obj(group, ui_PatchFileRevertBut);
		lv_group_add_obj(group, ui_PatchFileDeleteBut);
	}

	void prepare_focus(lv_group_t *parent_group) {
		base_group = parent_group;
		confirm_popup.init(lv_layer_top(), base_group);
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
		if (patches.get_view_patch_vol() == Volume::RamDisk || patches.get_view_patch_vol() == Volume::MaxVolumes) {
			// patch has not been saved yet:
			lv_group_focus_obj(ui_PatchFileSaveBut);
			lv_obj_add_state(ui_PatchFileRevertBut, LV_STATE_DISABLED);
			lv_obj_add_state(ui_PatchFileDuplicateBut, LV_STATE_DISABLED);
			lv_obj_add_state(ui_PatchFileDeleteBut, LV_STATE_DISABLED);
			lv_obj_add_state(ui_PatchFileRevertBut, LV_STATE_DISABLED);
		} else {
			lv_group_focus_obj(ui_PatchFileSaveBut);
			lv_obj_clear_state(ui_PatchFileRevertBut, LV_STATE_DISABLED);
			lv_obj_clear_state(ui_PatchFileDuplicateBut, LV_STATE_DISABLED);
			lv_obj_clear_state(ui_PatchFileDeleteBut, LV_STATE_DISABLED);

			if (patches.get_view_patch_modification_count() > 0)
				lv_obj_clear_state(ui_PatchFileRevertBut, LV_STATE_DISABLED);
			else
				lv_obj_add_state(ui_PatchFileRevertBut, LV_STATE_DISABLED);
		}

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
		process_revert_patch();
	}

	void process_delete_file() {
		if (delete_state == DeleteState::TryRequest) {
			if (patch_storage.request_delete_file(patch_loc.filename, patch_loc.vol)) {
				delete_state = DeleteState::Requested;

				if (patches.get_playing_patch_loc_hash() == PatchLocHash{patch_loc}) {
					play_loader.stop_audio();
				}
			}

		} else if (delete_state == DeleteState::Requested) {
			auto msg = patch_storage.get_message().message_type;

			if (msg == FileStorageProxy::DeleteFileSuccess || msg == FileStorageProxy::DeleteFileFailed) {
				// If we made an attempt to delete a file and it failed, then we must assume
				// the file was deleted, or the file is corrupted, or the drive was unmounted.
				// In all these cases the file is not accessible anymore, so act as if it was deleted.
				if (msg == FileStorageProxy::DeleteFileFailed)
					notify_queue.put({"Error deleting file", Notification::Priority::Error});

				filesystem_changed = true;
				delete_state = DeleteState::Idle;

				page_list.remove_history_matching_args(
					{.patch_loc = patch_loc, .patch_loc_hash = PatchLocHash{patch_loc}});

				page_list.request_new_page_no_history(PageId::PatchSel, {});
				patches.close_view_patch();
				hide_menu();
			}
		}
	}

	void process_revert_patch() {
		if (revert_state == RevertState::TryRequest) {
			if (patch_storage.request_load_patch(patch_loc)) {
				revert_state = RevertState::Requested;

				if (patches.get_playing_patch_loc_hash() == PatchLocHash{patch_loc}) {
					was_playing = true;
					play_loader.stop_audio();
				} else
					was_playing = false;
			}

		} else if (revert_state == RevertState::Requested) {
			auto message = patch_storage.get_message();

			if (message.message_type == FileStorageProxy::LoadFileOK) {
				patches.close_view_patch();

				auto data = patch_storage.get_patch_data(message.bytes_read);

				if (patches.open_patch(data, patch_loc)) {
					if (was_playing) {
						play_loader.request_load_view_patch();
					}

					page_list.request_new_page_no_history(
						PageId::PatchView, {.patch_loc = patch_loc, .patch_loc_hash = PatchLocHash{patch_loc}});
					revert_state = RevertState::Idle;
					hide_menu();
				} else {
					notify_queue.put({"Error reverting patch", Notification::Priority::Error, 1000});
				}
			}

			if (message.message_type == FileStorageProxy::LoadFileFailed) {
				notify_queue.put({"Error opening file, not reverted.", Notification::Priority::Error});
				revert_state = RevertState::Idle;
				hide_menu();
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
	void show_save_dialog(SaveDialog::Action method) {
		current_action = method;
		save_dialog.prepare_focus(base_group, method);

		lv_obj_set_x(ui_PatchFileMenu, 220);
		visible = false;

		save_dialog.show();
	}

	void copy_patchname_to_filename() {
		// Copy patchname -> filename if patchname has been set
		std::string patchname = patches.get_view_patch()->patch_name;
		if (!patchname.starts_with("Untitled Patch ")) {
			patchname.append(".yml");
			patches.set_patch_filename(patchname);
		}
	}

	static void menu_button_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<PatchViewFileMenu *>(event->user_data);
		if (page->visible)
			page->hide();
		else {
			abort_cable(page->gui_state, page->notify_queue);
			page->show();
		}
	}

	static void savebut_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<PatchViewFileMenu *>(event->user_data);

		if (page->patches.get_view_patch_vol() == Volume::RamDisk ||
			page->patches.get_view_patch_vol() == Volume::MaxVolumes)
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

		// If it hasn't been saved yet, use the patchname if its been set
		if (page->patches.get_view_patch_vol() == Volume::RamDisk) {
			page->copy_patchname_to_filename();
		}
		page->show_save_dialog(SaveDialog::Action::Duplicate);
	}

	static void rename_but_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<PatchViewFileMenu *>(event->user_data);

		// If it hasn't been saved yet, use the patchname if its been set
		if (page->patches.get_view_patch_vol() == Volume::RamDisk) {
			page->copy_patchname_to_filename();
		}
		page->show_save_dialog(SaveDialog::Action::Rename);
	}

	static void delete_but_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<PatchViewFileMenu *>(event->user_data);

		std::string confirm_msg =
			"Delete " + std::string(page->patches.get_view_patch_filename()) + " on disk? This cannot be undone.";

		page->patch_loc = {page->patches.get_view_patch_filename(), page->patches.get_view_patch_vol()};
		page->confirm_popup.show(
			[page](unsigned choice) {
				if (choice == 1) {
					page->delete_state = DeleteState::TryRequest;
				}
			},
			confirm_msg.c_str(),
			"Delete");
	}

	static void revert_but_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<PatchViewFileMenu *>(event->user_data);

		std::string confirm_msg = "Revert " + std::string(page->patches.get_view_patch_filename()) +
								  " to last saved version on disk? This cannot be undone.";

		page->patch_loc = {page->patches.get_view_patch_filename(), page->patches.get_view_patch_vol()};
		page->confirm_popup.show(
			[page](unsigned choice) {
				if (choice == 1) {
					page->revert_state = RevertState::TryRequest;
				}
			},
			confirm_msg.c_str(),
			"Revert");
	}

	PatchPlayLoader &play_loader;
	FileStorageProxy &patch_storage;
	OpenPatchManager &patches;
	NotificationQueue &notify_queue;
	PageList &page_list;
	GuiState &gui_state;

	SaveDialog save_dialog;
	ConfirmPopup confirm_popup;

	lv_group_t *group;
	lv_group_t *base_group = nullptr;
	bool visible = false;

	bool filesystem_changed = false;
	bool was_playing = false;
	PatchLocation patch_loc;

	enum class DeleteState { Idle, TryRequest, Requested } delete_state = DeleteState::Idle;
	enum class RevertState { Idle, TryRequest, Requested } revert_state = RevertState::Idle;

	SaveDialog::Action current_action{};
};

} // namespace MetaModule
