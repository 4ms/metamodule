#pragma once
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/base.hh"
#include "gui/pages/confirm_popup.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/styles.hh"

namespace MetaModule
{

struct SystemMenuPage : PageBase {
	SystemMenuPage(PatchInfo info)
		: PageBase{info, PageId::SystemMenu}
		, tabs(lv_tabview_get_tab_btns(ui_SystemMenuTabView)) {

		init_bg(ui_SystemMenu);

		lv_group_remove_all_objs(group);
		lv_group_add_obj(group, tabs);
		lv_group_set_editing(group, true);

		lv_obj_add_event_cb(tabs, tab_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_clear_flag(ui_SystemMenuUpdateFWBut, LV_OBJ_FLAG_HIDDEN);
	}

	void prepare_focus() final {
		lv_hide(ui_FWUpdateSpinner);
		lv_group_focus_obj(tabs);
		lv_group_set_editing(group, true);
	}

	void update() final {
		bool pressed_back = metaparams.meta_buttons[0].is_just_released();

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

		auto clicked_tab = lv_btnmatrix_get_selected_btn(page->tabs);
		if (clicked_tab >= 0 && clicked_tab < NumTabs)
			page->active_tab = static_cast<Tabs>(clicked_tab);

		switch (clicked_tab) {
			case Tabs::Status: {
				//...
				break;
			}

			case Tabs::Update: {
				lv_group_remove_all_objs(page->group);
				lv_group_add_obj(page->group, ui_SystemMenuUpdateFWBut);
				break;
			}

			case Tabs::Check: {
				//...
				break;
			}

			case Tabs::Prefs: {
				//...
				break;
			}
		}
	}

	enum Tabs { Status = 0, Prefs = 1, Check = 2, Update = 3, NumTabs };
	Tabs active_tab = Status;
	lv_obj_t *tabs = nullptr;
};

} // namespace MetaModule

