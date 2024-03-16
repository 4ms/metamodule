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
	engine::Module *module = nullptr;
	widget::Widget *panel = nullptr;
	plugin::Model *model = nullptr;

	std::string svg_filename;

	void setModule(engine::Module *m) {
		module = m;
	}

	void setModel(plugin::Model *m) {
		model = m;
	}

	engine::Module *getModule() {
		return module;
	}

	plugin::Model *getModel() {
		return model;
	}

	void setPanel(app::SvgPanel *newpanel);

	void setPanel(std::shared_ptr<window::Svg> svg);

	widget::Widget *getPanel() {
		return panel;
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
		update_coords(lightWidget->box, lightWidget->element);
		place_at(lightElements, lightWidget->firstLightId, lightWidget->element);

		// Makes same assumption as VCV Rack: That we are given ownership of the widget pointer
		owned_widgets.push_back(lightWidget);
	}

	void addParam(app::ParamWidget *paramWidget) {
		if (!paramWidget) {
			printf("Error: can't add a null ParamWidget\n");
			return;
		}
		update_coords(paramWidget->box, paramWidget->element);
		place_at(paramElements, paramWidget->paramId, paramWidget->element);

		// Makes same assumption as VCV Rack: That we are given ownership of the widget pointer
		owned_widgets.push_back(paramWidget);
	}

	void addInput(app::PortWidget *input) {
		if (!input) {
			printf("Error: can't add a null input PortWidget\n");
			return;
		}
		update_coords(input->box, input->element);
		place_at(inputElements, input->portId, input->element);

		// Makes same assumption as VCV Rack: That we are given ownership of the widget pointer
		owned_widgets.push_back(input);
	}

	void addOutput(app::PortWidget *output) {
		if (!output) {
			printf("Error: can't add a null output PortWidget\n");
			return;
		}
		update_coords(output->box, output->element);
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

	~ModuleWidget() override;

private:
	std::vector<MetaModule::Element> paramElements;
	std::vector<MetaModule::Element> inputElements;
	std::vector<MetaModule::Element> outputElements;
	std::vector<MetaModule::Element> lightElements;

	std::list<Widget *> owned_widgets;

	static void update_coords(math::Rect const &box, MetaModule::Element &element);
};

} // namespace rack::app
