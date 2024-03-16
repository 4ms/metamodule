#pragma once
#include "VCV_adaptor/app/CableWidget.hpp"
#include "VCV_adaptor/componentlibrary.hpp"
#include "VCV_adaptor/history.hpp"
#include "VCV_adaptor/nanovg.h"

namespace rack::app
{

struct RackWidget : widget::OpaqueWidget {
	ParamWidget *touchedParam = nullptr;

	widget::Widget *getModuleContainer() {
		return {};
	}
	widget::Widget *getCableContainer() {
		return {};
	}
	math::Vec getMousePos() {
		return {};
	}

	ParamWidget *getTouchedParam() {
		return touchedParam;
	}
	void setTouchedParam(ParamWidget *pw) {
		touchedParam = pw;
	}

	void step() override {
	}
	void clearCablesOnPort(PortWidget *port) {
	}
	void addCable(CableWidget *cw) {
	}
	void removeCable(CableWidget *cw) {
	}
	CableWidget *getIncompleteCable() {
		return {};
	}
	void setIncompleteCable(CableWidget *cw) {
	}
	CableWidget *releaseIncompleteCable() {
		return {};
	}
	CableWidget *getTopCable(PortWidget *port) {
		return {};
	}
	CableWidget *getCable(int64_t cableId) {
		return {};
	}
	std::vector<CableWidget *> getCompleteCables() {
		return {};
	}
	std::vector<CableWidget *> getCablesOnPort(PortWidget *port) {
		return {};
	}
	std::vector<CableWidget *> getCompleteCablesOnPort(PortWidget *port) {
		return {};
	}

	int getNextCableColorId() {
		return {};
	}
	void setNextCableColorId(int id) {
	}
	NVGcolor getNextCableColor() {
		return {};
	}

	void addModule(ModuleWidget *mw) {
	}
	void addModuleAtMouse(ModuleWidget *mw) {
	}
	void removeModule(ModuleWidget *mw) {
	}
	ModuleWidget *getModule(int64_t moduleId) {
		return nullptr;
	}
	std::vector<ModuleWidget *> getModules() {
		return {};
	}
	bool hasModules() {
		return false;
	}

	bool requestModulePos(ModuleWidget *mw, math::Vec pos) {
		return false;
	}
	void setModulePosNearest(ModuleWidget *mw, math::Vec pos) {
	}
	void setModulePosForce(ModuleWidget *mw, math::Vec pos) {
	}
	void setModulePosSqueeze(ModuleWidget *mw, math::Vec pos) {
	}
	void updateModuleOldPositions() {
	}
};

} // namespace rack::app
