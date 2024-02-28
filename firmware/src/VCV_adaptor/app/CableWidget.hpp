#pragma once
#include "VCV_adaptor/componentlibrary.hpp"
#include "VCV_adaptor/nanovg.h"
// #include "VCV_adaptor/app/PortWidget.hpp"
#include "VCV_adaptor/engine/Cable.hpp"

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
