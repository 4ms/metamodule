#include <app/LightWidget.hpp>

namespace rack::app
{

void LightWidget::draw(const DrawArgs &args) {
}

void LightWidget::drawLayer(const DrawArgs &args, int layer) {
	if (layer == 1) {
		// Use the formula `lightColor * (1 - dest) + dest` for blending
		// nvgGlobalCompositeBlendFunc(args.vg, NVG_ONE_MINUS_DST_COLOR, NVG_ONE);
		drawLight(args);
		// drawHalo(args);
	}

	Widget::drawLayer(args, layer);
}

void LightWidget::drawBackground(const DrawArgs &args) {
}

void LightWidget::drawLight(const DrawArgs &args) {
}

void LightWidget::drawHalo(const DrawArgs &args) {
}

} // namespace rack::app
