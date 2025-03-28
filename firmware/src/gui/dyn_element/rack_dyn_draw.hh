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
			// This violates safety of shared pointer, so we must be careful
			// to use `displays[].widget` only when the weak_ptr is locked

			for (auto &widget : mw->get_drawable_widgets()) {
				displays.push_back({.widget = widget});
			}

#if defined(__GNUC__) && !defined(__clang__)
			// See if the ModuleWidget overrides draw() or drawLayer().
			// We will only allocate the module-sized pixel buffer if the module needs it.
			// This uses a GCC extension, so for simulator we just always assume
			// the ModuleWidget uses a custom draw().
			//
			// See https://gcc.gnu.org/onlinedocs/gcc/Bound-member-functions.html

			rack::app::ModuleWidget *ptr = mw.get();
			custom_draw =
				(void *)((*ptr).*(&rack::app::ModuleWidget::draw)) != (void *)(&rack::app::ModuleWidget::draw);
			custom_draw |= (void *)((*ptr).*(&rack::app::ModuleWidget::drawLayer)) !=
						   (void *)(&rack::app::ModuleWidget::drawLayer);

#else
			custom_draw = true;
#endif

			if (custom_draw) {
				displays.push_back({.widget = mw.get()});
			}
		}
	}

	void prepare(lv_obj_t *module_canvas, unsigned px_per_3U) override {

		if (auto mw = module_widget.lock()) {
			for (auto &disp : displays) {

				if (disp.lv_canvas && lv_obj_is_valid(disp.lv_canvas)) {
					pr_warn("RackDynDraw: canvas is a valid lvgl object, deleting\n");
					lv_obj_del(disp.lv_canvas);
				}

				disp.x = std::round(svgpx_to_pngpx(disp.widget->box.pos.x, px_per_3U));
				disp.y = std::round(svgpx_to_pngpx(disp.widget->box.pos.y, px_per_3U));
				disp.w = std::round(svgpx_to_pngpx(disp.widget->box.size.x, px_per_3U));
				disp.h = std::round(svgpx_to_pngpx(disp.widget->box.size.y, px_per_3U));

				// Don't let rounding errors make us have an empty buffer
				disp.w = std::max<lv_coord_t>(disp.w, 1);
				disp.h = std::max<lv_coord_t>(disp.h, 1);

				if (disp.h > (lv_coord_t)px_per_3U || disp.w > 1000) {
					pr_warn(
						"RackDynDraw: canvas height %u exceeds module height, or width %u > 1000px\n", disp.h, disp.w);
					disp.h = std::min<lv_coord_t>(px_per_3U, disp.h);
					disp.w = std::min<lv_coord_t>(1000, disp.w);
				}

				disp.lv_canvas = lv_canvas_create(module_canvas);
				lv_obj_move_to_index(disp.lv_canvas, 0);
				lv_obj_set_pos(disp.lv_canvas, disp.x, disp.y);
				lv_obj_set_size(disp.lv_canvas, disp.w, disp.h);

				// Debug object positions with a red border:
				// lv_obj_set_style_outline_width(disp.lv_canvas, 1, 0);
				// lv_obj_set_style_outline_color(disp.lv_canvas, lv_color_make(0xFF, 0, 0), 0);
				// lv_obj_set_style_outline_opa(disp.lv_canvas, LV_OPA_50, 0);
				// lv_obj_set_style_outline_pad(disp.lv_canvas, 1, 0);

				// setup backing buffer for canvas
				disp.lv_buffer.resize(LV_CANVAS_BUF_SIZE_TRUE_COLOR_ALPHA(disp.w, disp.h));
				std::ranges::fill(disp.lv_buffer, 0);
				lv_canvas_set_buffer(disp.lv_canvas, disp.lv_buffer.data(), disp.w, disp.h, LV_IMG_CF_TRUE_COLOR_ALPHA);

				disp.fullcolor_buffer.resize(disp.w * disp.h);
				std::ranges::fill(disp.fullcolor_buffer, 0);
				// disp.tvg_canvas.reset(tvg::SwCanvas::gen());

				disp.args.vg = nvgCreatePixelBufferContext(disp.lv_canvas, disp.fullcolor_buffer, disp.w, px_per_3U);
				disp.args.fb = nullptr;

				pr_dbg("RackDynDraw: prepared canvas at %u, %u (%u x %u, 3u=%u)\n",
					   disp.x,
					   disp.y,
					   disp.w,
					   disp.h,
					   px_per_3U);

				pr_dump(" -- Create NVGContext %p buffer %p + 0x%xB, lv_buffer is %p + 0x%xB \n",
						disp.args.vg,
						disp.fullcolor_buffer.data(),
						disp.fullcolor_buffer.size() * sizeof(disp.fullcolor_buffer[0]),
						disp.lv_buffer.data(),
						disp.lv_buffer.size());
			}
		}
	}

	void draw() override {

		if (auto mw = module_widget.lock()) {
			if (!custom_draw) {
				mw->step();
			}

			for (auto &disp : displays) {
				// Debug::Pin2::high();

				if (!disp.widget->isVisible())
					continue;

				if (!disp.args.vg)
					return;

				rack::contextGet()->window->vg = disp.args.vg;

				std::ranges::fill(disp.fullcolor_buffer, 0);

				nvgBeginFrame(disp.args.vg, mw->box.getWidth(), mw->box.getHeight(), 1);

				disp.args.clipBox = disp.widget->getBox().zeroPos();

				disp.widget->step();
				for (auto *child : disp.widget->children) {
					if (child->isVisible())
						child->step();
				}

				disp.widget->draw(disp.args);
				disp.widget->drawLayer(disp.args, 1);

				nvgEndFrame(disp.args.vg);

				if (copy_buffer(disp.lv_buffer, disp.fullcolor_buffer)) {
					lv_obj_invalidate(disp.lv_canvas);
				}

				// Debug::Pin2::low();
			}
		}
	}

	void blur() override {
		if (auto mw = module_widget.lock()) {

			for (auto &disp : displays) {
				if (disp.args.vg) {
					pr_trace("RackDynDraw::blur() call nvgDeletePixelBufferContext(NVGcontext %p)\n", disp.args.vg);
					nvgDeletePixelBufferContext(disp.args.vg);
					disp.args.vg = nullptr;
				}
			}
		}
		for (auto &disp : displays) {
			if (disp.lv_canvas && lv_obj_is_valid(disp.lv_canvas)) {
				lv_obj_del(disp.lv_canvas);
				disp.lv_canvas = nullptr;
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
		lv_obj_t *lv_canvas{};

		rack::app::ModuleWidget::DrawArgs args{};
		std::vector<char> lv_buffer;

		// std::unique_ptr<tvg::SwCanvas> tvg_canvas;
		std::vector<uint32_t> fullcolor_buffer;
	};

	std::vector<Display> displays;

	bool custom_draw = false;
};
} // namespace MetaModule
