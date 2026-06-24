#include <app/Switch.hpp>

namespace rack::app
{

Switch::Switch() {
	internal = nullptr;
}

Switch::~Switch() = default;

void Switch::initParamQuantity() {
}
void Switch::step() {
}
void Switch::onDoubleClick(const DoubleClickEvent &e) {
}
void Switch::onDragStart(const DragStartEvent &e) {
}
void Switch::onDragEnd(const DragEndEvent &e) {
}

} // namespace rack::app
