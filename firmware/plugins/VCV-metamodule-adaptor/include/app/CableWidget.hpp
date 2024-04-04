#pragma once
#include <app/PortWidget.hpp>
#include <app/common.hpp>
#include <engine/Cable.hpp>
#include <map>
#include <widget/Widget.hpp>

namespace rack::app
{

struct PlugWidget;

struct CableWidget : widget::Widget {
	/** Owned. */
	engine::Cable *cable = nullptr;
	NVGcolor color;
	PlugWidget *inputPlug;
	PlugWidget *outputPlug;

	PortWidget *inputPort = nullptr;
	PortWidget *outputPort = nullptr;
	PortWidget *hoveredInputPort = nullptr;
	PortWidget *hoveredOutputPort = nullptr;

	~CableWidget() override {
		if (cable)
			delete cable;
	}
	bool isComplete() {
		return false;
	}
	void updateCable() {
	}
	void setCable(engine::Cable *cable) {
		this->cable = cable;
	}
	engine::Cable *getCable() {
		return cable;
	}
	math::Vec getInputPos() {
		return {};
	}
	math::Vec getOutputPos() {
		return {};
	}
	void mergeJson(json_t *rootJ) {
	}
	void fromJson(json_t *rootJ) {
	}
	engine::Cable *releaseCable() {
		auto t = cable;
		cable = nullptr;
		return t;
	}
};

} // namespace rack::app
