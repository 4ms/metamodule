#pragma once
#include <app/common.hpp>
#include <widget/TransparentWidget.hpp>

namespace rack::app
{

struct LightWidget : widget::TransparentWidget {
	NVGcolor bgColor = nvgRGBA(0, 0, 0, 0);
	NVGcolor color = nvgRGBA(0, 0, 0, 0);
	NVGcolor borderColor = nvgRGBA(0, 0, 0, 0);

	virtual void drawBackground(const DrawArgs &args) {
	}
	virtual void drawLight(const DrawArgs &args) {
	}
	virtual void drawHalo(const DrawArgs &args) {
	}
};

} // namespace rack::app
