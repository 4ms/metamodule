#pragma once
#include "gui/helpers/lv_helpers.hh"
#include "gui/notify/queue.hh"
#include "gui/pages/confirm_popup.hh"
#include "gui/pages/module_view_automap.hh"
#include "gui/pages/page_list.hh"
#include "gui/pages/patch_selector_sidebar.hh"
#include "gui/pages/save_dialog.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/styles.hh"
#include "lvgl.h"
#include "patch_play/patch_mod_queue.hh"
#include "patch_play/patch_playloader.hh"
#include "patch_play/randomize_param.hh"

namespace MetaModule
{

struct ModuleViewActionMenu {

	ModuleViewActionMenu(PatchModQueue &patch_mod_queue, OpenPatchManager &patches, PageList &page_list)
		: patch_mod_queue{patch_mod_queue}
		, patches{patches}
		, page_list{page_list}
		, auto_map{patch_mod_queue, patches}
		, randomizer{patch_mod_queue}
		, group(lv_group_create()) {
		lv_obj_set_parent(ui_ModuleViewActionMenu, lv_layer_top());
		lv_show(ui_ModuleViewActionMenu);
		lv_obj_set_x(ui_ModuleViewActionMenu, 140);

		lv_obj_add_event_cb(ui_ModuleViewActionBut, menu_button_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_ModuleViewActionAutopatchBut, autopatch_but_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_ModuleViewActionDeleteBut, delete_but_cb, LV_EVENT_CLICKED, this);
		lv_obj_add_event_cb(ui_ModuleViewActionRandomBut, random_but_cb, LV_EVENT_CLICKED, this);

		lv_group_add_obj(group, ui_ModuleViewActionAutopatchBut);
		lv_group_add_obj(group, ui_ModuleViewActionRandomBut);
		lv_group_add_obj(group, ui_ModuleViewActionDeleteBut);
	}

	void prepare_focus(lv_group_t *parent_group, unsigned module_idx) {
		this->module_idx = module_idx;
		base_group = parent_group;
		confirm_popup.init(lv_layer_top(), base_group);
	}

	void back() {
		if (confirm_popup.is_visible()) {
			confirm_popup.hide();
		} else if (auto_map.is_visible()) {
			auto_map.hide();
		} else if (visible) {
			hide();
		}
	}

	void hide() {
		confirm_popup.hide();
		hide_menu();
	}

	void hide_menu() {
		if (visible) {
			DropOutToRight_Animation(ui_ModuleViewActionMenu, 0);
			auto indev = lv_indev_get_next(nullptr);
			if (indev && base_group)
				lv_indev_set_group(indev, base_group);
			visible = false;
		}
	}

	void show() {
		lv_group_focus_obj(ui_ModuleViewActionAutopatchBut);

		if (!visible) {
			lv_show(ui_ModuleViewActionMenu);
			DropInFromLeft_Animation(ui_ModuleViewActionMenu, 0);
			auto indev = lv_indev_get_next(nullptr);
			if (indev && group)
				lv_indev_set_group(indev, group);
			visible = true;
		}
	}

	bool is_visible() {
		return visible;
	}

	void update() {
		process_delete_module();
		auto_map.update();
	}

private:
	void process_delete_module() {
		if (delete_state == DeleteState::TryRequest) {
			patch_mod_queue.put(RemoveModule{.module_idx = uint16_t(module_idx)});
			delete_state = DeleteState::Requested;
			page_list.remove_history_matching_args(PageArguments{.module_id = module_idx});
		}
	}

	void show_auto_map() {
		hide();
		auto_map.prepare_focus(module_idx, group);
		auto_map.show();
	}

	void randomize() {
		randomizer.randomize(module_idx, patches.get_view_patch());
	}

	static void menu_button_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<ModuleViewActionMenu *>(event->user_data);
		if (page->visible)
			page->hide();
		else
			page->show();
	}

	static void autopatch_but_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<ModuleViewActionMenu *>(event->user_data);

		page->show_auto_map();
	}

	static void random_but_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<ModuleViewActionMenu *>(event->user_data);
		page->randomize();
	}

	static void delete_but_cb(lv_event_t *event) {
		if (!event || !event->user_data)
			return;
		auto page = static_cast<ModuleViewActionMenu *>(event->user_data);

		std::string confirm_msg =
			"Remove this module, all its mappings, and all connected cables from the patch? This cannot be undone.";

		page->confirm_popup.show(
			[page](unsigned choice) {
				if (choice == 1) {
					page->delete_state = DeleteState::TryRequest;
				}
			},
			confirm_msg.c_str(),
			"Delete");
	}

	PatchModQueue &patch_mod_queue;
	OpenPatchManager &patches;
	PageList &page_list;

	ConfirmPopup confirm_popup;

	ModuleViewAutoMapDialog auto_map;
	RandomizeParams randomizer;

	unsigned module_idx = 0;
	lv_group_t *group;
	lv_group_t *base_group = nullptr;
	bool visible = false;

	enum class DeleteState { Idle, TryRequest, Requested } delete_state = DeleteState::Idle;
};

} // namespace MetaModule
