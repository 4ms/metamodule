#pragma once
#include "pages/base.hh"
#include "pages/lvgl_mem_helper.hh"
#include "pages/lvgl_string_helper.hh"
#include "pages/page_list.hh"
#include "pages/patch_view.hh"
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
		lv_obj_add_style(roller, &Gui::plain_border_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY | LV_STATE_EDITED);
		lv_obj_add_style(roller, &Gui::roller_sel_style, LV_PART_SELECTED);

		lv_obj_set_pos(roller, 0, 30);
		lv_obj_set_size(roller, 320, 210);

		header_text = lv_label_create(base);
		lv_label_set_text_static(header_text, "Select a Patch:");
		lv_obj_add_style(header_text, &Gui::header_style, LV_PART_MAIN);
		lv_obj_set_align(base, LV_ALIGN_TOP_MID);
		lv_obj_set_pos(header_text, 0, 0);
		lv_obj_set_width(header_text, 320);
	}

	void init() override {
		LVGLMemory::print_mem_usage("PatchSel::init in");

		refresh_patchlist();

		LVGLMemory::print_mem_usage("PatchSel::init out");
	}

	void refresh_patchlist() {
		printf("refresh_patchlist\n");
		std::string patchnames;
		for (unsigned i = 0; i < patch_list.num_patches(); i++) {
			patchnames += patch_list.get_patch_name(i).data();
			patchnames += '\n';
		}
		if (patchnames.length() > 0)
			patchnames.pop_back();

		lv_roller_set_options(roller, patchnames.c_str(), LV_ROLLER_MODE_NORMAL);
		lv_roller_set_visible_row_count(roller, 9);
		lv_roller_set_selected(roller, 1, LV_ANIM_OFF);
		printf("Preselecting %d from %p\n", lv_roller_get_selected(roller), roller);
	}

	void update() override {
		if (should_show_patchview) {
			should_show_patchview = false;
			printf("Requesting new page: PatchView, patch id %d\n", selected_patch);
			PageList::set_selected_patch_id(selected_patch);
			PageList::request_new_page(PageId::PatchView);
			blur();
		}

		// if (!patch_list.is_ready()) {
		// 	if (patchlist_ready) {
		// 		lv_indev_set_group(lv_indev_get_next(nullptr), wait_group);
		// 		// lv_obj_clear_flag(wait_cont, LV_OBJ_FLAG_HIDDEN);
		// 		patchlist_ready = false;
		// 	}
		// 	return;
		// }

		// if (!patchlist_ready) {
		// 	// lv_obj_add_flag(wait_cont, LV_OBJ_FLAG_HIDDEN);
		// 	// lv_obj_add_flag(popup_cont, LV_OBJ_FLAG_HIDDEN);
		// 	lv_indev_set_group(lv_indev_get_next(nullptr), group);
		// 	lv_group_set_editing(group, true);
		// 	patchlist_ready = true;
		// }

		// handle_changing_patch();
		// if (mbox.patchlist_updated) {
		// 	refresh_patchlist();
		// 	mbox.patchlist_updated = false;
		// }
	}

	// void blur() override {
	// 	// hide_popup();
	// }

	// static void popup_play_event_cb(lv_event_t *event) {
	// 	auto _instance = static_cast<PatchSelectorPage *>(event->user_data);

	// 	printf("Clicked Play: playing patch# %d\n\r", _instance->selected_patch);
	// 	_instance->start_changing_patch(_instance->selected_patch);
	// 	_instance->hide_popup();
	// }

	// static void popup_back_event_cb(lv_event_t *event) {
	// 	auto _instance = static_cast<PatchSelectorPage *>(event->user_data);
	// 	printf("Clicked Back\n\r");
	// 	_instance->hide_popup();
	// }

	// static void popup_explore_event_cb(lv_event_t *event) {
	// 	// auto _instance = static_cast<PatchSelectorPage *>(event->user_data);
	// 	printf("Clicked Explore\n\r");
	// }

	// static void patch_selector_event_cb(lv_obj_t *obj, lv_event_t event) {
	// 	switch (event) {
	// 		case LV_EVENT_VALUE_CHANGED: {
	// 			if (obj == _instance->patch_selector_patchlist) {
	// 				selected_patch = lv_dropdown_get_selected(obj);
	// 				lv_label_set_text(_instance->popup_patchname, _instance->patch_list.get_patch_name(selected_patch));
	// 				lv_label_set_text(_instance->popup_desc, "TODO: Patch descriptions...");
	// 				lv_obj_realign(_instance->popup_patchname);
	// 				lv_obj_realign(_instance->popup_desc);
	// 				_instance->show_popup();
	// 				printf("Event obj is patch_selector_patchlist\n\r");

	// 				// } else if (obj == _instance->popup_playbut) {
	// 				// 	printf("C Play\n\r");
	// 				// } else if (obj == _instance->popup_explorebut) {
	// 				// 	printf("Clicked Explore\n\r");
	// 				// } else if (obj == _instance->popup_backbut) {
	// 				// 	printf("Clicked Back\n\r");
	// 			} else
	// 				printf("Event obj not known\n\r");

	// 		} break;

	// 		case LV_EVENT_CLICKED: {
	// 			if (obj == _instance->popup_explorebut) {
	// 				printf("Clicked Explore\n\r");

	// 			} else if (obj == _instance->popup_playbut) {
	// 				printf("Clicked Play: playing patch# %d\n\r", selected_patch);
	// 				_instance->start_changing_patch(selected_patch);
	// 				_instance->hide_popup();

	// 			} else if (obj == _instance->popup_backbut) {
	// 				printf("Clicked Back\n\r");
	// 				_instance->hide_popup();
	// 			}
	// 		} break;

	// 		default:
	// 			// printf("Event = %s, obj.coords = {%d, %d}, {%d, %d}. obj=%p\n\r",
	// 			// 	   LVGLStrings::Events[event].data(),
	// 			// 	   obj->coords.x1,
	// 			// 	   obj->coords.y1,
	// 			// 	   obj->coords.x2,
	// 			// 	   obj->coords.y2,
	// 			// 	   obj);
	// 			break;
	// 	}
	// }

	static void patchlist_event_cb(lv_event_t *event) {
		auto _instance = static_cast<PatchSelectorPage *>(event->user_data);
		_instance->selected_patch = lv_roller_get_selected(_instance->roller);
		_instance->should_show_patchview = true;
	}

	void start_changing_patch(int32_t new_patch_index) {
		if (!mbox.loading_new_patch && (new_patch_index != (int32_t)patch_list.cur_patch_index())) {
			mbox.new_patch_index = new_patch_index;
			mbox.loading_new_patch = true;
			printf("Loading patch %s\n\r", patch_list.get_patch_name(new_patch_index).data());
		}
	}

	void handle_changing_patch() {
		if (mbox.loading_new_patch && mbox.audio_is_muted) {
			auto cur_patch_index = patch_list.cur_patch_index();
			auto orig_patch_data = patch_list.get_patch(cur_patch_index);
			patch_player.unload_patch();
			patch_list.set_cur_patch_index(mbox.new_patch_index);
			bool ok = patch_player.load_patch(patch_list.get_patch(mbox.new_patch_index));
			if (!ok) {
				mbox.append_message("Can't load patch\n\r");
				printf("Can't load patch\n\r");
				patch_player.unload_patch();
				patch_player.load_patch(orig_patch_data);
			} else
				mbox.append_message("Patch loaded\n\r");

			mbox.loading_new_patch = false;
		}
	}

private:
	uint32_t selected_patch = 0;
	// bool patchlist_ready = true;
	bool should_show_patchview = false;

	lv_obj_t *roller;
	lv_obj_t *header_text;
	lv_obj_t *base;

	// PatchViewPage patch_view_page;
};

} // namespace MetaModule
