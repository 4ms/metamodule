#pragma once
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
	}

	void draw() override {
		if (auto mw = module_widget.lock()) {

			// args.clipBox = mw->getBox();

			for (auto &w : mw->drawable_widgets) {
				if (!w->isVisible())
					continue;

				// Don't draw if child is outside clip box
				// if (!args.clipBox.intersects(w->box))
				// 	continue;

				mw->drawChild(w, args);
				mw->drawChild(w, args, 1);
			}
		}
	}

	~RackDynDraw() override = default;

private:
	std::weak_ptr<rack::app::ModuleWidget> module_widget{};
	rack::app::ModuleWidget::DrawArgs args{}; // one per module
};
} // namespace MetaModule
