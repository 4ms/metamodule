#pragma once
#include "base_dyn_draw.hh"
#include <app/ModuleWidget.hpp>
#include <window/Window.hpp>
#include <memory>

namespace MetaModule
{

struct RackDynDraw : BaseDynDraw {
	rack::app::ModuleWidget::DrawArgs args{};

	RackDynDraw(std::shared_ptr<rack::app::ModuleWidget> module_widget)
		: module_widget{module_widget} {
		args.vg = nvgCreatePixelBufferContext(0);
	}

	void draw() override {
		if (auto mw = module_widget.lock()) {

			for (auto &w : mw->drawable_widgets) {
				w->draw(args);
				w->drawLayer(args, 1);
			}
		}
	}

private:
	std::weak_ptr<rack::app::ModuleWidget> module_widget{};
};
} // namespace MetaModule
