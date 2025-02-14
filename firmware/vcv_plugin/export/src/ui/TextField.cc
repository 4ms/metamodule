#include <ui/TextField.hpp>

namespace rack::ui
{

TextField::TextField() = default;

void TextField::draw(const DrawArgs &args) {
}
void TextField::onDragHover(const DragHoverEvent &e) {
}
void TextField::onButton(const ButtonEvent &e) {
}
void TextField::onSelectText(const SelectTextEvent &e) {
}
void TextField::onSelectKey(const SelectKeyEvent &e) {
}
int TextField::getTextPosition(math::Vec mousePos) {
	return cursor;
}

std::string TextField::getText() {
	return text;
}
void TextField::setText(std::string text) {
	this->text = text;
}
void TextField::selectAll() {
}
std::string TextField::getSelectedText() {
	return {};
}
void TextField::insertText(std::string text) {
}
void TextField::copyClipboard() {
}
void TextField::cutClipboard() {
}
void TextField::pasteClipboard() {
}
void TextField::cursorToPrevWord() {
}
void TextField::cursorToNextWord() {
}
void TextField::createContextMenu() {
}

} // namespace rack::ui
