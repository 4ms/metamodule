#pragma once
#include "CoreModules/CoreProcessor.hh"
#include "CoreModules/moduleFactory.hh"
#include "CoreModules/pixels.hh"
#include "base_dyn_draw.hh"
#include "debug.hh"
#include "pr_dbg.hh"
#include "thorvg.h"
#include "util/overloaded.hh"
#include <cmath>

namespace MetaModule
{

struct DynDraw : BaseDynDraw {

	DynDraw(CoreProcessor *module, std::string_view slug)
		: module{module} {
		auto info = ModuleFactory::getModuleInfo(slug);

		// Scan elements for dynamic graphic displays
		for (auto i = 0u; auto const &el : info.elements) {
			auto const &index = info.indices[i++];

			std::visit(overloaded{[](BaseElement const &e) {},
								  [=, this](DynamicGraphicDisplay const &e) {
									  displays.push_back({.id = index.light_idx, .element = e});
								  }},
					   el);
		}
	}

	void prepare(lv_obj_t *module_canvas, unsigned px_per_3U) override {
		parent_canvas = module_canvas;

		for (auto &disp : displays) {
			disp.x = std::round(mm_to_px(disp.element.x_mm, px_per_3U));
			disp.y = std::round(mm_to_px(disp.element.y_mm, px_per_3U));
			disp.w = std::round(mm_to_px(disp.element.width_mm, px_per_3U));
			disp.h = std::round(mm_to_px(disp.element.height_mm, px_per_3U));

			if (disp.h > (lv_coord_t)px_per_3U || disp.w > 1000) {
				pr_warn("NativeDynDraw: canvas height %u exceeds module height, or width > 1000px\n", disp.h, disp.w);
				disp.h = std::min<lv_coord_t>(px_per_3U, disp.h);
				disp.w = std::min<lv_coord_t>(1000, disp.w);
			}

			disp.lv_canvas = lv_canvas_create(parent_canvas);
			lv_obj_move_to_index(disp.lv_canvas, 0);
			lv_obj_set_pos(disp.lv_canvas, disp.x, disp.y);
			lv_obj_set_size(disp.lv_canvas, disp.w, disp.h);

			pr_trace("Create buffer %u*%u lvgl pixels:  %u bytes\n", disp.w, disp.h, disp.w * disp.h * 3);

			disp.lv_buffer.resize(disp.w * disp.h * 3, 0);
			lv_canvas_set_buffer(disp.lv_canvas, disp.lv_buffer.data(), disp.w, disp.h, LV_IMG_CF_TRUE_COLOR_ALPHA);

			disp.fullcolor_buffer.resize(disp.w * disp.h, 0);

			module->show_graphic_display(disp.id, disp.fullcolor_buffer, disp.w, disp.h);
		}
	}

	void draw() override {
		if (!module || !parent_canvas || !lv_obj_is_valid(parent_canvas) || !lv_obj_is_visible(parent_canvas))
			return;

		for (auto &disp : displays) {
			Debug::Pin2::high();

			if (module->draw_graphic_display(disp.id)) {
				if (copy_buffer(disp.lv_buffer, disp.fullcolor_buffer))
					lv_obj_invalidate(disp.lv_canvas);
			}

			Debug::Pin2::low();
		}
	}

	void blur() override {

		for (auto &disp : displays) {
			pr_trace("DynDraw::blur() Release graphic display %u buffers\n", disp.id);
			if (module)
				module->hide_graphic_display(disp.id);
			disp.fullcolor_buffer.clear();
			disp.lv_buffer.clear();

			if (disp.lv_canvas && lv_obj_is_valid(disp.lv_canvas) && parent_canvas && lv_obj_is_valid(parent_canvas)) {
				lv_obj_del(disp.lv_canvas);
				disp.lv_canvas = nullptr;
			} else
				pr_err("DynDraw: cannot delete child canvas of module canvas %p\n", parent_canvas);
		}
	}

	~DynDraw() override {
		blur();
	}

private:
	CoreProcessor *module = nullptr;

	struct Display {
		unsigned id{};
		DynamicGraphicDisplay element{};
		lv_coord_t x{};
		lv_coord_t y{};
		lv_coord_t w{};
		lv_coord_t h{};
		lv_obj_t *lv_canvas{};
		std::vector<char> lv_buffer;
		std::vector<uint32_t> fullcolor_buffer;
	};
	std::vector<Display> displays;

	lv_obj_t *parent_canvas{};

	void clear_pixels() {
		for (auto &disp : displays) {
			std::ranges::fill(disp.fullcolor_buffer, 0);
			std::ranges::fill(disp.lv_buffer, 0);
		}
	}
};

} // namespace MetaModule
