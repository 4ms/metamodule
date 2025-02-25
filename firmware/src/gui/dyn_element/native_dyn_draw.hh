#pragma once
#include "CoreModules/CoreProcessor.hh"
#include "CoreModules/moduleFactory.hh"
#include "base_dyn_draw.hh"
#include "thorvg.h"
#include "util/overloaded.hh"
// #include "debug.hh"
#include "pr_dbg.hh"

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

			pr_dbg("Create buffer w*h * 4 = %u*%u, %u\n", w, h, w * h * 4);
			disp.lv_buffer.resize(w * h, 0); //CoreProcessor::Pixel{});
			lv_canvas_set_buffer(
				disp.canvas, disp.lv_buffer.data(), w, h, LV_IMG_CF_RGBA8888); //LV_IMG_CF_TRUE_COLOR_ALPHA);

			disp.lv_buffer.resize(w * h, 0); //CoreProcessor::Pixel{});

			// disp.tvg_canvas = tvg::SwCanvas::gen();
			// disp.tvg_canvas->target(disp.buffer.data(), w, w, h, tvg::ColorSpace::ARGB8888);
		}
	}

	void draw() override {
		if (!module || !module_canvas || !lv_obj_is_valid(module_canvas) || !lv_obj_is_visible(module_canvas))
			return;

		for (auto &disp : displays) {
			auto pix_buf = reinterpret_cast<CoreProcessor::Pixel *>(disp.fullcolor_buffer.data());
			[[maybe_unused]] auto changed = module->get_canvas_pixels(disp.id, pix_buf, disp.w, disp.h);
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
		// tvg::SwCanvas *tvg_canvas{};
		std::vector<char> lv_buffer;
		std::vector<uint32_t> fullcolor_buffer;
	};
	std::vector<Display> displays;

	lv_obj_t *module_canvas{};

	void clear_pixels() {
		for (auto &disp : displays) {
			// std::ranges::fill(disp.buffer, CoreProcessor::Pixel{0, 0, 0, 0});
			std::ranges::fill(disp.lv_buffer, 0);
		}
	}
};

} // namespace MetaModule
