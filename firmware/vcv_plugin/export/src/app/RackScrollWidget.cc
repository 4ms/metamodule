#include <app/RackScrollWidget.hpp>

namespace rack::app
{

RackScrollWidget::RackScrollWidget() = default;
RackScrollWidget::~RackScrollWidget() = default;

void RackScrollWidget::reset() {
}

math::Vec RackScrollWidget::getGridOffset() {
	return {};
}

void RackScrollWidget::setGridOffset(math::Vec gridOffset) {
}

float RackScrollWidget::getZoom() {
	return {};
}

void RackScrollWidget::setZoom(float zoom) {
}

void RackScrollWidget::setZoom(float zoom, math::Vec pivot) {
}

void RackScrollWidget::step() {
}
void RackScrollWidget::draw(const DrawArgs &args) {
}
void RackScrollWidget::onHoverKey(const HoverKeyEvent &e) {
}
void RackScrollWidget::onHoverScroll(const HoverScrollEvent &e) {
}
void RackScrollWidget::onHover(const HoverEvent &e) {
}
void RackScrollWidget::onButton(const ButtonEvent &e) {
}

} // namespace rack::app
