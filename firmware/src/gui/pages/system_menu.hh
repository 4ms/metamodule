#pragma once
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/base.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/meta5/ui.h"

namespace MetaModule
{

struct SystemMenuPage : PageBase {
	SystemMenuPage(PatchInfo info)
		: PageBase{info, PageId::SystemMenu} {

		root = lv_obj_create(nullptr);
		init_bg(root);

		lv_obj_t *menu = lv_menu_create(root);
		// lv_obj_set_size(menu, lv_pct(100), lv_pct(100));
		lv_obj_set_size(menu, 320, 240);
		lv_obj_center(menu);

		lv_obj_t *info_page = lv_menu_page_create(menu, nullptr);
		lv_obj_set_style_pad_hor(info_page, lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);

		lv_obj_t *info_sep = lv_menu_separator_create(info_page);
		lv_obj_t *info_page_section = lv_menu_section_create(info_page);
		lv_obj_t *info_page_label = lv_label_create(info_page_section);
		lv_label_set_text(info_page_label, "MetaModule version 0.5.1\n");
		auto info_btn = lv_btn_create(info_page_section);

		lv_obj_t *update_page = lv_menu_page_create(menu, nullptr);
		lv_obj_set_style_pad_hor(update_page, lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);
		lv_obj_t *update_sep = lv_menu_separator_create(update_page);
		lv_obj_t *update_section = lv_menu_section_create(update_page);

		auto update_btn = lv_btn_create(update_section);
		lv_obj_t *update_page_label = lv_label_create(update_btn);
		lv_label_set_text(update_page_label, "Update Firmware\n");

		lv_menu_set_mode_root_back_btn(menu, LV_MENU_ROOT_BACK_BTN_ENABLED);

		auto root_page = lv_menu_page_create(menu, "Settings");
		lv_obj_set_style_pad_hor(root_page, lv_obj_get_style_pad_left(lv_menu_get_main_header(menu), 0), 0);
		auto root_section = lv_menu_section_create(root_page);

		auto info_cont = lv_menu_cont_create(root_section);
		auto info_label = lv_label_create(info_cont);
		lv_label_set_text(info_label, "Info");
		lv_obj_set_flex_grow(info_label, 1);
		lv_menu_set_load_page_event(menu, info_cont, info_page);

		auto update_cont = lv_menu_cont_create(root_section);
		auto update_label = lv_label_create(update_cont);
		lv_label_set_text(update_label, "Update");
		lv_obj_set_flex_grow(update_label, 1);

		lv_menu_set_load_page_event(menu, update_cont, update_page);

		lv_menu_set_sidebar_page(menu, root_page);

		lv_event_send(
			lv_obj_get_child(lv_obj_get_child(lv_menu_get_cur_sidebar_page(menu), 0), 0), LV_EVENT_CLICKED, nullptr);

		lv_group_remove_all_objs(group);

		lv_group_add_obj(group, info_cont);
		lv_group_add_obj(group, update_cont);
		lv_group_add_obj(group, info_btn);
		lv_group_add_obj(group, update_btn);
		// lv_group_focus_obj(ui_MenuPanelPatches);
		// lv_obj_add_event_cb(ui_MenuPanelPatches, patchsel_cb, LV_EVENT_CLICKED, this);
	}

	void prepare_focus() final {
		lv_group_set_editing(group, false);
		// lv_group_focus_obj(ui_MenuPanelPatches);
	}

	void update() final {
	}

	void blur() final {
		;
	}

private:
	lv_obj_t *root;
};

} // namespace MetaModule
