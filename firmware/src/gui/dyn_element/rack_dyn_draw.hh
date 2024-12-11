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
		args.vg = nvgCreatePixelBufferContext(widget_canvas);
		args.fb = nullptr;
		canvas = widget_canvas;

		lv_obj_refr_size(canvas);
		width = lv_obj_get_width(canvas);
		height = lv_obj_get_height(canvas);
	}

	void draw() override {
		rack::contextGet()->window->vg = args.vg;

		if (auto mw = module_widget.lock()) {

			clear_canvas();

			for (auto &widget : mw->drawable_widgets) {
				if (!widget->isVisible())
					continue;

				args.clipBox = widget->getBox();

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

	// Takes ~50us for A 14HP-ish module
	void clear_canvas() {
		if (canvas) {
			auto buf = lv_canvas_get_img(canvas);
			if (buf) {
				std::memset((void *)buf->data, 0, width * height * 3);
			}
		}
	}
};
} // namespace MetaModule
