#pragma once
#include "VCV-adaptor/nanovg.h"
#include "VCV-adaptor/widgets.hh"
// #include "VCV-adaptor/app/PortWidget.hpp"
#include "VCV-adaptor/engine/Cable.hpp"

namespace rack::app
{

struct PlugWidget;

struct CableWidget : widget::Widget {
	engine::Cable *cable = nullptr;
	NVGcolor color;
	PlugWidget *inputPlug;
	PlugWidget *outputPlug;

	PortWidget *inputPort = nullptr;
	PortWidget *outputPort = nullptr;
	PortWidget *hoveredInputPort = nullptr;
	PortWidget *hoveredOutputPort = nullptr;

	bool isComplete() {
		return {};
	}
	void updateCable() {
	}
	void setCable(engine::Cable *cable) {
	}
	engine::Cable *getCable() {
		return {};
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
	void step() override {
	}
	void draw(const DrawArgs &args) override {
	}
	void drawLayer(const DrawArgs &args, int layer) override {
	}
	engine::Cable *releaseCable() {
		return {};
	}
};

} // namespace rack::app
