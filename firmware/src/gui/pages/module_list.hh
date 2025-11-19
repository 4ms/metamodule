#pragma once
#include "gui/elements/module_drawer.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/helpers/roller_hover_text.hh"
#include "gui/pages/base.hh"
#include "gui/pages/page_list.hh"
#include "gui/pages/tags.hh"
#include "gui/slsexport/meta5/ui.h"
#include "src/core/lv_obj_pos.h"
#include "src/misc/lv_timer.h"

namespace MetaModule
{

struct ModuleListPage : PageBase {
	ModuleListPage(PatchContext info)
		: PageBase{info, PageId::ModuleList}
		, roller_hover{ui_ModuleListRollerPanel, ui_ModuleListRoller} {
		init_bg(ui_ModuleListPage);

		lv_group_add_obj(group, ui_ModuleListRoller);
		lv_obj_add_event_cb(ui_ModuleListRoller, click_roller_cb, LV_EVENT_VALUE_CHANGED, this);
		lv_obj_add_event_cb(ui_ModuleListRoller, scroll_cb, LV_EVENT_KEY, this);
		lv_obj_remove_style(ui_ModuleListRoller, nullptr, LV_STATE_EDITED);
		lv_obj_remove_style(ui_ModuleListRoller, nullptr, LV_STATE_FOCUS_KEY);
		lv_obj_set_width(ui_ModuleListRollerPanel, 164);

		auto hov = roller_hover.get_cont();
		lv_obj_set_align(hov, LV_ALIGN_LEFT_MID);
		lv_obj_set_x(hov, -2);
		lv_obj_set_y(hov, 13);
		lv_obj_set_width(hov, 172);

		lv_label_set_recolor(lv_obj_get_child(ui_ModuleListRoller, 0), true);
	}

private:
	struct ListEntry {
		std::string_view brand_slug;
		std::string_view module_slug;
		std::string_view module_display_name;
	};
	std::vector<ListEntry> entries;

	void populate_modules() {
		auto all_brand_slugs = ModuleFactory::getBrandSlugsWithDisplayName(sel_brand_display_name);

		entries.clear();

		// Populate brand/module list
		for (auto const &brand_slug : all_brand_slugs) {
			auto all_slugs = ModuleFactory::getAllModuleSlugs(brand_slug);
			for (auto const &module_slug : all_slugs) {
				auto combined_slug = std::string(brand_slug) + ":" + std::string(module_slug);
				auto display_name = ModuleFactory::getModuleDisplayName(combined_slug);

				entries.push_back(
					{.brand_slug = brand_slug, .module_slug = module_slug, .module_display_name = display_name});
			}
		}

		// Remove 4ms Hub
		std::erase_if(entries, [](auto const &entry) {
			return (entry.brand_slug == "4msCompany" &&
					(entry.module_slug == "HubMedium" || entry.module_slug == "Panel"));
		});

		// Sort
		std::ranges::sort(entries,
						  [](auto a, auto b) { return less_ci(a.module_display_name, b.module_display_name); });

		// Create roller entries
		std::string slugs_str;
		slugs_str.reserve(entries.size() * (sizeof(ModuleTypeSlug) + 1));

		for (auto entry : entries) {
			slugs_str += entry.module_display_name;
			slugs_str += "\n";
		}

		if (slugs_str.length())
			slugs_str.pop_back();

		lv_roller_set_options(ui_ModuleListRoller, slugs_str.c_str(), LV_ROLLER_MODE_NORMAL);
		lv_roller_set_selected(ui_ModuleListRoller, 0, LV_ANIM_OFF);
	}

	void populate_brands() {
		auto all_brands = ModuleFactory::getAllBrandDisplayNames();
		std::ranges::sort(all_brands, less_ci);

		std::string roller_str = "";
		roller_str += Gui::blue_text("Sort by tag " LV_SYMBOL_RIGHT);
		roller_str += "\n";
		roller_str += "________________";
		roller_str += "\n";
		roller_str += Gui::orange_text("Brands:");
		roller_str += "\n";

		roller_str.reserve(roller_str.size() + all_brands.size() * (sizeof(ModuleTypeSlug) + 1));

		unsigned sel_idx = 1; // account for the first toggle item
		for (unsigned i = 0; auto const &item : all_brands) {
			if (!item.length())
				continue;
			roller_str += item;
			roller_str += "\n";
			if (sel_brand_display_name == item)
				sel_idx = i + 3; // shift for headers
			i++;
		}
		// Remove last newline
		if (roller_str.size())
			roller_str.pop_back();
		lv_roller_set_options(ui_ModuleListRoller, roller_str.c_str(), LV_ROLLER_MODE_NORMAL);
		lv_roller_set_selected(ui_ModuleListRoller, sel_idx, LV_ANIM_OFF);
		cur_selected = sel_idx;
	}

