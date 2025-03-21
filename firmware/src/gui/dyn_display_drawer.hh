#pragma once
#include "CoreModules/CoreProcessor.hh"
#include "CoreModules/moduleFactory.hh"
#include "debug.hh"
#include "gui/elements/context.hh"
#include "gui/styles.hh"
#include "pr_dbg.hh"
#include "util/overloaded.hh"
#include <cmath>

namespace MetaModule
{

struct DynamicDisplayDrawer {

	// TODO: pass in the std::vector<DrawnElement> here
	DynamicDisplayDrawer(CoreProcessor *module, std::vector<DrawnElement> const &drawn_elements)
		: module{module} {
		for (auto const &drawn_el : drawn_elements) {

			std::visit(overloaded{[](BaseElement const &e) {},
								  [&drawn_el, this](DynamicGraphicDisplay const &e) {
									  displays.push_back({.id = drawn_el.gui_element.idx.light_idx,
														  .element = e,
														  .lv_canvas = drawn_el.gui_element.obj});
								  }},
					   drawn_el.element);
		}
	}

	DynamicDisplayDrawer(CoreProcessor *module, std::string_view slug)
		: module{module} {
		auto info = ModuleFactory::getModuleInfo(slug);

		// Scan elements for dynamic graphic displays
		for (auto i = 0u; auto const &el : info.elements) {
			auto const &index = info.indices[i++];

			std::visit(overloaded{[](BaseElement const &e) {},
								  [=, this](DynamicGraphicDisplay const &e) {
									  displays.push_back({.id = index.light_idx, .element = e, .lv_canvas = nullptr});
								  }},
					   el);
		}
	}

	void prepare(lv_obj_t *module_canvas, unsigned px_per_3U) {
		parent_canvas = module_canvas;

		for (auto &disp : displays) {
			// If size is 0, then don't make a buffer for it
			// This is done intentionally by rack::Module to create non-drawable elements
			// that need to be stepped
			if (disp.element.width_mm == 0 && disp.element.height_mm == 0) {
				pr_trace("DynDraw::prepare() Graphic display has zero size, will not draw\n");
				disp.fullcolor_buffer.clear();
				disp.w = 0;
				disp.lv_canvas = nullptr;

			} else {

				disp.x = std::round(mm_to_px(disp.element.x_mm, px_per_3U));
				disp.y = std::round(mm_to_px(disp.element.y_mm, px_per_3U));
				disp.w = std::round(mm_to_px(disp.element.width_mm, px_per_3U));
				disp.h = std::round(mm_to_px(disp.element.height_mm, px_per_3U));

				// Don't let rounding errors make us have an empty buffer
				disp.w = std::max<lv_coord_t>(disp.w, 1);
				disp.h = std::max<lv_coord_t>(disp.h, 1);

				if (disp.h > (lv_coord_t)px_per_3U || disp.w > 1000) {
					pr_warn("DynDraw: canvas height %u exceeds module height, or width > 1000px\n", disp.h, disp.w);
					disp.h = std::min<lv_coord_t>(px_per_3U, disp.h);
					disp.w = std::min<lv_coord_t>(1000, disp.w);
				}

				if (disp.lv_canvas == nullptr) {
					disp.lv_canvas = lv_canvas_create(parent_canvas);
					lv_obj_move_to_index(disp.lv_canvas, 0);
					lv_obj_set_pos(disp.lv_canvas, disp.x, disp.y);
					lv_obj_set_size(disp.lv_canvas, disp.w, disp.h);
				} else {
					lv_obj_move_to_index(disp.lv_canvas, 0);
				}

				// Debug object positions with a red border:
				// lv_obj_set_style_outline_width(disp.lv_canvas, 1, 0);
				// lv_obj_set_style_outline_color(disp.lv_canvas, lv_color_make(0xFF, 0, 0), 0);
				// lv_obj_set_style_outline_opa(disp.lv_canvas, LV_OPA_50, 0);
				// lv_obj_set_style_outline_pad(disp.lv_canvas, 1, 0);

				pr_trace("DynDraw: Create buffer %u*%u lvgl px: %u bytes\n", disp.w, disp.h, disp.w * disp.h * 3);

				disp.lv_buffer.resize(LV_CANVAS_BUF_SIZE_TRUE_COLOR_ALPHA(disp.w, disp.h), 0);
				lv_canvas_set_buffer(disp.lv_canvas, disp.lv_buffer.data(), disp.w, disp.h, LV_IMG_CF_TRUE_COLOR_ALPHA);

				disp.fullcolor_buffer.resize(disp.w * disp.h, 0);
			}

			module->show_graphic_display(disp.id, disp.fullcolor_buffer, disp.w, disp.lv_canvas);
		}
	}

	void draw() {
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

	void blur() {

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
				pr_err("DynDraw: cannot delete child canvas %p of module canvas %p\n", disp.lv_canvas, parent_canvas);
		}
	}

	~DynamicDisplayDrawer() {
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

	bool copy_buffer(std::span<char> lv_buffer, std::span<uint32_t> fullcolor_buffer) {
		if ((fullcolor_buffer.size() * 3) > lv_buffer.size()) {
			pr_err("DynDraw buffer size error\n");
			return false;
		}

		unsigned buf_pos = 0;
		bool diff = false;
		for (auto pixel : fullcolor_buffer) {

			auto col = lv_color_make_rgb565(pixel >> 16, pixel >> 8, pixel);
			uint8_t alpha = (pixel >> 24) & 0xFF;

			if (lv_buffer[buf_pos] != (col.full & 0xFF)) {
				diff = true;
				lv_buffer[buf_pos] = col.full & 0xFF;
			}
			if (lv_buffer[buf_pos + 1] != (col.full >> 8)) {
				diff = true;
				lv_buffer[buf_pos + 1] = col.full >> 8;
			}
			if (lv_buffer[buf_pos + 2] != alpha) {
				diff = true;
				lv_buffer[buf_pos + 2] = alpha;
			}

			buf_pos += 3;
		}
		return diff;
	}
};

} // namespace MetaModule
