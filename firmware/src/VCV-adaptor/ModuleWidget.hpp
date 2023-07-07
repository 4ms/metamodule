#pragma once
#include "VCV-adaptor/widgets.hh"

namespace rack
{

struct ModuleWidget {
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
