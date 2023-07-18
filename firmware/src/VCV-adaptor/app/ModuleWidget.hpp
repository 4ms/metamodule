#pragma once
#include "CoreModules/moduleFactory.hh"
#include "VCV-adaptor/app/Menu.hpp"
#include "VCV-adaptor/helpers.hpp"
#include "VCV-adaptor/widgets.hh"
#include "VCV-adaptor/window.hpp"
#include <vector>

namespace rack
{

struct ModuleWidget : widget::Widget {
	engine::Module *module;

	void setModule(engine::Module *m) {
		module = m;
	}

	void setPanel(Widget *panel) {
	}

	void setPanel(std::shared_ptr<window::Svg> svg) {
	}

	void addChild(Widget *w) {
		// Check if it's a light
		//Ignore all others(?)

		// delete w;
	}

	void addParam(app::ParamWidget *paramWidget) {
		// Makes same assumption as VCV Rack: That we are given ownership of the widget pointer
		auto paramId = paramWidget->paramId;
		if (paramId >= 0) {
			// Make sure vector is big enough
			if (paramId >= (int)paramElements.size()) {
				paramElements.resize(paramId + 1);
			}
			// Copy newly created element into our local vector
			paramElements[paramId] = paramWidget->element;
		}
		delete paramWidget;
	}

	void addInput(app::PortWidget *input) {
		// delete input;
	}

	void addOutput(app::PortWidget *output) {
		// delete output;
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

	void populate_elements(std::vector<MetaModule::Element> &elements) {
		elements.clear();
		elements.reserve(paramElements.size() + inputElements.size() + outputElements.size() + lightElements.size());
		elements.insert(elements.end(), paramElements.begin(), paramElements.end());
		elements.insert(elements.end(), inputElements.begin(), inputElements.end());
		elements.insert(elements.end(), outputElements.begin(), outputElements.end());
		elements.insert(elements.end(), lightElements.begin(), lightElements.end());
	}

private:
	std::vector<MetaModule::Element> paramElements;
	std::vector<MetaModule::Element> inputElements;
	std::vector<MetaModule::Element> outputElements;
	std::vector<MetaModule::Element> lightElements;
};

} // namespace rack
