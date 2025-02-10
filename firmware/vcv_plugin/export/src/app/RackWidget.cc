#include <app/RackWidget.hpp>

namespace rack::app
{

widget::Widget *RackWidget::getModuleContainer() {
	return {};
}
widget::Widget *RackWidget::getCableContainer() {
	return {};
}
math::Vec RackWidget::getMousePos() {
	return {};
}

void RackWidget::clear() {
}
void RackWidget::mergeJson(json_t *rootJ) {
}
void RackWidget::fromJson(json_t *rootJ) {
}
void RackWidget::pasteJsonAction(json_t *rootJ) {
}
void RackWidget::pasteModuleJsonAction(json_t *moduleJ) {
}
void RackWidget::pasteClipboardAction() {
}

void RackWidget::addModule(ModuleWidget *mw) {
}
void RackWidget::addModuleAtMouse(ModuleWidget *mw) {
}
void RackWidget::removeModule(ModuleWidget *mw) {
}
ModuleWidget *RackWidget::getModule(int64_t moduleId) {
	return nullptr;
}
std::vector<ModuleWidget * RackWidget::> getModules() {
	return {};
}
bool RackWidget::hasModules() {
	return {};
}

bool RackWidget::requestModulePos(ModuleWidget *mw, math::Vec pos) {
	return {};
}
void RackWidget::setModulePosNearest(ModuleWidget *mw, math::Vec pos) {
}
void RackWidget::setModulePosForce(ModuleWidget *mw, math::Vec pos) {
}
void RackWidget::setModulePosSqueeze(ModuleWidget *mw, math::Vec pos) {
}
void RackWidget::updateModuleOldPositions() {
}
history::ComplexAction *RackWidget::getModuleDragAction() {
	return {};
}

void RackWidget::updateSelectionFromRect() {
}
void RackWidget::selectAll() {
}
void RackWidget::deselectAll() {
}
void RackWidget::select(ModuleWidget *mw, bool selected = true) {
}
bool RackWidget::hasSelection() {
	return {};
}
std::set<ModuleWidget *> RackWidget::selected;
const RackWidget::std::set<ModuleWidget *> &getSelected() {
	return selected;
}
bool RackWidget::isSelected(ModuleWidget *mw) {
	return {};
}
json_t *RackWidget::selectionToJson(bool cables = true) {
	return {};
}
void RackWidget::loadSelection(std::string path) {
}
void RackWidget::loadSelectionDialog() {
}
void RackWidget::saveSelection(std::string path) {
}
void RackWidget::saveSelectionDialog() {
}
void RackWidget::copyClipboardSelection() {
}
void RackWidget::resetSelectionAction() {
}
void RackWidget::randomizeSelectionAction() {
}
void RackWidget::disconnectSelectionAction() {
}
void RackWidget::cloneSelectionAction(bool cloneCables = true) {
}
void RackWidget::bypassSelectionAction(bool bypassed) {
}
bool RackWidget::isSelectionBypassed() {
	return {};
}
void RackWidget::deleteSelectionAction() {
}
bool RackWidget::requestSelectionPos(math::Vec delta) {
	return {};
}
void RackWidget::setSelectionPosNearest(math::Vec delta) {
}
void RackWidget::appendSelectionContextMenu(ui::Menu *menu) {
}

void RackWidget::clearCables() {
}
void RackWidget::clearCablesAction() {
}
void RackWidget::clearCablesOnPort(PortWidget *port) {
}
void RackWidget::addCable(CableWidget *cw) {
}
void RackWidget::removeCable(CableWidget *cw) {
}
CableWidget *RackWidget::getIncompleteCable() {
	return {};
}
void RackWidget::setIncompleteCable(CableWidget *cw) {
}
CableWidget *RackWidget::releaseIncompleteCable() {
	return {};
}
CableWidget *RackWidget::getTopCable(PortWidget *port) {
	return {};
}
CableWidget *RackWidget::getCable(int64_t cableId) {
	return {};
}
std::vector<CableWidget * RackWidget::> getCompleteCables() {
	return {};
}
std::vector<CableWidget * RackWidget::> getCablesOnPort(PortWidget *port) {
	return {};
}
std::vector<CableWidget * RackWidget::> getCompleteCablesOnPort(PortWidget *port) {
	return {};
}
int RackWidget::getNextCableColorId() {
	return {};
}
void RackWidget::setNextCableColorId(int id) {
}
NVGcolor RackWidget::getNextCableColor() {
	return {};
}
ParamWidget *RackWidget::getTouchedParam() {
	return {};
}
void RackWidget::setTouchedParam(ParamWidget *pw) {
}

} // namespace rack::app
