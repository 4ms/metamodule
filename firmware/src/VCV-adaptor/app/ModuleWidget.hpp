#pragma once
#include "CoreModules/moduleFactory.hh"
#include "VCV-adaptor/app/menu.hpp"
#include "VCV-adaptor/helpers.hpp"
#include "VCV-adaptor/widgets.hh"
#include "VCV-adaptor/window.hpp"

namespace rack
{

struct ModuleWidget : widget::Widget {
	engine::Module *module;

	void setModule(engine::Module *m) {
		// module = m;
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
		// Copy newly created element into our local vector
		// Keep the params in order
		auto paramId = paramWidget->paramId;
		if (paramId >= 0) {
			if (paramId >= (int)paramElements.size()) {
				paramElements.resize(paramId + 1);
			}
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

	const MetaModule::ModuleInfoView &get_info_view() {
		info.width_hp = 1; //TODO: deprecate width_hp
		info.elements = paramElements;
		//append: + inputElements + outputElements + lightElements;
		return info;
	}

private:
	std::vector<MetaModule::Element> paramElements;
	std::vector<MetaModule::Element> inputElements;
	std::vector<MetaModule::Element> outputElements;
	std::vector<MetaModule::Element> lightElements;
	MetaModule::ModuleInfoView info;
};

} // namespace rack
