#pragma once
#include "base_dyn_draw.hh"
#include "src/core/lv_obj.h"
#include "vcv_plugin/internal/nanovg_gl.hh"
#include <app/ModuleWidget.hpp>
#include <memory>

namespace MetaModule
{

struct RackDynDraw : BaseDynDraw {
	static inline rack::app::ModuleWidget::DrawArgs args{}; // there can be only one of these

	RackDynDraw(std::shared_ptr<rack::app::ModuleWidget> module_widget)
		: module_widget{module_widget} {

		args.vg = nvgCreatePixelBufferContext();
	}

	// void prepare_focus(lv_obj_t *module_canvas) override {
	// }

	void draw(lv_obj_t *canvas) override {
		if (auto mw = module_widget.lock()) {

			nvgBindFrameBuffer(args.vg, canvas);

			for (auto &w : mw->drawable_widgets) {
				args.clipBox = w->getBox();

				w->draw(args);
				w->drawLayer(args, 1);
			}
		}
	}

private:
	std::weak_ptr<rack::app::ModuleWidget> module_widget{};
};
} // namespace MetaModule
