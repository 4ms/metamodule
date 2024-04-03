#pragma once
#include <app/common.hpp>
#include <engine/Module.hpp>
#include <engine/PortInfo.hpp>
#include <ui/Tooltip.hpp>
#include <widget/OpaqueWidget.hpp>

namespace rack
{
namespace app
{

/** Manages an engine::Port on a ModuleWidget. */
struct PortWidget : widget::OpaqueWidget {

	engine::Module *module = nullptr;
	engine::Port::Type type = engine::Port::INPUT;
	int portId = -1;

	engine::Port *getPort() {
		if (!module)
			return nullptr;
		if (type == engine::Port::INPUT)
			return (size_t)portId < module->inputs.size() ? &module->inputs[portId] : nullptr;
		else
			return (size_t)portId < module->outputs.size() ? &module->outputs[portId] : nullptr;
	}

	engine::PortInfo *getPortInfo() {
		if (!module)
			return nullptr;
		if (type == engine::Port::INPUT)
			return (size_t)portId < module->inputInfos.size() ? module->inputInfos[portId].get() : nullptr;
		else
			return (size_t)portId < module->outputInfos.size() ? module->outputInfos[portId].get() : nullptr;
	}

	void createTooltip() {
	}
	void destroyTooltip() {
	}
	void createContextMenu() {
	}
	virtual void appendContextMenu(ui::Menu *menu) {
	}
	void deleteTopCableAction() {
	}
};

} // namespace app
} // namespace rack
