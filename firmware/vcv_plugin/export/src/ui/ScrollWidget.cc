#include <ui/ScrollWidget.hpp>

namespace rack::ui
{

struct ScrollWidget::Internal {};

ScrollWidget::ScrollWidget() = default;
ScrollWidget::~ScrollWidget() = default;

void ScrollWidget::scrollTo(math::Rect r) {
}
math::Rect ScrollWidget::getContainerOffsetBound() {
	return {};
}
math::Vec ScrollWidget::getHandleOffset() {
	return {};
}
math::Vec ScrollWidget::getHandleSize() {
	return {};
}
bool ScrollWidget::isScrolling() {
	return {};
}
void ScrollWidget::draw(const DrawArgs &args) {
}
void ScrollWidget::step() {
}
void ScrollWidget::onHover(const HoverEvent &e) {
}
void ScrollWidget::onButton(const ButtonEvent &e) {
}
void ScrollWidget::onDragStart(const DragStartEvent &e) {
}
void ScrollWidget::onDragMove(const DragMoveEvent &e) {
}
void ScrollWidget::onHoverScroll(const HoverScrollEvent &e) {
}
void ScrollWidget::onHoverKey(const HoverKeyEvent &e) {
}

} // namespace rack::ui
