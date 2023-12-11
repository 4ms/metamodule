#pragma once
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/base.hh"
#include "gui/pages/confirm_popup.hh"
#include "gui/pages/firmware_update.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/meta5/ui.h"
#include "gui/styles.hh"
#include "util/poll_event.hh"

namespace MetaModule
{

struct SystemMenuPage : PageBase {
	SystemMenuPage(PatchInfo info)
		: PageBase{info, PageId::SystemMenu}
		, fwupdate_page{patch_storage, patch_playloader}
		, tabs(lv_tabview_get_tab_btns(ui_SystemMenuTabView)) {

		init_bg(ui_SystemMenu);

		lv_group_remove_all_objs(group);
		lv_group_add_obj(group, tabs);
		lv_group_set_editing(group, true);

		lv_obj_add_event_cb(tabs, tab_cb, LV_EVENT_VALUE_CHANGED, this);
	}

	void prepare_focus() final {
		lv_hide(ui_FWUpdateSpinner);
		lv_group_focus_obj(tabs);
		lv_group_set_editing(group, true);

		fwupdate_page.prepare_focus(group);
	}

	void update() final {
		bool pressed_back = metaparams.meta_buttons[0].is_just_released();

		switch (active_tab) {
			case Tabs::Status: {
				if (pressed_back)
					page_list.request_last_page();
				//TODO: handle Status page
			} break;

			case Tabs::Update: {
				if (pressed_back) {
					if (fwupdate_page.try_go_back())
						page_list.request_last_page();
				}
				fwupdate_page.update();
			} break;

			case Tabs::Test: {
				if (pressed_back)
					page_list.request_last_page();
				//TODO: handle HW Test page
			} break;
		}
	}

	void blur() final {
	}

private:
	static void tab_cb(lv_event_t *event) {
		auto page = static_cast<SystemMenuPage *>(event->user_data);
		if (!page)
			return;

		switch (lv_btnmatrix_get_selected_btn(page->tabs)) {
			case Tabs::Status: {
				page->active_tab = Tabs::Status;
				lv_group_remove_obj(ui_SystemMenuUpdateFWBut);
				break;
			}

			case Tabs::Update: {
				page->active_tab = Tabs::Update;
				lv_hide(ui_FWUpdateSpinner);
				break;
			}

			case Tabs::Test: {
				page->active_tab = Tabs::Test;
				lv_group_remove_obj(ui_SystemMenuUpdateFWBut);
				break;
			}
		}
	}

	FirmwareUpdateTab fwupdate_page;

	enum Tabs { Status = 0, Update = 1, Test = 2 };
	Tabs active_tab = Status;
	lv_obj_t *tabs = nullptr;
};

} // namespace MetaModule
