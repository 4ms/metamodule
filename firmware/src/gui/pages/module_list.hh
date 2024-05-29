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
		lv_obj_add_event_cb(ui_ModuleListRoller, click_roller_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(ui_ModuleListRoller, scroll_cb, LV_EVENT_KEY, this);
		lv_obj_remove_style(ui_ModuleListRoller, nullptr, LV_STATE_EDITED);
		lv_obj_remove_style(ui_ModuleListRoller, nullptr, LV_STATE_FOCUS_KEY);
		lv_obj_set_width(ui_ModuleListRollerPanel, 160);
	}

	void populate_slugs() {
		//TODO: only repopulate if plugins changed

		auto all_slugs = ModuleFactory::getAllSlugs(selected_brand);
		std::sort(all_slugs.begin(), all_slugs.end(), [](auto a, auto b) {
			return std::string_view{a} < std::string_view{b};
		});

		std::string slugs_str;
		slugs_str.reserve(all_slugs.size() * (sizeof(ModuleTypeSlug) + 1));
		for (auto slug : all_slugs) {
			if (!slug.is_equal("HubMedium")) {
				slugs_str += std::string_view{slug};
				slugs_str += "\n";
			}
		}
		slugs_str.pop_back();
		lv_roller_set_options(ui_ModuleListRoller, slugs_str.c_str(), LV_ROLLER_MODE_NORMAL);
		lv_roller_set_selected(ui_ModuleListRoller, 0, LV_ANIM_OFF);
	}

	void populate_brands() {
		auto all_brands = ModuleFactory::getAllBrands();

		std::string roller_str;
		roller_str.reserve(all_brands.size() * (sizeof(ModuleTypeSlug) + 1));
		for (auto item : all_brands) {
			roller_str += std::string_view{item};
			roller_str += "\n";
		}
		roller_str.pop_back();
		lv_roller_set_options(ui_ModuleListRoller, roller_str.c_str(), LV_ROLLER_MODE_NORMAL);
	}

	void prepare_focus() final {
		view = View::BrandRoller;
		if (draw_timer)
			lv_timer_del(draw_timer);
		draw_timer = nullptr;
		roller_brand_list();
	}

	void roller_module_list() {
		lv_label_set_text(ui_ModuleListRollerTitle, selected_brand);
		populate_slugs();
		drawn_module_idx = -1; //force redraw
		draw_module();
		draw_timer = lv_timer_create(draw_module_cb, 100, this);

		show_roller();
	}

	void roller_brand_list() {
		lv_label_set_text(ui_ModuleListRollerTitle, "Brands:");
		hide_module();
		populate_brands();
		show_roller();
	}

	void update() final {
		if (metaparams.back_button.is_just_released()) {

			if (view == View::BrandRoller) {
				gui_state.force_redraw_patch = true;
				load_prev_page();

			} else if (view == View::ModuleRoller) {
				view = View::BrandRoller;
				if (draw_timer)
					lv_timer_del(draw_timer);
				roller_brand_list();

			} else if (view == View::ModuleOnly) {
				view = View::ModuleRoller;
				show_roller();
			}
		}

		if (do_redraw) {
			do_redraw = false;
			draw_module();
		}
	}

	void show_roller() {
		lv_obj_set_width(ui_ModuleListRollerPanel, 160);
		lv_group_focus_obj(ui_ModuleListRoller);
		lv_group_set_editing(group, true);
		lv_group_set_wrap(group, false);
	}

	void hide_roller() {
		lv_obj_set_width(ui_ModuleListRollerPanel, 2);
		lv_group_set_editing(group, true);
	}

	void show_module() {
		lv_show(ui_ModuleListImage);
	}

	void hide_module() {
		lv_hide(ui_ModuleListImage);
	}

	void blur() final {
		if (draw_timer)
			lv_timer_del(draw_timer);
		draw_timer = nullptr;
	}

private:
	static void click_roller_cb(lv_event_t *event) {
		auto page = static_cast<ModuleListPage *>(event->user_data);
		if (!page)
			return;

		ModuleTypeSlug selected_str;
		lv_roller_get_selected_str(event->target, selected_str._data, selected_str.capacity);

		if (page->view == View::BrandRoller) {
			page->view = View::ModuleRoller;
			page->selected_brand = selected_str;
			page->roller_module_list();
			page->show_module();

		} else if (page->view == View::ModuleRoller) {
			page->view = View::ModuleOnly;
			page->hide_roller();

		} else {
			std::string slug = std::string{page->selected_brand} + ":" + std::string{selected_str};
			page->patch_mod_queue.put(AddModule{slug.c_str()});
			page->patch_storage.get_view_patch()->module_slugs.push_back({slug.c_str()});
			page->page_list.increment_patch_revision();
			page->load_page(PageId::PatchView, page->args);
		}
	}

	static void scroll_cb(lv_event_t *event) {
		auto page = static_cast<ModuleListPage *>(event->user_data);
		if (!page)
			return;

		if (page->view == View::ModuleOnly || page->view == View::ModuleRoller) {
			lv_timer_reset(page->draw_timer);
		}
	}

	static void draw_module_cb(lv_timer_t *timer) {
		auto page = static_cast<ModuleListPage *>(timer->user_data);
		if (!page)
			return;

		if (page->view == View::ModuleOnly || page->view == View::ModuleRoller) {
			page->do_redraw = true;
		}
	}

	void draw_module() {
		auto cur_idx = lv_roller_get_selected(ui_ModuleListRoller);
		if (cur_idx != drawn_module_idx) {
			drawn_module_idx = cur_idx;
			ModuleTypeSlug module_slug;
			lv_roller_get_selected_str(ui_ModuleListRoller, module_slug._data, module_slug.capacity);
			std::string slug = std::string{selected_brand} + ":" + std::string{module_slug};
			draw_module(slug.c_str());
		}
	}

	void draw_module(ModuleTypeSlug slug) {
		clear_module_canvas();

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

	void clear_module_canvas() {
		lv_foreach_child(ui_ModuleListImage, [](auto *obj, int i) {
			lv_obj_del_async(obj);
			return true;
		});
	}

	enum class View { BrandRoller, ModuleRoller, ModuleOnly } view{View::BrandRoller};
	lv_timer_t *draw_timer{};
	unsigned drawn_module_idx = -1;
	bool do_redraw = false;
	ModuleTypeSlug selected_brand{"4ms"};
};

} // namespace MetaModule
