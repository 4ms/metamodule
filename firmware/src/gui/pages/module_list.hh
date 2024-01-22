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
		: PageBase{info, PageId::ModuleList} {
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

		// TODO: sort by brand name
		// std::ranges::sort(all_slugs, [](auto a, auto b) { return std::string_view{a} < std::string_view{b}; });

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
		show_roller();
		lv_group_focus_obj(ui_ModuleListRoller);
		lv_group_set_editing(group, true);
		lv_group_set_wrap(group, false);
	}

	void update() final {
		if (metaparams.meta_buttons[0].is_just_released()) {
			if (roller_shown) {
				hide_roller();
			} else
				load_prev_page();
		}
	}

	bool is_roller_shown() const {
		return roller_shown;
	}

	void show_roller() {
		roller_shown = true;
		lv_show(ui_ModuleListRollerPanel);
	}

	void hide_roller() {
		roller_shown = false;
		lv_hide(ui_ModuleListRollerPanel);
	}

	void blur() final {
	}

private:
	static void add_button_cb(lv_event_t *event) {
		auto page = static_cast<ModuleListPage *>(event->user_data);
		if (!page)
			return;

		if (page->is_roller_shown()) {
			ModuleTypeSlug slug;
			lv_roller_get_selected_str(event->target, slug._data, slug.capacity);
			page->patch_mod_queue.put(AddModule{slug});
			page->patch_storage.get_view_patch().module_slugs.push_back(slug);
			page->page_list.increment_patch_revision();
			page->load_page(PageId::PatchView, page->args);
			page->notify_queue.put({"Adding module " + std::string{slug}});
		} else {
			page->show_roller();
			lv_group_set_editing(page->group, true);
		}
	}

	static void scroll_cb(lv_event_t *event) {
		auto page = static_cast<ModuleListPage *>(event->user_data);
		if (!page)
			return;

		ModuleTypeSlug slug;
		lv_roller_get_selected_str(event->target, slug._data, slug.capacity);
		page->draw_module(slug);
		page->show_roller();
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

	lv_color_t buffer[LV_CANVAS_BUF_SIZE_TRUE_COLOR_ALPHA(320, 240)]{};
	bool roller_shown = true;
};

} // namespace MetaModule
