#include <ui/MenuItem.hpp>

namespace rack::ui
{

void MenuItem::draw(const DrawArgs &args) {
}

void MenuItem::drawOffset(NVGcontext *vg, float offset) {
}

void MenuItem::step() {
}

void MenuItem::onEnter(const EnterEvent &e) {
}

void MenuItem::onDragDrop(const DragDropEvent &e) {
}

void MenuItem::doAction(bool consume) {
	widget::EventContext cAction;
	ActionEvent eAction;
	eAction.context = &cAction;
	if (consume) {
		eAction.consume(this);
	}
	onAction(eAction);
}

void MenuItem::onAction(const ActionEvent &e) {
}

void ColorDotMenuItem::draw(const DrawArgs &args) {
}

void ColorDotMenuItem::step() {
}

} // namespace rack::ui
