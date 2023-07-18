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

	void place_at(std::vector<MetaModule::Element> &elements, int id, const MetaModule::Element &el) {
		if (id < 0)
			return;

		// Make sure vector is big enough
		if (id >= (int)elements.size())
			elements.resize(id + 1);

		elements[id] = el;
	}

	void addChild(Widget *w) {
		if (!w)
			return;
		lightElements.push_back(w->element);
		// Makes same assumption as VCV Rack: That we are given ownership of the widget pointer
		delete w;
	}

	void addParam(app::ParamWidget *paramWidget) {
		if (!paramWidget)
			return;
		place_at(paramElements, paramWidget->paramId, paramWidget->element);
		// Makes same assumption as VCV Rack: That we are given ownership of the widget pointer
		delete paramWidget;
	}

	void addInput(app::PortWidget *input) {
		if (!input)
			return;
		place_at(inputElements, input->portId, input->element);
		// Makes same assumption as VCV Rack: That we are given ownership of the widget pointer
		delete input;
	}

	void addOutput(app::PortWidget *output) {
		if (!output)
			return;
		place_at(outputElements, output->portId, output->element);
		// Makes same assumption as VCV Rack: That we are given ownership of the widget pointer
		delete output;
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
