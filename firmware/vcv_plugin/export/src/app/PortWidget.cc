#include <app/PortWidget.hpp>
#include <engine/Module.hpp>

namespace rack::app
{

struct PortWidget::Internal {};

PortWidget::PortWidget() = default;
PortWidget::~PortWidget() = default;

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

void PortWidget::deleteTopCableAction() {
}

void PortWidget::step() {
}
void PortWidget::draw(const DrawArgs &args) {
}
void PortWidget::onButton(const ButtonEvent &e) {
}
void PortWidget::onEnter(const EnterEvent &e) {
}
void PortWidget::onLeave(const LeaveEvent &e) {
}
void PortWidget::onDragStart(const DragStartEvent &e) {
}
void PortWidget::onDragEnd(const DragEndEvent &e) {
}
void PortWidget::onDragDrop(const DragDropEvent &e) {
}
void PortWidget::onDragEnter(const DragEnterEvent &e) {
}
void PortWidget::onDragLeave(const DragLeaveEvent &e) {
}

} // namespace rack::app
