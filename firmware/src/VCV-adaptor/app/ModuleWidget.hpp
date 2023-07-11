#pragma once
#include "VCV-adaptor/app/menu.hpp"
#include "VCV-adaptor/widgets.hh"

namespace rack
{

struct ParamWidget {};
struct PortWidget {};
struct DrawArgs {};

struct ModuleWidget {
	engine::Module *module;

	void setModule(void *) {
	}

	void setPanel(unsigned) {
	}

	void addChild(unsigned) {
	}

	void addParam(unsigned) {
	}

	void addInput(unsigned) {
	}

	void addOutput(unsigned) {
	}

	template<typename T>
	unsigned createParam(auto...) {
		return 0;
	}

	template<typename T>
	unsigned createInput(math::Vec, void *, unsigned) {
		return 0;
	}

	template<typename T>
	unsigned createOutput(auto...) {
		return 0;
	}

	template<typename T>
	unsigned createWidget(auto...) {
		return 0;
	}

	template<typename T>
	unsigned createLight(auto...) {
		return 0;
	}

	virtual void appendContextMenu(Menu *) {
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
	unsigned loadSvg(unsigned) {
		return 0;
	}
};

struct App {
	Window *window;
};

extern App *APP;

} // namespace rack
