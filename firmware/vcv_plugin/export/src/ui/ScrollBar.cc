#include <ui/Scrollbar.hpp>

namespace rack::ui
{

struct Scrollbar::Internal {};

Scrollbar::Scrollbar() = default;

Scrollbar::~Scrollbar() = default;

void Scrollbar::draw(const DrawArgs &args) {
}
void Scrollbar::onButton(const ButtonEvent &e) {
}
void Scrollbar::onDragStart(const DragStartEvent &e) {
}
void Scrollbar::onDragEnd(const DragEndEvent &e) {
}
void Scrollbar::onDragMove(const DragMoveEvent &e) {
}

} // namespace rack::ui
