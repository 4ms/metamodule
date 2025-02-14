#include <app/Knob.hpp>

namespace rack::app
{

Knob::Knob() = default;
Knob::~Knob() = default;

void Knob::initParamQuantity() {
	ParamWidget::initParamQuantity();
	engine::ParamQuantity *pq = getParamQuantity();
	if (pq) {
		if (snap)
			pq->snapEnabled = true;
		// Only enable smoothing if snapping is disabled
		if (smooth && !pq->snapEnabled)
			pq->smoothEnabled = true;
	}
}

void Knob::onHover(const HoverEvent &e) {
}
void Knob::onButton(const ButtonEvent &e) {
}
void Knob::onDragStart(const DragStartEvent &e) {
}
void Knob::onDragEnd(const DragEndEvent &e) {
}
void Knob::onDragMove(const DragMoveEvent &e) {
}
void Knob::onDragLeave(const DragLeaveEvent &e) {
}
void Knob::onHoverScroll(const HoverScrollEvent &e) {
}
void Knob::onLeave(const LeaveEvent &e) {
}

} // namespace rack::app
