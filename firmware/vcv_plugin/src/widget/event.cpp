#include <widget/event.hpp>

namespace rack::widget
{

void EventState::setHoveredWidget(Widget *w) {
}
void EventState::setDraggedWidget(Widget *w, int button) {
}
void EventState::setDragHoveredWidget(Widget *w) {
}
void EventState::setSelectedWidget(Widget *w) {
}
void EventState::finalizeWidget(Widget *w) {
}
bool EventState::handleButton(math::Vec pos, int button, int action, int mods) {
	return false;
}
bool EventState::handleHover(math::Vec pos, math::Vec mouseDelta) {
	return false;
}
bool EventState::handleLeave() {
	return false;
}
bool EventState::handleScroll(math::Vec pos, math::Vec scrollDelta) {
	return false;
}
bool EventState::handleText(math::Vec pos, int codepoint) {
	return false;
}
bool EventState::handleKey(math::Vec pos, int key, int scancode, int action, int mods) {
	return false;
}
bool EventState::handleDrop(math::Vec pos, const std::vector<std::string> &paths) {
	return false;
}
bool EventState::handleDirty() {
	return false;
}

} // namespace rack::widget
