#pragma once
#include "gui/elements/module_drawer.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/base.hh"
#include "gui/pages/page_list.hh"
#include "gui/slsexport/meta5/ui.h"
#include "src/core/lv_obj_pos.h"
#include "src/misc/lv_timer.h"

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
		lv_obj_set_width(ui_ModuleListRollerPanel, 160);
	}

	void populate_slugs() {
		//TODO: only repopulate if plugins changed

		auto all_slugs = ModuleFactory::getAllSlugs();

		// TODO: sort by brand name
		std::sort(all_slugs.begin(), all_slugs.end(), [](auto a, auto b) {
			return std::string_view{a} < std::string_view{b};
		});

		std::string slugs_str;
		slugs_str.reserve(all_slugs.size() * sizeof(ModuleTypeSlug));
		for (auto slug : all_slugs) {
			if (!slug.is_equal("HubMedium")) {
				slugs_str += std::string_view{slug};
				slugs_str += "\n";
			}
		}
		slugs_str.pop_back();
		lv_roller_set_options(ui_ModuleListRoller, slugs_str.c_str(), LV_ROLLER_MODE_NORMAL);
	}

	void prepare_focus() final {
		populate_slugs();
		drawn_module_idx = -1; //force redraw
		draw_module();
		draw_timer = lv_timer_create(draw_module_cb, 100, this);

		show_roller();
		lv_group_focus_obj(ui_ModuleListRoller);
		lv_group_set_editing(group, true);
		lv_group_set_wrap(group, false);
	}

	void update() final {
		if (metaparams.back_button.is_just_released()) {
			if (roller_shown) {
				gui_state.force_redraw_patch = true;
				load_prev_page();
			} else {
				show_roller();
				lv_group_set_editing(group, true);
			}
		}
	}

	bool is_roller_shown() const {
		return roller_shown;
	}

	void show_roller() {
		roller_shown = true;
		lv_obj_set_width(ui_ModuleListRollerPanel, 160);
	}

	void hide_roller() {
		roller_shown = false;
		lv_obj_set_width(ui_ModuleListRollerPanel, 2);
		lv_group_set_editing(group, true);
	}

	void blur() final {
		lv_timer_del(draw_timer);
	}

private:
	static void add_button_cb(lv_event_t *event) {
		auto page = static_cast<ModuleListPage *>(event->user_data);
		if (!page)
			return;

		if (page->is_roller_shown()) {
			page->hide_roller();
		} else {
			ModuleTypeSlug slug;
			lv_roller_get_selected_str(event->target, slug._data, slug.capacity);
			page->patch_mod_queue.put(AddModule{slug});
			page->patch_storage.get_view_patch()->module_slugs.push_back(slug);
			page->page_list.increment_patch_revision();
			page->load_page(PageId::PatchView, page->args);
			page->notify_queue.put({"Adding module " + std::string{slug}});
		}
	}

	static void scroll_cb(lv_event_t *event) {
		auto page = static_cast<ModuleListPage *>(event->user_data);
		if (!page)
			return;

		lv_timer_reset(page->draw_timer);
	}

	static void draw_module_cb(lv_timer_t *timer) {
		auto page = static_cast<ModuleListPage *>(timer->user_data);
		if (!page)
			return;
		page->draw_module();
	}

	void draw_module() {
		ModuleTypeSlug slug;
		auto cur_idx = lv_roller_get_selected(ui_ModuleListRoller);
		if (cur_idx != drawn_module_idx) {
			drawn_module_idx = cur_idx;
			lv_roller_get_selected_str(ui_ModuleListRoller, slug._data, slug.capacity);
			draw_module(slug);
		}
	}

	void draw_module(ModuleTypeSlug slug) {
		ModuleDrawer drawer{ui_ModuleListImage, 240};
		auto module_canvas = drawer.draw_faceplate(slug, page_pixel_buffer);
		if (module_canvas) {
			lv_obj_refr_size(module_canvas);
			auto width_px = lv_obj_get_width(module_canvas);
			lv_obj_set_width(ui_ModuleListImage, width_px);
			lv_obj_refr_size(ui_ModuleListImage);
			drawer.draw_elements(slug, module_canvas);
		} else
			notify_queue.put(Notification{"Could not load faceplate image", Notification::Priority::Error});
	}

	bool roller_shown = true;
	lv_timer_t *draw_timer{};
	unsigned drawn_module_idx = -1;
};

} // namespace MetaModule
