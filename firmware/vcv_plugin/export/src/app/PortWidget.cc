#include <app/PortWidget.hpp>
#include <engine/Module.hpp>

namespace rack::app
{

engine::Port *PortWidget::getPort() {
	if (!module)
		return nullptr;
	if (type == engine::Port::INPUT)
		return (size_t)portId < module->inputs.size() ? &module->inputs[portId] : nullptr;
	else
		return (size_t)portId < module->outputs.size() ? &module->outputs[portId] : nullptr;
}

engine::PortInfo *PortWidget::getPortInfo() {
	if (!module)
		return nullptr;
	if (type == engine::Port::INPUT)
		return (size_t)portId < module->inputInfos.size() ? module->inputInfos[portId] : nullptr;
	else
		return (size_t)portId < module->outputInfos.size() ? module->outputInfos[portId] : nullptr;
}

void PortWidget::createTooltip() {
}

void PortWidget::destroyTooltip() {
}

void PortWidget::createContextMenu() {
}

void PortWidget::appendContextMenu(ui::Menu *menu) {
}

void PortWidget::deleteTopCableAction() {
}

} // namespace rack::app
