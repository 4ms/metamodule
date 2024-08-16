#pragma once
#include "CoreModules/modules_helpers.hh"
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

private:
	void populate_modules() {
		//TODO: only repopulate if plugins changed

		auto all_slugs = ModuleFactory::getAllModuleDisplayNames(selected_brand_slug);
		std::sort(all_slugs.begin(), all_slugs.end(), [](auto a, auto b) {
			return std::string_view{a} < std::string_view{b};
		});

		std::string slugs_str;
		slugs_str.reserve(all_slugs.size() * (sizeof(ModuleTypeSlug) + 1));
		for (auto slug : all_slugs) {
			if (slug != "HubMedium") {
				slugs_str += slug;
				slugs_str += "\n";
			}
		}
		slugs_str.pop_back();
		lv_roller_set_options(ui_ModuleListRoller, slugs_str.c_str(), LV_ROLLER_MODE_NORMAL);
		lv_roller_set_selected(ui_ModuleListRoller, 0, LV_ANIM_OFF);
	}

	void populate_brands() {
		auto all_brands = ModuleFactory::getAllBrandDisplayNames();

		std::string roller_str = "";
		roller_str.reserve(all_brands.size() * (sizeof(ModuleTypeSlug) + 1));
		unsigned sel_idx = 0;
		for (unsigned i = 0; auto const &item : all_brands) {
			roller_str += item;
			roller_str += "\n";
			if (selected_brand == item)
				sel_idx = i;
			i++;
		}
		roller_str.pop_back();
		lv_roller_set_options(ui_ModuleListRoller, roller_str.c_str(), LV_ROLLER_MODE_NORMAL);
		lv_roller_set_selected(ui_ModuleListRoller, sel_idx, LV_ANIM_OFF);
	}

	void roller_module_list() {
		lv_label_set_text(ui_ModuleListRollerTitle, selected_brand.data());
		populate_modules();
		drawn_module_idx = -1; //force redraw
		draw_module();

		draw_timer = lv_timer_create(draw_module_cb, 100, this);

		show_roller();
		show_module();
	}

	void roller_brand_list() {
		lv_label_set_text(ui_ModuleListRollerTitle, "Brands:");
		hide_module();
		populate_brands();
		show_roller();
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

public:
	void prepare_focus() final {
		view = View::BrandRoller;
		roller_brand_list();
	}

	void update() final {
		if (gui_state.back_button.is_just_released()) {

			if (view == View::BrandRoller) {
				gui_state.force_redraw_patch = true;
				load_prev_page();

			} else if (view == View::ModuleRoller) {
				view = View::BrandRoller;
				if (draw_timer)
					lv_timer_del(draw_timer);
				draw_timer = nullptr;
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
			page->selected_brand = selected_str.c_str();
			page->selected_brand_slug = ModuleFactory::getBrandSlug(page->selected_brand);
			if (!page->selected_brand_slug.length()) {
				pr_err("Brand not found with display name %s\n", page->selected_brand.data());
			}
			page->roller_module_list();

		} else if (page->view == View::ModuleRoller) {
			page->view = View::ModuleOnly;
			page->hide_roller();

		} else {
			std::string slug = std::string{page->selected_brand_slug} + ":" + page->selected_module_slug;
			page->add_module(slug);
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

	void add_module(std::string_view slug) {
		patch_playloader.load_module(slug);
		patches.mark_view_patch_modified();
	}

	void draw_module() {
		if (view == View::ModuleOnly || view == View::ModuleRoller) {
			auto cur_idx = lv_roller_get_selected(ui_ModuleListRoller);
			if (cur_idx != drawn_module_idx) {
				drawn_module_idx = cur_idx;
				ModuleTypeSlug module_display_name;
				lv_roller_get_selected_str(
					ui_ModuleListRoller, module_display_name._data, module_display_name.capacity);
				selected_module_slug = ModuleFactory::getModuleSlug(selected_brand_slug, module_display_name);
				std::string slug = std::string{selected_brand_slug} + ":" + selected_module_slug;
				draw_module(slug.c_str());
			}
		}
	}

	void draw_module(BrandModuleSlug slug) {
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
	std::string selected_brand{"4msCompany"};
	std::string selected_brand_slug{"4msCompany"};
	std::string selected_module_slug;
};

} // namespace MetaModule
