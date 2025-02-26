#pragma once
#include "CoreModules/elements/units.hh"
#include "base_dyn_draw.hh"
#include "debug.hh"
#include "pr_dbg.hh"
#include "vcv_plugin/internal/nanovg_pixbuf.hh"
#include <app/ModuleWidget.hpp>
#include <memory>

namespace MetaModule
{

struct RackDynDraw : BaseDynDraw {

	RackDynDraw(std::shared_ptr<rack::app::ModuleWidget> module_widget)
		: module_widget{module_widget} {

		if (auto mw = this->module_widget.lock()) {
			for (auto &widget : mw->get_drawable_widgets()) {
				displays.push_back({.widget = widget});
			}

			// This violates safety of shared pointer, so we must be careful
			// to use it only when the weak_ptr is locked
			// displays.push_back({.widget = module_widget.get()});
		}
	}

	void prepare(lv_obj_t *module_canvas, unsigned px_per_3U) override {
		// create canvas, same size as module
		if (auto mw = module_widget.lock()) {
			for (auto &disp : displays) {
				if (disp.canvas && lv_obj_is_valid(disp.canvas)) {
					pr_dbg("RackDynDraw: canvas is a valid lvgl object, deleting\n");
					lv_obj_del(disp.canvas);
				}

				// disp.x = std::round(PNGpx_to_SVGpx(disp.widget->box.pos.x));
				// disp.y = std::round(PNGpx_to_SVGpx(disp.widget->box.pos.y));
				// disp.w = std::round(PNGpx_to_SVGpx(disp.widget->box.size.x));
				// disp.h = std::round(PNGpx_to_SVGpx(disp.widget->box.size.y));
				disp.x = std::round(svgpx_to_pngpx(disp.widget->box.pos.x, px_per_3U));
				disp.y = std::round(svgpx_to_pngpx(disp.widget->box.pos.y, px_per_3U));
				disp.w = std::round(svgpx_to_pngpx(disp.widget->box.size.x, px_per_3U));
				disp.h = std::round(svgpx_to_pngpx(disp.widget->box.size.y, px_per_3U));

				if (disp.h > (lv_coord_t)px_per_3U || disp.w > 1000) {
					pr_dbg("Height %u exceeds module height, or width %u > 1000px\n", disp.h, disp.w);
					disp.h = std::min<lv_coord_t>(px_per_3U, disp.h);
					disp.w = std::min<lv_coord_t>(1000, disp.w);
				}

				disp.canvas = lv_canvas_create(module_canvas);
				lv_obj_move_to_index(disp.canvas, 0);
				lv_obj_set_pos(disp.canvas, disp.x, disp.y);
				lv_obj_set_size(disp.canvas, disp.w, disp.h);
				lv_obj_set_align(disp.canvas, LV_ALIGN_TOP_LEFT);
				lv_obj_set_style_border_width(disp.canvas, 1, 0);
				lv_obj_set_style_border_color(disp.canvas, lv_color_make(0xFF, 0, 0), 0);

				// setup backing buffer for canvas
				disp.buffer.resize(LV_CANVAS_BUF_SIZE_TRUE_COLOR_ALPHA(disp.w, disp.h));
				std::ranges::fill(disp.buffer, 0);
				lv_canvas_set_buffer(disp.canvas, disp.buffer.data(), disp.w, disp.h, LV_IMG_CF_TRUE_COLOR_ALPHA);

				disp.args.vg = nvgCreatePixelBufferContext(disp.canvas, px_per_3U);
				disp.args.fb = nullptr;

				pr_dbg("RackDynDraw: prepared canvas at %u, %u (%u x %u) (pxp3u %u) -- create ctx %p\n",
					   disp.x,
					   disp.y,
					   disp.w,
					   disp.h,
					   px_per_3U,
					   disp.args.vg);
			}
		}
	}

	void draw() override {

		if (auto mw = module_widget.lock()) {

			mw->step();
			// mw->draw(disp.args);
			// mw->drawLayer(disp.args, 1);

			for (auto &disp : displays) {
				if (!disp.widget->isVisible())
					continue;

				if (!disp.args.vg)
					return;

				rack::contextGet()->window->vg = disp.args.vg;

				clear_canvas();
				nvgBeginFrame(disp.args.vg, mw->box.getWidth(), mw->box.getHeight(), 1);

				disp.args.clipBox = disp.widget->getBox();

				Debug::Pin2::high();
				disp.widget->step();
				mw->drawChild(disp.widget, disp.args);
				mw->drawChild(disp.widget, disp.args, 1);
				Debug::Pin2::low();

				nvgEndFrame(disp.args.vg);
			}
		}
	}

	void blur() override {
		if (auto mw = module_widget.lock()) {

			for (auto &disp : displays) {
				if (disp.args.vg) {
					pr_dbg("RackDynDraw:: blur (del ctx %p)\n", disp.args.vg);
					nvgDeletePixelBufferContext(disp.args.vg);
					disp.args.vg = nullptr;
				}
				disp.buffer.clear();
			}
		}
		rack::contextGet()->window->vg = nullptr;
	}

	~RackDynDraw() override {
		blur();
	}

private:
	std::weak_ptr<rack::app::ModuleWidget> module_widget{};

	struct Display {
		rack::widget::Widget *widget{};
		lv_coord_t x{};
		lv_coord_t y{};
		lv_coord_t w{};
		lv_coord_t h{};
		lv_obj_t *canvas{};

		rack::app::ModuleWidget::DrawArgs args{}; // one per module
		std::vector<char> buffer;
	};

	std::vector<Display> displays;

	void clear_canvas() {
		for (auto &disp : displays) {
			std::ranges::fill(disp.buffer, 0);
		}
	}
};
} // namespace MetaModule
