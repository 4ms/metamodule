#pragma once
#include "CoreModules/elements/units.hh"
#include "base_dyn_draw.hh"
#include "lvgl.h"
#include "pr_dbg.hh"
#include "vcv_plugin/internal/nanovg_gl.hh"
#include <app/ModuleWidget.hpp>
#include <memory>

namespace MetaModule
{

struct RackDynDraw : BaseDynDraw {

	RackDynDraw(std::shared_ptr<rack::app::ModuleWidget> module_widget)
		: module_widget{module_widget} {
	}

	void prepare(lv_obj_t *widget_canvas) override {
		pr_dbg("RackDynDraw::prepare(canvas = %p)\n", widget_canvas);
		args.vg = nvgCreatePixelBufferContext(widget_canvas);
		args.fb = nullptr;
		canvas = widget_canvas;
		width = lv_obj_get_width(canvas);
		height = lv_obj_get_height(canvas);
	}

	void draw() override {

		clear_canvas();

		if (auto mw = module_widget.lock()) {

			// args.clipBox = mw->getBox();

			for (auto &widget : mw->drawable_widgets) {
				if (!widget->isVisible())
					continue;

				// Don't draw if child is outside clip box
				// if (!args.clipBox.intersects(w->box))
				// 	continue;

				// auto b = widget->getBox();
				// auto x = svgpx_to_pngpx(b.pos.x);
				// auto y = svgpx_to_pngpx(b.pos.y);
				// auto w = svgpx_to_pngpx(b.size.x);
				// auto h = svgpx_to_pngpx(b.size.y);

				// auto buf = lv_canvas_get_img(canvas);
				// const auto cw = buf->header.w;
				// const uint32_t px_size = 3; //lv_img_cf_get_px_size(buf->header.cf) >> 3;

				// uint32_t px = cw * y * px_size + x * px_size;
				// for (lv_coord_t i = 0; i < h; i++) {
				// 	lv_memset_00((void *)&buf->data[px], w * px_size);
				// 	px += cw * px_size;
				// }

				mw->drawChild(widget, args);
				mw->drawChild(widget, args, 1);
			}
		}
	}

	~RackDynDraw() override = default;

private:
	lv_obj_t *canvas{};
	lv_coord_t width{};
	lv_coord_t height{};

	std::weak_ptr<rack::app::ModuleWidget> module_widget{};
	rack::app::ModuleWidget::DrawArgs args{}; // one per module

	void clear_canvas() {
		if (canvas) {
			auto buf = lv_canvas_get_img(canvas);
			if (buf) {
				std::memset((void *)buf->data, 0, width * height * 3);
			}
		}
	}

	// void clear_canvas(lv_coord_t x, lv_coord_t y, lv_coord_t w, lv_coord_t h) {
	// }
};
} // namespace MetaModule
