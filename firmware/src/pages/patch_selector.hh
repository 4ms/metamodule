#pragma once
#include "pages/base.hh"
#include "pages/lvgl_mem_helper.hh"
#include "pages/lvgl_string_helper.hh"
#include "pages/page_list.hh"
#include "pages/styles.hh"
#include "printf.h"

namespace MetaModule
{

struct PatchSelectorPage : PageBase {
	PatchSelectorPage(PatchInfo info)
		: PageBase{info}
		, base(lv_obj_create(nullptr))
	// , patch_view_page{info}
	{
		PageList::register_page(this, PageId::PatchSel);

		init_bg(base);

		roller = lv_roller_create(base);
		lv_group_add_obj(group, roller);
		lv_obj_add_event_cb(roller, patchlist_event_cb, LV_EVENT_VALUE_CHANGED, this);

		lv_obj_add_style(roller, &Gui::roller_style, LV_PART_MAIN);
		lv_obj_add_style(roller, &Gui::plain_border_style, (int)LV_PART_MAIN | LV_STATE_FOCUS_KEY | LV_STATE_EDITED);
		lv_obj_add_style(roller, &Gui::roller_sel_style, LV_PART_SELECTED);

		lv_obj_set_pos(roller, 0, 30);
		lv_obj_set_size(roller, 320, 210);

		header_text = lv_label_create(base);
		lv_label_set_text_static(header_text, "Select a Patch:");
		lv_obj_add_style(header_text, &Gui::header_style, LV_PART_MAIN);
		lv_obj_set_align(base, LV_ALIGN_TOP_MID);
		lv_obj_set_pos(header_text, 0, 0);
		lv_obj_set_width(header_text, 320);

		// wait_cont = lv_obj_create(base);
		// lv_obj_set_align(wait_cont, LV_ALIGN_CENTER);
		// lv_obj_add_style(wait_cont, &style_wait_cont, LV_PART_MAIN);
		// lv_cont_set_layout(wait_cont, LV_LAYOUT_CENTER);
		// lv_cont_set_fit(wait_cont, LV_FIT_TIGHT);

		// wait_text = lv_label_create(wait_cont);
		// lv_obj_add_style(wait_text, &style_popup_patchname, LV_PART_MAIN);
		// lv_obj_set_align(wait_text, LV_ALIGN_CENTER);
		// lv_label_set_text(wait_text, "Refreshing Patches...");

		// lv_obj_add_flag(wait_cont, LV_OBJ_FLAG_HIDDEN);

		// wait_group = lv_group_create();
	}

	void init() override {
		LVGLMemory::print_mem_usage("PatchSel::init in");

		refresh_patchlist();

		LVGLMemory::print_mem_usage("PatchSel::init out");
	}

	void refresh_patchlist() {
		std::string patchnames;
		for (unsigned i = 0; i < patch_storage.patch_list.num_patches(); i++) {
			patchnames += patch_storage.patch_list.get_patch_name(i).data();
			patchnames += '\n';
		}
		// remove trailing \n
		if (patchnames.length() > 0)
			patchnames.pop_back();

		lv_roller_set_options(roller, patchnames.c_str(), LV_ROLLER_MODE_NORMAL);
		// lv_roller_set_visible_row_count(roller, 9);
		// unsigned default_sel = patchnames.size() > 9 ? 5U : 0;
		unsigned default_sel = patchnames.size() > 10 ? 5 : patchnames.size() / 2;
		lv_roller_set_selected(roller, default_sel, LV_ANIM_OFF);
		printf_("Patch Selector page refreshed %d patches, preselecting %d\n",
				patch_storage.patch_list.num_patches(),
				lv_roller_get_selected(roller));
	}

	void update() override {
		if (should_show_patchview) {
			should_show_patchview = false;
			printf_("Requesting new page: PatchView, patch id %d\n", selected_patch);
			patch_storage.load_view_patch(selected_patch);
			PageList::set_selected_patch_id(selected_patch);
			PageList::request_new_page(PageId::PatchView);
			blur();
		}

		if (!patch_storage.patch_list.is_ready()) {
			if (patchlist_was_ready) {
				// lv_indev_set_group(lv_indev_get_next(nullptr), wait_group);
				// lv_obj_clear_flag(wait_cont, LV_OBJ_FLAG_HIDDEN);
				patchlist_was_ready = false;
			}
			return;
		}

		if (!patchlist_was_ready) {
			// lv_obj_add_flag(wait_cont, LV_OBJ_FLAG_HIDDEN);
			lv_indev_set_group(lv_indev_get_next(nullptr), group);
			lv_group_set_editing(group, true);
			patchlist_was_ready = true;
		}

		if (patch_storage.patch_list.is_modified()) {
			refresh_patchlist();
		}
	}

	void blur() override {
		// lv_obj_add_flag(wait_cont, LV_OBJ_FLAG_HIDDEN);
	}

	static void patchlist_event_cb(lv_event_t *event) {
		auto _instance = static_cast<PatchSelectorPage *>(event->user_data);
		_instance->selected_patch = lv_roller_get_selected(_instance->roller);
		_instance->should_show_patchview = true;
	}

private:
	uint32_t selected_patch = 0;
	bool patchlist_was_ready = true;
	bool should_show_patchview = false;

	lv_obj_t *roller;
	lv_obj_t *header_text;
	lv_obj_t *base;

	// PatchViewPage patch_view_page;
};

} // namespace MetaModule
