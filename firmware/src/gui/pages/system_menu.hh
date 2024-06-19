#pragma once
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/base.hh"
#include "gui/pages/confirm_popup.hh"
#include "gui/pages/firmware_update_tab.hh"
#include "gui/pages/page_list.hh"
#include "gui/pages/plugin_tab.hh"
#include "gui/pages/prefs_tab.hh"
#include "gui/pages/system_info_tab.hh"
#include "gui/pages/system_tab.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/styles.hh"
#include "util/poll_event.hh"

namespace MetaModule
{

struct SystemMenuPage : PageBase {

	SystemMenuPage(PatchContext info)
		: PageBase{info, PageId::SystemMenu}
		, plugin_tab{info.plugin_manager, info.notify_queue}
		, system_tab{patch_storage, params, metaparams, patch_playloader}
		, fwupdate_tab{patch_storage, patch_playloader}
		, tab_bar(lv_tabview_get_tab_btns(ui_SystemMenuTabView)) {

		init_bg(ui_SystemMenu);

		lv_group_remove_all_objs(group);
		lv_group_add_obj(group, tab_bar);
		lv_group_set_editing(group, true);

		lv_obj_add_event_cb(tab_bar, tab_cb, LV_EVENT_VALUE_CHANGED, this);
	}

	void prepare_focus() final {
		lv_hide(ui_FWUpdateSpinner);
		lv_tabview_set_act(ui_SystemMenuTabView, 0, LV_ANIM_OFF);
		info_tab.prepare_focus(group);

		lv_group_remove_all_objs(group);
		lv_group_add_obj(group, tab_bar);
		lv_group_focus_obj(tab_bar);
		lv_group_set_editing(group, true);
	}

	void update() final {

		active_tab->update();

		if (metaparams.back_button.is_just_released()) {
			if (!active_tab->consume_back_event()) {

				if (lv_group_get_focused(group) == tab_bar) {
					page_list.request_last_page();
				} else {
					lv_group_remove_all_objs(group);
					lv_group_add_obj(group, tab_bar);
					lv_group_focus_obj(tab_bar);
					lv_group_set_editing(group, true);
				}
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

		page->tab_click();
	}

	void tab_click() {
		lv_group_remove_all_objs(group);
		lv_group_add_obj(group, tab_bar);

		auto active_tab_index = lv_btnmatrix_get_selected_btn(tab_bar);
		active_tab = tabs[active_tab_index];
		active_tab->prepare_focus(group);
	}

	InfoTab info_tab;
	PluginTab plugin_tab;
	PrefsTab prefs_tab;
	SystemTab system_tab;
	FirmwareUpdateTab fwupdate_tab;
	std::array<SystemMenuTab *, 5> tabs{&info_tab, &plugin_tab, &prefs_tab, &system_tab, &fwupdate_tab};
	SystemMenuTab *active_tab = &info_tab;

	lv_obj_t *tab_bar;
};

} // namespace MetaModule