	void populate_tags() {
		// Gather unique tags from all modules
		std::vector<std::string> all_tags;

		for (auto const &brand : ModuleFactory::getAllBrands()) {
			for (auto const &slug : ModuleFactory::getAllModuleSlugs(brand)) {
				auto tags = ModuleFactory::getModuleTags(brand, slug);
				for (auto const &tag : tags) {
					if (tag.empty())
						continue;

					// Normalize tag aliases:
					auto t = std::string(ModuleTags::normalize_tag(tag));

					// Populate unique values
					if (std::ranges::find(all_tags, t) == all_tags.end()) {
						all_tags.emplace_back(t);
					}
				}
			}
		}
		std::ranges::sort(all_tags, [](std::string const &a, std::string const &b) { return less_ci(a, b); });

		std::string roller_str;
		roller_str += Gui::blue_text("Sort by brand " LV_SYMBOL_RIGHT);
		roller_str += "\n";
		roller_str += "________________";
		roller_str += "\n";
		roller_str += Gui::orange_text("Tags:");
		roller_str += "\n";
		unsigned sel_idx = 0;
		for (unsigned i = 0; auto const &t : all_tags) {
			roller_str += t;
			roller_str += "\n";
			if (sel_tag == t)
				sel_idx = i + 3; // shift by 1
			i++;
		}
		if (roller_str.size())
			roller_str.pop_back();
		lv_roller_set_options(ui_ModuleListRoller, roller_str.c_str(), LV_ROLLER_MODE_NORMAL);
		lv_roller_set_selected(ui_ModuleListRoller, sel_idx, LV_ANIM_OFF);
		cur_selected = sel_idx;
	}

