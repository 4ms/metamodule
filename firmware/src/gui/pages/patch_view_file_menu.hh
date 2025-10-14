#pragma once
#include "gui/helpers/lv_helpers.hh"
#include "gui/notify/queue.hh"
#include "gui/pages/confirm_popup.hh"
#include "gui/pages/make_cable.hh"
#include "gui/pages/missing_plugin_scan.hh"
#include "gui/pages/page_list.hh"
#include "gui/pages/patch_save_dialog.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/slsexport/ui_local.h"
#include "patch_play/patch_playloader.hh"

namespace MetaModule
{

struct PatchViewFileMenu {
	static constexpr bool SavingMakesStartupPatch = false;

	PatchViewFileMenu(PatchPlayLoader &play_loader,
					  FileStorageProxy &patch_storage,
					  OpenPatchManager &patches,
					  FileSaveDialog &file_save_dialog,
					  NotificationQueue &notify_queue,
					  PageList &page_list,
					  GuiState &gui_state,
					  UserSettings &settings,
					  PluginManager &plugin_manager,
					  MissingPluginScanner &missing_plugins)
		: play_loader{play_loader}
		, patch_storage{patch_storage}
		, patches{patches}
		, notify_queue{notify_queue}
		, page_list{page_list}
		, gui_state{gui_state}
		, settings{settings}
		, patch_save_dialog{patch_storage, patches, play_loader, file_save_dialog, notify_queue, page_list}
		, group(lv_group_create())
		, missing_plugins{missing_plugins} {
		lv_obj_set_parent(ui_PatchFileMenu, lv_layer_top());
		lv_show(ui_PatchFileMenu);
		lv_obj_set_x(ui_PatchFileMenu, 140);

		lv_obj_add_event_cb(ui_SaveButton, menu_button_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_PatchFileMenuCloseButton, menu_button_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_PatchFileSaveBut, savebut_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_PatchFileDuplicateBut, saveas_but_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_PatchFileRenameBut, rename_but_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_PatchFileDeleteBut, delete_but_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_PatchFileRevertBut, revert_but_cb, LV_EVENT_CLICKED, this);

		make_default_patch_menu = create_file_menu_item(ui_PatchFileMenu, "Startup patch");
		lv_obj_move_to_index(make_default_patch_menu, 6);
		lv_obj_add_event_cb(make_default_patch_menu, make_startup_patch, LV_EVENT_CLICKED, this);

		lv_group_add_obj(group, ui_PatchFileMenuCloseButton);
		lv_group_add_obj(group, ui_PatchFileSaveBut);
		lv_group_add_obj(group, ui_PatchFileDuplicateBut);
		lv_group_add_obj(group, ui_PatchFileRenameBut);
		lv_group_add_obj(group, ui_PatchFileRevertBut);
		lv_group_add_obj(group, make_default_patch_menu);
		lv_group_add_obj(group, ui_PatchFileDeleteBut);

		lv_obj_set_width(ui_PatchFileMenu, 140);
		lv_label_set_text(ui_PatchFileRenameLabel, "Move/Rename");
	}

	void prepare_focus(lv_group_t *parent_group) {
		base_group = parent_group;
		confirm_popup.init(lv_layer_top(), base_group);
	}

	void back() {
		if (confirm_popup.is_visible()) {
			confirm_popup.hide();
			hide_menu();

		} else if (missing_plugins.is_visible()) {
			missing_plugins.hide();
			hide_menu();

		} else if (visible) {
			hide();
		}
	}

	void hide() {
		patch_save_dialog.hide();
		confirm_popup.hide();
		hide_menu();
	}

