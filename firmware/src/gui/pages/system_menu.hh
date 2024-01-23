#pragma once
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/base.hh"
#include "gui/pages/confirm_popup.hh"
#include "gui/pages/firmware_update_tab.hh"
#include "gui/pages/hardware_test_tab.hh"
#include "gui/pages/page_list.hh"
#include "gui/pages/prefs_tab.hh"
#include "gui/pages/system_status_tab.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/styles.hh"
#include "util/poll_event.hh"

namespace MetaModule
{

struct SystemMenuPage : PageBase {
	SystemMenuPage(PatchContext info)
		: PageBase{info, PageId::SystemMenu}
		, fwupdate_tab{patch_storage, patch_playloader}
		, prefs_tab{patch_storage}
		, tabs(lv_tabview_get_tab_btns(ui_SystemMenuTabView)) {

		init_bg(ui_SystemMenu);

		lv_group_remove_all_objs(group);
		lv_group_add_obj(group, tabs);
		lv_group_set_editing(group, true);

		lv_obj_add_event_cb(tabs, tab_cb, LV_EVENT_VALUE_CHANGED, this);
	}

	void prepare_focus() final {
		lv_hide(ui_FWUpdateSpinner);
		lv_tabview_set_act(ui_SystemMenuTabView, 0, LV_ANIM_OFF);
		status_tab.prepare_focus(group);

		lv_group_remove_all_objs(group);
		lv_group_add_obj(group, tabs);
		lv_group_focus_obj(tabs);
		lv_group_set_editing(group, true);
	}

	void update() final {
		bool pressed_back = metaparams.meta_buttons[0].is_just_released();

		if (active_tab == Tabs::Update) {
			fwupdate_tab.update();
			if (pressed_back && fwupdate_tab.consume_back_event())
				pressed_back = false;

		} else if (active_tab == Tabs::Prefs) {
			prefs_tab.update();
			if (pressed_back && prefs_tab.consume_back_event())
				pressed_back = false;

		} else if (active_tab == Tabs::Status) {
			status_tab.update();

		} else if (active_tab == Tabs::Check) {
			check_tab.update();
		}

		if (pressed_back) {
			if (lv_group_get_focused(group) == tabs)
				page_list.request_last_page();
			else {
				lv_group_remove_all_objs(group);
				lv_group_add_obj(group, tabs);
				lv_group_focus_obj(tabs);
				lv_group_set_editing(group, true);
			}
		}
	}

	void blur() final {
	}

private:
	static void tab_cb(lv_event_t *event) {
		auto page = static_cast<SystemMenuPage *>(event->user_data);
		if (!page)
			return;

		lv_group_remove_obj(ui_SystemMenuUpdateFWBut);
		lv_group_remove_obj(ui_ResetFactoryPatchesButton);

		switch (lv_btnmatrix_get_selected_btn(page->tabs)) {
			case Tabs::Status: {
				page->active_tab = Tabs::Status;
				page->status_tab.prepare_focus(page->group);
				break;
			}

			case Tabs::Update: {
				page->active_tab = Tabs::Update;
				page->fwupdate_tab.prepare_focus(page->group);
				break;
			}

			case Tabs::Check: {
				page->active_tab = Tabs::Check;
				page->check_tab.prepare_focus(page->group);
				break;
			}

			case Tabs::Prefs: {
				page->active_tab = Tabs::Prefs;
				page->prefs_tab.prepare_focus(page->group);
				break;
			}
		}
	}

	FirmwareUpdateTab fwupdate_tab;
	HardwareTestTab check_tab;
	SystemStatusTab status_tab;
	PrefsTab prefs_tab;

	enum Tabs { Status = 0, Prefs = 1, Check = 2, Update = 3, NumTabs };
	Tabs active_tab = Status;
	lv_obj_t *tabs = nullptr;
};

} // namespace MetaModule
