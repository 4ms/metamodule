#include <app/ModuleLightWidget.hpp>

namespace rack::app
{

engine::Light *ModuleLightWidet::getLight(int colorId) {
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

} // namespace rack::app
