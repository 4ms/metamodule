#pragma once
#include "CoreModules/CoreProcessor.hh"
#include "CoreModules/moduleFactory.hh"
#include "base_dyn_draw.hh"
#include "debug.hh"
#include "gui/styles.hh"
#include "pr_dbg.hh"
#include "thorvg.h"
#include "util/overloaded.hh"
#include <cmath>
#include <cstdint>

namespace MetaModule
{

struct DynDraw : BaseDynDraw {

	DynDraw(CoreProcessor *module, std::string_view slug)
		: module{module} {
		auto info = ModuleFactory::getModuleInfo(slug);

		// Scan elements for dynamic graphic displays
		unsigned i = 0;
		for (auto const &el : info.elements) {
			std::visit(overloaded{
						   [](BaseElement const &e) {},
						   [i = i, this](DynamicGraphicDisplay const &e) {
							   displays.push_back({.id = i});
							   element = e;
							   pr_dbg("Found display: %f,%f + %f,%f\n", e.x_mm, e.y_mm, e.width_mm, e.height_mm);
						   },
					   },
					   el);
			i++;
		}
	}

	void prepare(lv_obj_t *widget_canvas, unsigned px_per_3U) override {
		module_canvas = widget_canvas;

		for (auto &disp : displays) {
			disp.canvas = lv_canvas_create(module_canvas);

			disp.x = std::round(mm_to_px(element.x_mm, px_per_3U));
			disp.y = std::round(mm_to_px(element.y_mm, px_per_3U));
			disp.w = std::round(mm_to_px(element.width_mm, px_per_3U));
			disp.h = std::round(mm_to_px(element.height_mm, px_per_3U));

			if (disp.h > (lv_coord_t)px_per_3U) {
				pr_dbg("Height %u cannot exceed 3U\n", disp.h);
				disp.h = px_per_3U;
			}
			lv_obj_set_pos(disp.canvas, disp.x, disp.y);
			lv_obj_set_size(disp.canvas, disp.w, disp.h);

			pr_dbg("Create buffer %u*%u lvgl pixels:  %u bytes\n", disp.w, disp.h, disp.w * disp.h * 3);

			disp.lv_buffer.resize(disp.w * disp.h * 3, 0);
			lv_canvas_set_buffer(disp.canvas, disp.lv_buffer.data(), disp.w, disp.h, LV_IMG_CF_TRUE_COLOR_ALPHA);

			disp.fullcolor_buffer.resize(disp.w * disp.h, CoreProcessor::Pixel{});

			module->show_graphic_display(disp.id, disp.fullcolor_buffer.data(), disp.w, disp.h);
		}
	}

	void draw() override {
		if (!module || !module_canvas || !lv_obj_is_valid(module_canvas) || !lv_obj_is_visible(module_canvas))
			return;

		for (auto &disp : displays) {
			Debug::Pin2::high();

			if (module->get_canvas_pixels(disp.id, disp.fullcolor_buffer.data(), disp.w, disp.h)) {
				lv_coord_t x = 0;
				lv_coord_t y = 0;
				bool diff = false;
				for (auto px : disp.fullcolor_buffer) {
					auto col = lv_color_make_rgb565(px.red, px.green, px.blue);

					const unsigned buf_pos = (x + y * disp.w) * 3;

					if (disp.lv_buffer[buf_pos] != (col.full & 0xFF)) {
						diff = true;
						disp.lv_buffer[buf_pos] = col.full & 0xFF;
					}
					if (disp.lv_buffer[buf_pos + 1] != (col.full >> 8)) {
						diff = true;
						disp.lv_buffer[buf_pos + 1] = col.full >> 8;
					}
					if (disp.lv_buffer[buf_pos + 2] != px.alpha) {
						diff = true;
						disp.lv_buffer[buf_pos + 2] = px.alpha;
					}

					if (++x >= disp.w) {
						x = 0;
						y++;
						if (y > disp.h) {
							pr_err("NativeDynDraw Range error: %u x %u != %zu\n",
								   disp.w,
								   disp.h,
								   disp.fullcolor_buffer.size());
							break;
						}
					}
				}

				if (diff) {
					lv_obj_invalidate(disp.canvas);
				}
			}

			Debug::Pin2::low();
		}
	}

	void blur() override {
		clear_pixels();
		for (auto &disp : displays) {
			module->hide_graphic_display(disp.id);
		}
	}

	~DynDraw() override = default;

private:
	CoreProcessor *module = nullptr;

	struct Display {
		unsigned id{};
		lv_coord_t x{};
		lv_coord_t y{};
		lv_coord_t w{};
		lv_coord_t h{};
		lv_obj_t *canvas{};
		// tvg::SwCanvas *tvg_canvas{};
		std::vector<char> lv_buffer;
		std::vector<CoreProcessor::Pixel> fullcolor_buffer;
	};
	std::vector<Display> displays;

	DynamicGraphicDisplay element{};

	lv_obj_t *module_canvas{};

	void clear_pixels() {
		for (auto &disp : displays) {
			// std::ranges::fill(disp.buffer, CoreProcessor::Pixel{0, 0, 0, 0});
			std::ranges::fill(disp.lv_buffer, 0);
		}
	}
};

} // namespace MetaModule
