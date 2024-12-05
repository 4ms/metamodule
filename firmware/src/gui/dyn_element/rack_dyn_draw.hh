#pragma once
#include "base_dyn_draw.hh"
#include <app/ModuleWidget.hpp>
#include <memory>

namespace MetaModule
{

struct RackDynDraw : BaseDynDraw {
	RackDynDraw(std::shared_ptr<rack::app::ModuleWidget> module_widget)
		: module_widget{module_widget} {
	}

	void draw() override {
		if (auto mw = module_widget.lock()) {

			rack::app::ModuleWidget::DrawArgs args{};

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