	void roller_module_list() {
		lv_label_set_text(ui_ModuleListRollerTitle, sel_brand_display_name.data());
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

	void roller_tag_list() {
		lv_label_set_text(ui_ModuleListRollerTitle, "Tags:");
		hide_module();
		populate_tags();
		show_roller();
	}

	void populate_modules_by_tag() {
		entries.clear();

		// Iterate all modules and filter by selected tag
		for (auto const &brand : ModuleFactory::getAllBrands()) {
			for (auto const &slug : ModuleFactory::getAllModuleSlugs(brand)) {
				auto tags = ModuleFactory::getModuleTags(brand, slug);

				for (auto const &tag : tags) {
					// Normalize tag aliases:
					auto t = std::string(ModuleTags::normalize_tag(tag));

					if (equal_ci(t, sel_tag)) {
						auto combined_slug = std::string(brand) + ":" + std::string(slug);
						auto display_name = ModuleFactory::getModuleDisplayName(combined_slug);
						entries.push_back(
							{.brand_slug = brand, .module_slug = slug, .module_display_name = display_name});
						break;
					}
				}
			}
		}

		// Remove 4ms Hub
		std::erase_if(entries, [](auto const &entry) {
			return (entry.brand_slug == "4msCompany" &&
					(entry.module_slug == "HubMedium" || entry.module_slug == "Panel"));
		});

		// Sort by display name
		std::ranges::sort(entries,
						  [](auto a, auto b) { return less_ci(a.module_display_name, b.module_display_name); });

		std::string slugs_str;
		slugs_str.reserve(entries.size() * (sizeof(ModuleTypeSlug) + 1));
		for (auto entry : entries) {
			slugs_str += entry.module_display_name;
			slugs_str += "\n";
		}
		if (slugs_str.length())
			slugs_str.pop_back();
		lv_roller_set_options(ui_ModuleListRoller, slugs_str.c_str(), LV_ROLLER_MODE_NORMAL);
		lv_roller_set_selected(ui_ModuleListRoller, 0, LV_ANIM_OFF);
	}

	void roller_module_list_by_tag() {
		lv_label_set_text(ui_ModuleListRollerTitle, sel_tag.c_str());
		populate_modules_by_tag();
		drawn_module_idx = -1;
		draw_module();
		draw_timer = lv_timer_create(draw_module_cb, 100, this);
		show_roller();
		show_module();
	}

	void show_roller() {
		lv_obj_set_width(ui_ModuleListRollerPanel, 166);
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
		view = View::CategoryRoller;
		if (sort == Sort::Brand) {
			roller_brand_list();
		} else {
			roller_tag_list();
		}
		roller_hover.hide();
	}

	void update() final {
		roller_hover.update();
		if (gui_state.back_button.is_just_released()) {
			roller_hover.hide();

			if (view == View::CategoryRoller) {
				gui_state.force_redraw_patch = true;
				load_prev_page();

			} else if (view == View::ModuleRoller) {
				view = View::CategoryRoller;
				if (draw_timer)
					lv_timer_del(draw_timer);
				draw_timer = nullptr;

				if (sort == Sort::Brand)
					roller_brand_list();
				else
					roller_tag_list();

			} else if (view == View::ModuleOnly) {
				view = View::ModuleRoller;
				show_roller();
			}
		}

		if (do_redraw) {
			do_redraw = false;
			draw_module();
		}

		poll_patch_file_changed();
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

		if (page->view == View::CategoryRoller) {
			if (page->sort == Sort::Brand) {
				auto idx = lv_roller_get_selected(event->target);
				if (idx == 0 || idx == 1) {
					page->sort = Sort::Tag;
					page->roller_tag_list();
				} else {
					page->view = View::ModuleRoller;
					ModuleTypeSlug selected_str;
					lv_roller_get_selected_str(event->target, selected_str._data, selected_str.capacity);
					page->sel_brand_display_name = selected_str.c_str();
					page->roller_module_list();
				}

			} else if (page->sort == Sort::Tag) {
				auto idx = lv_roller_get_selected(event->target);
				if (idx == 0 || idx == 1) {
					page->sort = Sort::Brand;
					page->roller_brand_list();
				} else {
					page->view = View::ModuleRoller;
					ModuleTypeSlug selected_str;
					lv_roller_get_selected_str(event->target, selected_str._data, selected_str.capacity);
					page->sel_tag = selected_str.c_str();
					page->roller_module_list_by_tag();
				}
			}

		} else if (page->view == View::ModuleRoller) {
			page->view = View::ModuleOnly;
			page->hide_roller();

		} else {
			auto cur_idx = lv_roller_get_selected(ui_ModuleListRoller);
			if (auto slug = page->get_selected_combined_slug(cur_idx); slug.length()) {
				page->add_module(slug);
				page->load_page(PageId::PatchView, page->args);
			} else {
				page->notify_queue.put({"Cannot add module, slug is empty"});
			}
		}
	}

	static inline unsigned cur_selected = 0;

	static void scroll_cb(lv_event_t *event) {
		auto page = static_cast<ModuleListPage *>(event->user_data);
		if (!page)
			return;

		page->roller_hover.hide();

		if (page->view == View::ModuleOnly || page->view == View::ModuleRoller) {
			lv_timer_reset(page->draw_timer);
		}

		if (page->view == View::CategoryRoller) {
			auto cur_sel = lv_roller_get_selected(ui_ModuleListRoller);
			auto prev_sel = page->cur_selected;

			// Skip over headers
			if (lv_roller_get_selected(ui_ModuleListRoller) < 3) {
				// Scrolled down -> scroll past headers
				if (prev_sel >= cur_sel) {
					cur_sel = 0;
				} else {
					cur_sel = 3;
				}
				lv_roller_set_selected(ui_ModuleListRoller, cur_sel, LV_ANIM_ON);
			}
			page->cur_selected = cur_sel;
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

	std::string get_selected_combined_slug(unsigned selected_idx) {
		std::string slug;
		if (selected_idx >= 0 && selected_idx < entries.size()) {
			auto const &entry = entries[selected_idx];
			slug = std::string{entry.brand_slug} + ":" + std::string{entry.module_slug};
		}
		return slug;
	}

	void draw_module() {
		if (view == View::ModuleOnly || view == View::ModuleRoller) {
			auto cur_idx = lv_roller_get_selected(ui_ModuleListRoller);
			if (cur_idx != drawn_module_idx) {

				if (auto slug = get_selected_combined_slug(cur_idx); slug.length()) {
					drawn_module_idx = cur_idx;
					draw_module(slug.c_str());
				}
			}
		}
	}

	void draw_module(BrandModuleSlug slug) {
		clear_module_canvas();

		ModuleDrawer drawer{ui_ModuleListImage, 240};

		auto [faceplate, width] = drawer.read_faceplate(slug);
		auto module_canvas = drawer.draw_faceplate(faceplate, width, page_pixel_buffer);

		if (module_canvas) {
			lv_obj_refr_size(module_canvas);
			auto width_px = lv_obj_get_width(module_canvas);
			lv_obj_set_width(ui_ModuleListImage, width_px);
			lv_obj_refr_size(ui_ModuleListImage);
			drawer.draw_elements(slug, module_canvas);
		} else
			notify_queue.put(Notification{"Could not load faceplate image", Notification::Priority::Error, 2000});
	}

	void clear_module_canvas() {
		lv_foreach_child(ui_ModuleListImage, [](auto *obj, int i) { lv_obj_del_async(obj); });
	}

	enum class View { CategoryRoller, ModuleRoller, ModuleOnly } view{View::CategoryRoller};
	enum class Sort { Brand, Tag } sort{Sort::Brand};
	lv_timer_t *draw_timer{};
	unsigned drawn_module_idx = -1;
	bool do_redraw = false;
	std::string sel_brand_display_name{"4msCompany"};
	std::string sel_tag{};
	std::string selected_module_slug;

	RollerHoverText roller_hover;
	;
};

} // namespace MetaModule
