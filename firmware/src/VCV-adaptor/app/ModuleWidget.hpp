#pragma once
#include "VCV-adaptor/app/menu.hpp"
#include "VCV-adaptor/widgets.hh"

namespace rack
{

struct DrawArgs {};

struct ModuleWidget : Widget {
	engine::Module *module;

	void setModule(engine::Module *) {
	}

	void setPanel(Widget *) {
	}

	void addChild(Widget *) {
	}

	void addParam(Widget *) {
	}

	void addInput(Widget *) {
	}

	void addOutput(Widget *) {
	}

	// ParamWidget *createParam(auto...) {
	// 	return nullptr;
	// }

	// PortWidget *createInput(auto...) {
	// 	return nullptr;
	// }

	// PortWidget *createOutput(auto...) {
	// 	return nullptr;
	// }

	// void *createWidget(auto...) {
	// 	return nullptr;
	// }

	// void *createLight(auto...) {
	// 	return nullptr;
	// }

	virtual void appendContextMenu(ui::Menu *) {
	}

	void addParam(ParamWidget *param) {
	}
	void addInput(PortWidget *input) {
	}
	void addOutput(PortWidget *output) {
	}
	ParamWidget *getParam(int paramId) {
		return nullptr;
	}
	PortWidget *getInput(int portId) {
		return nullptr;
	}
	PortWidget *getOutput(int portId) {
		return nullptr;
	}

	void draw(const DrawArgs &args) {
	}
	void drawLayer(const DrawArgs &args, int layer) {
	}

	virtual void onHover(const HoverEvent &e) {
	}
	virtual void onHoverKey(const HoverKeyEvent &e) {
	}
	virtual void onButton(const ButtonEvent &e) {
	}
	virtual void onDragStart(const DragStartEvent &e) {
	}
	virtual void onDragEnd(const DragEndEvent &e) {
	}
	virtual void onDragMove(const DragMoveEvent &e) {
	}
	virtual void onDragHover(const DragHoverEvent &e) {
	}
};

struct Window {
	Widget *loadSvg(unsigned) {
		return nullptr;
	}
};

struct App {
	Window *window;
};

extern App *APP;

} // namespace rack
