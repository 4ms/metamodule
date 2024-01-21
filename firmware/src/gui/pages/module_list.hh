#pragma once
#include "gui/elements/module_drawer.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/base.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/meta5/ui.h"

namespace MetaModule
{

struct ModuleListPage : PageBase {
	ModuleListPage(PatchContext info)
		: PageBase{info, PageId::ModuleList}
		, ui_ModuleListPage(lv_obj_create(nullptr))
		, ui_ModuleListImage(lv_obj_create(ui_ModuleListPage))
		, ui_ModuleListRoller(lv_roller_create(ui_ModuleListPage)) {

		lv_obj_clear_flag(ui_ModuleListPage, LV_OBJ_FLAG_SCROLLABLE); /// Flags
		lv_obj_set_style_radius(ui_ModuleListPage, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_bg_color(ui_ModuleListPage, lv_color_hex(0x111111), LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_bg_opa(ui_ModuleListPage, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_left(ui_ModuleListPage, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_right(ui_ModuleListPage, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_top(ui_ModuleListPage, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_bottom(ui_ModuleListPage, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_border_color(ui_ModuleListPage, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_border_opa(ui_ModuleListPage, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_border_width(ui_ModuleListPage, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

		lv_obj_set_style_bg_color(ui_ModuleListPage, lv_color_hex(0x000000), LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
		lv_obj_set_style_bg_opa(ui_ModuleListPage, 255, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_left(ui_ModuleListPage, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_right(ui_ModuleListPage, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_top(ui_ModuleListPage, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_bottom(ui_ModuleListPage, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_row(ui_ModuleListPage, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_column(ui_ModuleListPage, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

		lv_obj_set_width(ui_ModuleListImage, 180);
		lv_obj_set_height(ui_ModuleListImage, 240);
		lv_obj_set_align(ui_ModuleListImage, LV_ALIGN_LEFT_MID);
		lv_obj_clear_flag(ui_ModuleListImage,
						  LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
							  LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
							  LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
		lv_obj_set_style_radius(ui_ModuleListImage, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_bg_color(ui_ModuleListImage, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_bg_opa(ui_ModuleListImage, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_border_color(ui_ModuleListImage, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_border_opa(ui_ModuleListImage, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_border_width(ui_ModuleListImage, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_left(ui_ModuleListImage, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_right(ui_ModuleListImage, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_top(ui_ModuleListImage, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_bottom(ui_ModuleListImage, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_row(ui_ModuleListImage, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_column(ui_ModuleListImage, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_radius(ui_ModuleListImage, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
		lv_obj_set_style_bg_color(ui_ModuleListImage, lv_color_hex(0x000000), LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
		lv_obj_set_style_bg_opa(ui_ModuleListImage, 255, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

		lv_roller_set_options(ui_ModuleListRoller, "Item\nItem2", LV_ROLLER_MODE_NORMAL);
		lv_obj_set_height(ui_ModuleListRoller, 240);
		lv_obj_set_width(ui_ModuleListRoller, 320 - 180);
		lv_obj_set_align(ui_ModuleListRoller, LV_ALIGN_BOTTOM_RIGHT);
		lv_obj_clear_flag(ui_ModuleListRoller,
						  LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
							  LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE); /// Flags
		lv_obj_set_style_text_color(ui_ModuleListRoller, lv_color_hex(0x999999), LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_opa(ui_ModuleListRoller, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_letter_space(ui_ModuleListRoller, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_line_space(ui_ModuleListRoller, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_align(ui_ModuleListRoller, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_font(
			ui_ModuleListRoller, &ui_font_MuseoSansRounded70016, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_radius(ui_ModuleListRoller, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_bg_color(ui_ModuleListRoller, lv_color_hex(0x333333), LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_bg_opa(ui_ModuleListRoller, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_border_width(ui_ModuleListRoller, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_outline_color(ui_ModuleListRoller, lv_color_hex(0x777777), LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_outline_opa(ui_ModuleListRoller, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_outline_width(ui_ModuleListRoller, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_outline_pad(ui_ModuleListRoller, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_color(ui_ModuleListRoller, lv_color_hex(0xFFFFFF), LV_PART_SELECTED | LV_STATE_DEFAULT);
		lv_obj_set_style_text_opa(ui_ModuleListRoller, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);
		lv_obj_set_style_text_letter_space(ui_ModuleListRoller, 0, LV_PART_SELECTED | LV_STATE_DEFAULT);
		lv_obj_set_style_text_line_space(ui_ModuleListRoller, 6, LV_PART_SELECTED | LV_STATE_DEFAULT);
		lv_obj_set_style_text_align(ui_ModuleListRoller, LV_TEXT_ALIGN_LEFT, LV_PART_SELECTED | LV_STATE_DEFAULT);
		lv_obj_set_style_text_font(
			ui_ModuleListRoller, &ui_font_MuseoSansRounded70016, LV_PART_SELECTED | LV_STATE_DEFAULT);
		lv_obj_set_style_radius(ui_ModuleListRoller, 0, LV_PART_SELECTED | LV_STATE_DEFAULT);
		lv_obj_set_style_bg_color(ui_ModuleListRoller, lv_color_hex(0xFD8B18), LV_PART_SELECTED | LV_STATE_DEFAULT);
		lv_obj_set_style_bg_opa(ui_ModuleListRoller, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);
		lv_obj_set_style_border_color(ui_ModuleListRoller, lv_color_hex(0x000000), LV_PART_SELECTED | LV_STATE_DEFAULT);
		lv_obj_set_style_border_opa(ui_ModuleListRoller, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);

		init_bg(ui_ModuleListPage);

		lv_group_add_obj(group, ui_ModuleListRoller);
		lv_obj_add_event_cb(ui_ModuleListRoller, add_button_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(ui_ModuleListRoller, scroll_cb, LV_EVENT_KEY, this);
		lv_obj_remove_style(ui_ModuleListRoller, nullptr, LV_STATE_EDITED);
		lv_obj_remove_style(ui_ModuleListRoller, nullptr, LV_STATE_FOCUS_KEY);

		populate_slugs();

		ModuleTypeSlug slug;
		lv_roller_get_selected_str(ui_ModuleListRoller, slug._data, slug.capacity);
		draw_module(slug);
	}

	void populate_slugs() {

		auto all_slugs = ModuleFactory::getAllSlugs();
		std::ranges::sort(all_slugs, [](auto a, auto b) { return std::string_view{a} < std::string_view{b}; });
		std::string slugs_str;
		slugs_str.reserve(all_slugs.size() * sizeof(ModuleTypeSlug));
		for (auto slug : all_slugs) {
			slugs_str += std::string_view{slug};
			slugs_str += "\n";
		}
		slugs_str.pop_back();
		lv_roller_set_options(ui_ModuleListRoller, slugs_str.c_str(), LV_ROLLER_MODE_NORMAL);

	}

	void prepare_focus() final {
		lv_group_focus_obj(ui_ModuleListRoller);
		lv_group_set_editing(group, true);
		lv_group_set_wrap(group, false);
	}

	void update() final {
		if (metaparams.meta_buttons[0].is_just_released()) {
			load_prev_page();
		}
	}

	void blur() final {
	}

private:
	static void add_button_cb(lv_event_t *event) {
		auto page = static_cast<ModuleListPage *>(event->user_data);
		if (!page)
			return;

		ModuleTypeSlug slug;
		lv_roller_get_selected_str(event->target, slug._data, slug.capacity);
		page->patch_mod_queue.put(AddModule{slug});
		page->patch_storage.get_view_patch().module_slugs.push_back(slug);
		page->page_list.increment_patch_revision();
		page->load_page(PageId::PatchView, page->args);
		page->notify_queue.put({"Adding module " + std::string{slug}});
	}

	static void scroll_cb(lv_event_t *event) {
		auto page = static_cast<ModuleListPage *>(event->user_data);
		if (!page)
			return;

		ModuleTypeSlug slug;
		lv_roller_get_selected_str(event->target, slug._data, slug.capacity);
		page->draw_module(slug);
	}

	void draw_module(ModuleTypeSlug slug) {
		ModuleDrawer drawer{ui_ModuleListImage, 240};
		auto module_canvas = drawer.draw_faceplate(slug, buffer);
		lv_obj_refr_size(module_canvas);
		auto width_px = lv_obj_get_width(module_canvas);
		lv_obj_set_width(ui_ModuleListImage, width_px);
		lv_obj_refr_size(ui_ModuleListImage);
		drawer.draw_elements(slug, module_canvas);
	}

	lv_obj_t *ui_ModuleListPage;
	lv_obj_t *ui_ModuleListImage;
	lv_obj_t *ui_ModuleListRoller;
	lv_color_t buffer[LV_CANVAS_BUF_SIZE_TRUE_COLOR_ALPHA(320, 240)]{};
};

} // namespace MetaModule
