#pragma once
#include "CoreModules/moduleFactory.hh"
#include "VCV_adaptor/app/Menu.hpp"
#include "VCV_adaptor/componentlibrary.hpp"
#include "VCV_adaptor/helpers.hpp"
#include "VCV_adaptor/window.hpp"
#include <vector>

namespace rack::app
{

struct ModuleWidget : widget::Widget {
	engine::Module *module;
	widget::Widget panel;
	plugin::Model *model;

	std::string svg_filename;

	void setModule(engine::Module *m) {
		module = m;
	}

	void setModel(plugin::Model *m) {
		model = m;
	}

	void setPanel(Widget *newpanel) {
		panel = *newpanel;
		printf("Using a widget for a panel is not supported\n");
	}

	void setPanel(std::shared_ptr<window::Svg> svg) {
		svg_filename = svg->filename;
	}

	widget::Widget *getPanel() {
		return &panel;
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
		delete w;
	}

	void addChild(app::ModuleLightWidget *lightWidget) {
		if (!lightWidget)
			return;
		place_at(lightElements, lightWidget->firstLightId, lightWidget->element);

		// Makes same assumption as VCV Rack: That we are given ownership of the widget pointer
		owned_widgets.push_back(lightWidget);
	}

	void addParam(app::ParamWidget *paramWidget) {
		if (!paramWidget) {
			printf("Error: can't add a null ParamWidget\n");
			return;
		}
		place_at(paramElements, paramWidget->paramId, paramWidget->element);

		// Makes same assumption as VCV Rack: That we are given ownership of the widget pointer
		owned_widgets.push_back(paramWidget);
	}

	void addInput(app::PortWidget *input) {
		if (!input) {
			printf("Error: can't add a null input PortWidget\n");
			return;
		}
		place_at(inputElements, input->portId, input->element);

		// Makes same assumption as VCV Rack: That we are given ownership of the widget pointer
		owned_widgets.push_back(input);
	}

	void addOutput(app::PortWidget *output) {
		if (!output) {
			printf("Error: can't add a null output PortWidget\n");
			return;
		}
		place_at(outputElements, output->portId, output->element);

		// Makes same assumption as VCV Rack: That we are given ownership of the widget pointer
		owned_widgets.push_back(output);
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

	~ModuleWidget() override {
		// printf("~MW()\n");
		for (auto &w : owned_widgets) {
			delete w;
		}
	}

private:
	std::vector<MetaModule::Element> paramElements;
	std::vector<MetaModule::Element> inputElements;
	std::vector<MetaModule::Element> outputElements;
	std::vector<MetaModule::Element> lightElements;

	std::list<Widget *> owned_widgets;
};

} // namespace rack::app
