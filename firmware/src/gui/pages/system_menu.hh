#pragma once
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/base.hh"
#include "gui/pages/confirm_popup.hh"
#include "gui/pages/firmware_update_tab.hh"
#include "gui/pages/page_list.hh"
#include "gui/pages/plugin_tab.hh"
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
		, plugin_tab{info.plugin_manager, info.notify_queue}
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
		bool pressed_back = metaparams.back_button.is_just_released();

		if (active_tab == Tabs::Update) {
			fwupdate_tab.update();
			if (pressed_back && fwupdate_tab.consume_back_event())
				pressed_back = false;

		} else if (active_tab == Tabs::Prefs) {
			prefs_tab.update();
			if (pressed_back && prefs_tab.consume_back_event())
				pressed_back = false;

		} else if (active_tab == Tabs::Info) {
			status_tab.update();

		} else if (active_tab == Tabs::Plugins) {
			plugin_tab.update();
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

		lv_group_remove_all_objs(page->group);
		lv_group_add_obj(page->group, page->tabs);
		// lv_group_remove_obj(ui_SystemMenuUpdateFWBut);
		// lv_group_remove_obj(ui_ResetFactoryPatchesButton);

		switch (lv_btnmatrix_get_selected_btn(page->tabs)) {
			case Tabs::Info: {
				page->active_tab = Tabs::Info;
				page->status_tab.prepare_focus(page->group);
				break;
			}

			case Tabs::Update: {
				page->active_tab = Tabs::Update;
				page->fwupdate_tab.prepare_focus(page->group);
				break;
			}

			case Tabs::Plugins: {
				page->active_tab = Tabs::Plugins;
				page->plugin_tab.prepare_focus(page->group);
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
	PluginTab plugin_tab;
	SystemStatusTab status_tab;
	PrefsTab prefs_tab;

	enum Tabs { Plugins = 0, Info = 1, Prefs = 2, Update = 3, NumTabs };
	Tabs active_tab = Plugins;
	lv_obj_t *tabs = nullptr;
};

} // namespace MetaModule
