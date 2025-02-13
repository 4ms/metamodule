#include <app/ParamWidget.hpp>
#include <engine/Module.hpp>

namespace rack::app
{

engine::ParamQuantity *ParamWidget::getParamQuantity() {
	if (!module)
		return nullptr;
	return module->getParamQuantity(paramId);
}

void ParamWidget::createTooltip() {
}

void ParamWidget::destroyTooltip() {
}

void ParamWidget::createContextMenu() {
}

void ParamWidget::resetAction() {
}

void ParamWidget::step() {
}
void ParamWidget::draw(const DrawArgs &args) {
}
void ParamWidget::onButton(const ButtonEvent &e) {
}
void ParamWidget::onDoubleClick(const DoubleClickEvent &e) {
}
void ParamWidget::onEnter(const EnterEvent &e) {
}
void ParamWidget::onLeave(const LeaveEvent &e) {
}

} // namespace rack::app
