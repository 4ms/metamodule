#pragma once
#include "CoreModules/CoreProcessor.hh"
#include "CoreModules/moduleFactory.hh"
#include "base_dyn_draw.hh"
#include "lvgl.h"
#include "util/overloaded.hh"
// #include "debug.hh"
// #include "pr_dbg.hh"
#include <memory>

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
							   displays.push_back({i, e.x_mm, e.y_mm, e.width_mm, e.height_mm});
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
			auto x = mm_to_px(disp.x, px_per_3U);
			auto y = mm_to_px(disp.y, px_per_3U);
			auto w = mm_to_px(disp.w, px_per_3U);
			auto h = mm_to_px(disp.h, px_per_3U);
			lv_obj_set_pos(disp.canvas, x, y);
			lv_obj_set_size(disp.canvas, w, h);
			disp.draw_buffer.resize(w * h, CoreProcessor::Pixel{});
			disp.lvgl_buffer.resize(w * h * 3, 0);
		}
	}

	void draw() override {
		if (!module || !module_canvas || !lv_obj_is_valid(module_canvas) || !lv_obj_is_visible(module_canvas))
			return;

		for (auto &disp : displays) {
			[[maybe_unused]] auto changed = module->get_canvas_pixels(disp.id, disp.draw_buffer, disp.w, disp.h);
		}
	}

	void blur() override {
		clear_pixels();
	}

	~DynDraw() override = default;

private:
	CoreProcessor *module = nullptr;

	struct Display {
		unsigned id{};
		float x{};
		float y{};
		float w{};
		float h{};
		lv_obj_t *canvas{};
		std::vector<CoreProcessor::Pixel> draw_buffer;
		std::vector<char> lvgl_buffer;
	};
	std::vector<Display> displays;

	lv_obj_t *module_canvas{};

	void clear_pixels() {
		for (auto &disp : displays) {
			std::ranges::fill(disp.draw_buffer, CoreProcessor::Pixel{0, 0, 0, 0});
			std::ranges::fill(disp.lvgl_buffer, 0);
		}
	}
};

} // namespace MetaModule