	void hide_menu() {
		if (visible) {
			if (lv_obj_get_x(ui_PatchFileMenu) <= 180)
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
			lv_disable(ui_PatchFileRevertBut);
			lv_disable(ui_PatchFileDuplicateBut);
			lv_disable(ui_PatchFileRenameBut);
			lv_enable(ui_PatchFileDeleteBut);
			lv_label_set_text(lv_obj_get_child(make_default_patch_menu, 0), "Startup Patch");
		} else {
			lv_group_focus_obj(ui_PatchFileSaveBut);
			lv_enable(ui_PatchFileDuplicateBut);
			lv_enable(ui_PatchFileRenameBut);
			lv_enable(ui_PatchFileDeleteBut);
			lv_enable(ui_PatchFileRevertBut);

			if (is_viewpatch_default()) {
				lv_label_set_text(lv_obj_get_child(make_default_patch_menu, 0), "\xEF\x80\x8C Startup Patch");
			} else {
				lv_label_set_text(lv_obj_get_child(make_default_patch_menu, 0), "Startup Patch");
			}

			lv_label_set_text(ui_PatchFileRevertLabel,
							  patches.get_view_patch_modification_count() == 0 ? "Reload" : "Revert");
		}

		if (!visible) {
			DropInFromLeft_Animation(ui_PatchFileMenu, 0);
			auto indev = lv_indev_get_next(nullptr);
			if (indev && group)
				lv_indev_set_group(indev, group);
			visible = true;
		}

		reverted_patch = false;
	}

	bool is_visible() {
		return confirm_popup.is_visible() || patch_save_dialog.is_visible() || missing_plugins.is_visible() ||
			   !missing_plugins.is_done_processing() || visible;
	}

	void update() {
		if (is_visible()) {
			process_delete_file();
			process_revert_patch();
		} else {
			process_rename_patch();
		}
	}

	void process_rename_patch() {
		if (play_loader.is_renaming_idle()) {
			if (patch_save_dialog.did_rename()) {
				filesystem_changed = true;
			}
		}
	}

	void process_delete_file() {
		if (delete_state == DeleteState::TryRequest) {
			if (patch_loc.vol == Volume::RamDisk) {
				// Patch has never been saved, so just remove it from open patches
				// and from history
				if (patches.get_playing_patch_loc_hash() == PatchLocHash{patch_loc}) {
					play_loader.stop_audio();
				}
				patches.close_view_patch();
				page_list.remove_history_matching_args(
					{.patch_loc = patch_loc, .patch_loc_hash = PatchLocHash{patch_loc}});
				page_list.request_new_page_no_history(PageId::PatchSel, {});
				hide_menu();
				delete_state = DeleteState::Idle;

			} else if (patch_storage.request_delete_file(patch_loc.filename, patch_loc.vol)) {
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
		switch (revert_state) {
			case RevertState::Idle:
				break;

			case RevertState::LoadMissingPlugins:
				missing_plugins.start();
				revert_state = RevertState::ProcessMissingPlugins;
				break;

			case RevertState::ProcessMissingPlugins:
				missing_plugins.process(
					patches.get_view_patch(), group, [this] { revert_state = RevertState::TryRequest; });
				break;

			case RevertState::TryRequest: {
				if (patch_storage.request_load_patch(patch_loc)) {
					revert_state = RevertState::Requested;

					if (patches.get_playing_patch_loc_hash() == PatchLocHash{patch_loc}) {
						was_playing = true;
						play_loader.stop_audio();
					} else
						was_playing = false;
				}

			} break;

			case RevertState::Requested: {
				auto message = patch_storage.get_message();

				if (message.message_type == FileStorageProxy::LoadFileOK) {
					auto data = patch_storage.get_patch_data(message.bytes_read);

					if (patches.open_patch(data, patch_loc, message.timestamp)) {
						if (was_playing) {
							play_loader.request_load_view_patch();
						}

						page_list.request_new_page_no_history(
							PageId::PatchView, {.patch_loc = patch_loc, .patch_loc_hash = PatchLocHash{patch_loc}});

						gui_state.force_redraw_patch = true;
						revert_state = RevertState::Idle;
						reverted_patch = true;

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
			} break;
		}
	}

	bool did_reload() {
		auto t = reverted_patch;
		reverted_patch = false;
		return t;
	}

	bool did_filesystem_change() {
		bool result = patch_save_dialog.did_save();
		if (SavingMakesStartupPatch && result)
			make_viewpatch_default();
		result |= filesystem_changed;
		filesystem_changed = false;
		return result;
	}

private:
	void show_save_dialog(PatchSaveDialog::Action method) {
		current_action = method;
		patch_save_dialog.prepare_focus(method);

		lv_obj_set_x(ui_PatchFileMenu, 200);
		visible = false;

		hide_menu();
		patch_save_dialog.show(base_group);
	}

	bool is_viewpatch_default() {
		return (settings.load_initial_patch == true && settings.initial_patch_vol == patches.get_view_patch_vol() &&
				settings.initial_patch_name == patches.get_view_patch_filename());
	}

	bool make_viewpatch_default() {
		if (!is_viewpatch_default()) {
			settings.load_initial_patch = true;
			settings.initial_patch_vol = patches.get_view_patch_vol();
			settings.initial_patch_name = patches.get_view_patch_filename();

			pr_info("Will set last_patch opened to %s on %d\n",
					settings.initial_patch_name.c_str(),
					settings.initial_patch_vol);

			gui_state.do_write_settings = get_time();
			return true;
		} else
			// already is the default
			return false;
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
			if (SavingMakesStartupPatch)
				page->make_viewpatch_default();
			page->filesystem_changed = true;
			page->hide_menu();
		}
	}

	static void saveas_but_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<PatchViewFileMenu *>(event->user_data);

		// If it hasn't been saved yet, then we can't duplicate, so save
		if (page->patches.get_view_patch_vol() == Volume::RamDisk)
			page->show_save_dialog(PatchSaveDialog::Action::Save);
		else
			page->show_save_dialog(PatchSaveDialog::Action::Duplicate);
	}

	static void rename_but_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<PatchViewFileMenu *>(event->user_data);

		page->show_save_dialog(PatchSaveDialog::Action::Rename);
	}

	static void delete_but_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<PatchViewFileMenu *>(event->user_data);

		std::string confirm_msg =
			"Delete " + page->patches.get_view_patch_filename() + " on disk? This cannot be undone.";

		page->patch_loc = {page->patches.get_view_patch_filename(), page->patches.get_view_patch_vol()};

		page->confirm_popup.show(
			[page](unsigned choice) {
				if (choice == 1) {
					page->delete_state = DeleteState::TryRequest;
				} else {
					page->hide_menu();
				}
			},
			confirm_msg.c_str(),
			"Delete");
	}

