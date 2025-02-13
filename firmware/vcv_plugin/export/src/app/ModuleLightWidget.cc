#include <app/ModuleLightWidget.hpp>

namespace rack::app
{
ModuleLightWidget::ModuleLightWidget() = default;
ModuleLightWidget::~ModuleLightWidget() = default;

engine::Light *ModuleLightWidget::getLight(int colorId) {
	if (!module || firstLightId < 0)
		return nullptr;
	return &module->lights[firstLightId + colorId];
}

engine::LightInfo *ModuleLightWidget::getLightInfo() {
	if (!module || firstLightId < 0)
		return nullptr;
	return module->lightInfos[firstLightId];
}

void ModuleLightWidget::createTooltip() {
}

void ModuleLightWidget::destroyTooltip() {
}

void ModuleLightWidget::step() {
}
void ModuleLightWidget::onHover(const HoverEvent &e) {
}
void ModuleLightWidget::onEnter(const EnterEvent &e) {
}
void ModuleLightWidget::onLeave(const LeaveEvent &e) {
}

} // namespace rack::app
