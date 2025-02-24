#pragma once
#include "base_dyn_draw.hh"
#include "lvgl.h"
// #include "debug.hh"
// #include "pr_dbg.hh"
#include "vcv_plugin/internal/nanovg_pixbuf.hh"
#include <app/ModuleWidget.hpp>
#include <memory>

namespace MetaModule
{

struct RackDynDraw : BaseDynDraw {

	RackDynDraw(std::shared_ptr<rack::app::ModuleWidget> module_widget)
		: module_widget{module_widget} {
	}

	void prepare(lv_obj_t *module_canvas, unsigned px_per_3U) override {
		// create canvas, same size as module
		lv_obj_refr_size(module_canvas);
		auto w = lv_obj_get_width(module_canvas);
		auto h = lv_obj_get_height(module_canvas);

		if (canvas && lv_obj_is_valid(canvas)) {
			lv_obj_del(canvas);
		}

		canvas = lv_canvas_create(module_canvas);
		lv_obj_set_pos(canvas, 0, 0);
		lv_obj_set_size(canvas, w, h);

		// setup backing buffer for canvas
		buffer.resize(LV_CANVAS_BUF_SIZE_TRUE_COLOR_ALPHA(w, h));
		std::ranges::fill(buffer, 0);
		lv_canvas_set_buffer(canvas, buffer.data(), w, h, LV_IMG_CF_TRUE_COLOR_ALPHA);

		args.vg = nvgCreatePixelBufferContext(canvas, px_per_3U);
		args.fb = nullptr;

		lv_obj_refr_size(canvas);
		width = lv_obj_get_width(canvas);
		height = lv_obj_get_height(canvas);
	}

	void draw() override {
		if (!args.vg)
			return;

		rack::contextGet()->window->vg = args.vg;

		if (auto mw = module_widget.lock()) {

			clear_canvas();
			nvgBeginFrame(args.vg, mw->box.getWidth(), mw->box.getHeight(), 1);

			// Debug::Pin1::high();
			mw->step();
			mw->draw(args);
			mw->drawLayer(args, 1);
			// Debug::Pin1::low();

			for (auto &widget : mw->get_drawable_widgets()) {
				if (!widget->isVisible())
					continue;

				args.clipBox = widget->getBox();

				// Debug::Pin2::high();
				widget->step();
				mw->drawChild(widget, args);
				mw->drawChild(widget, args, 1);
				// Debug::Pin2::low();
			}
			nvgEndFrame(args.vg);
		}
	}

	void blur() override {
		nvgDeletePixelBufferContext(args.vg);
		args.vg = nullptr;
		rack::contextGet()->window->vg = nullptr;

		buffer.clear();
	}

	~RackDynDraw() override = default;

private:
	lv_obj_t *canvas{};
	lv_coord_t width{};
	lv_coord_t height{};

	std::weak_ptr<rack::app::ModuleWidget> module_widget{};
	rack::app::ModuleWidget::DrawArgs args{}; // one per module

	std::vector<char> buffer;

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
