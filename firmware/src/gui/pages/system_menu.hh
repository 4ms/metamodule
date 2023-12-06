#pragma once
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/base.hh"
#include "gui/pages/confirm_popup.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/meta5/ui.h"

namespace MetaModule
{

struct SystemMenuPage : PageBase {
	SystemMenuPage(PatchInfo info)
		: PageBase{info, PageId::SystemMenu} {

		init_bg(ui_SystemMenu);

		tabs = lv_tabview_get_tab_btns(ui_TabView1); //NOLINT
		lv_group_remove_all_objs(group);
		lv_group_add_obj(group, tabs);
		lv_group_set_editing(group, true);

		lv_obj_add_event_cb(tabs, tab_cb, LV_EVENT_VALUE_CHANGED, this);

		lv_obj_add_event_cb(ui_SystemMenuUpdateFWBut, updatebut_cb, LV_EVENT_CLICKED, this);
		confirm_popup.init(ui_SystemMenu, group);
	}

	void prepare_focus() final {
		lv_group_focus_obj(tabs);
		lv_group_set_editing(group, true);
	}

	void update() final {
		if (metaparams.meta_buttons[0].is_just_released()) {
			if (confirm_popup.is_visible()) {
				confirm_popup.hide();
			} else {
				page_list.request_last_page();
			}
		}
	}

	void blur() final {
		;
	}

private:
	void update_firmware() {
		printf("Update firmware would begin here...\n");
	}

	static void tab_cb(lv_event_t *event) {
		auto page = static_cast<SystemMenuPage *>(event->user_data);
		if (!page)
			return;

		uint32_t id = lv_btnmatrix_get_selected_btn(page->tabs);
		pr_dbg("Clicked Tab %d\n", id);

		if (id == 0) {
			lv_group_remove_obj(ui_SystemMenuUpdateFWBut);
		}
		if (id == 1) {
			lv_group_add_obj(page->group, ui_SystemMenuUpdateFWBut);
			lv_group_focus_obj(ui_SystemMenuUpdateFWBut);
			lv_group_set_editing(page->group, false);
		}
	}

	static void updatebut_cb(lv_event_t *event) {
		auto page = static_cast<SystemMenuPage *>(event->user_data);
		if (!page)
			return;

		page->confirm_popup.show(
			[page](bool ok) {
				if (!ok)
					return;
				page->update_firmware();
			},
			"Update");
	}

	ConfirmPopup confirm_popup;

	// lv_obj_t *confirmbox = nullptr;
	lv_obj_t *tabs = nullptr;
	// lv_group_t *confirm_group;

	// const char *btns[3] = {"Update", "Cancel", ""};
};

} // namespace MetaModule
