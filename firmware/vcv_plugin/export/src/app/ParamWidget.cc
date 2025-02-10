#include <app/ParamWidget.hpp>
#include <engine/Module.hpp>

namespace rack::app
{

void ParamWidget::initParamQuantity() {
}

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

void ParamWidget::appendContextMenu(ui::Menu *menu) {
}

void ParamWidget::resetAction() {
}

} // namespace rack::app
