#pragma once
#include "VCV-adaptor/app/menu.hpp"
#include "VCV-adaptor/widgets.hh"
#include "VCV-adaptor/window.hpp"
#include "helpers.hpp"

namespace rack
{

struct ModuleWidget : widget::Widget {
	engine::Module *module;

	void setModule(engine::Module *) {
	}

	void setPanel(Widget *panel) {
	}

	void setPanel(window::Svg *svg) {
	}

	void addChild(Widget *) {
	}

	void addParam(app::ParamWidget *param) {
	}

	void addInput(app::PortWidget *input) {
	}

	void addOutput(app::PortWidget *output) {
	}

	virtual void appendContextMenu(ui::Menu *) {
	}

	app::ParamWidget *getParam(int paramId) {
		return nullptr;
	}

	app::PortWidget *getInput(int portId) {
		return nullptr;
	}

	app::PortWidget *getOutput(int portId) {
		return nullptr;
	}

	void draw(const DrawArgs &args) override {
	}

	void drawLayer(const DrawArgs &args, int layer) override {
	}
};

} // namespace rack
