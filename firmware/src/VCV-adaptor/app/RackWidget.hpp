#pragma once
#include "VCV-adaptor/nanovg.h"
#include "VCV-adaptor/widgets.hh"
#include "VCV-adaptor/app/CableWidget.hpp"

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
};

} // namespace rack::app