	static void revert_but_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<PatchViewFileMenu *>(event->user_data);

		std::string confirm_msg = std::string(lv_label_get_text(ui_PatchFileRevertLabel)) + " " +
								  page->patches.get_view_patch_filename() +
								  " to last saved version? This cannot be undone.";

		page->patch_loc = {page->patches.get_view_patch_filename(), page->patches.get_view_patch_vol()};
		page->confirm_popup.show(
			[page](unsigned choice) {
				if (choice == 1) {
					page->revert_state = RevertState::LoadMissingPlugins;
				} else {
					page->hide_menu();
				}
			},
			confirm_msg.c_str(),
			lv_label_get_text(ui_PatchFileRevertLabel));
	}

	static void make_startup_patch(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<PatchViewFileMenu *>(event->user_data);

		if (page->make_viewpatch_default()) {
			lv_label_set_text(lv_obj_get_child(page->make_default_patch_menu, 0), "\xEF\x80\x8C Startup Patch");
		} else {
			page->settings.load_initial_patch = false;
			page->gui_state.do_write_settings = true;
			lv_label_set_text(lv_obj_get_child(page->make_default_patch_menu, 0), "Startup Patch");
		}
	}

	PatchPlayLoader &play_loader;
	FileStorageProxy &patch_storage;
	OpenPatchManager &patches;
	NotificationQueue &notify_queue;
	PageList &page_list;
	GuiState &gui_state;
	UserSettings &settings;

	PatchSaveDialog patch_save_dialog;
	ConfirmPopup confirm_popup;

	lv_obj_t *make_default_patch_menu = nullptr;

	lv_group_t *group;
	lv_group_t *base_group = nullptr;
	bool visible = false;

	bool filesystem_changed = false;
	bool was_playing = false;
	PatchLocation patch_loc;

	enum class DeleteState { Idle, TryRequest, Requested } delete_state = DeleteState::Idle;
	enum class RevertState {
		Idle,
		LoadMissingPlugins,
		ProcessMissingPlugins,
		TryRequest,
		Requested
	} revert_state = RevertState::Idle;
	bool reverted_patch = false;

	PatchSaveDialog::Action current_action{};

	MissingPluginScanner &missing_plugins;
};

} // namespace MetaModule
