#pragma once
#include <app/ModuleLightWidget.hpp>
#include <app/ParamWidget.hpp>
#include <app/PortWidget.hpp>
#include <app/SvgPanel.hpp>
#include <app/common.hpp>
#include <engine/Module.hpp>
#include <history.hpp>
#include <plugin/Model.hpp>
#include <ui/Menu.hpp>
#include <widget/OpaqueWidget.hpp>

namespace rack::app
{

struct ModuleWidget : widget::Widget {
	~ModuleWidget() override;

	plugin::Model *model = nullptr;

	engine::Module *module = nullptr;
	//TODO:
	// std::unique_ptr<engine::Module> module;

	widget::Widget *panel = nullptr;
	// std::unique_ptr<widget::Widget> panel;

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

	void place_at(std::vector<MetaModule::Element> &elements, int id, const MetaModule::Element &el);
	void populate_elements(std::vector<MetaModule::Element> &elements);

	void addChild(Widget *w);
	void addChild(app::ModuleLightWidget *lightWidget);
	void addParam(ParamWidget *param);
	void addInput(PortWidget *input);
	void addOutput(PortWidget *output);

	ParamWidget *getParam(int paramId);
	PortWidget *getInput(int portId);
	PortWidget *getOutput(int portId);
	std::vector<ParamWidget *> getParams();
	std::vector<PortWidget *> getPorts();
	std::vector<PortWidget *> getInputs();
	std::vector<PortWidget *> getOutputs();

	// clang-format off
	// These are all no-op:
	void draw(const DrawArgs &args) override { }
	void drawLayer(const DrawArgs &args, int layer) override { }
	virtual void appendContextMenu(ui::Menu *menu) {}
	void onHover(const HoverEvent &e) override { }
	void onHoverKey(const HoverKeyEvent &e) override { }
	void onButton(const ButtonEvent &e) override { }
	void onDragStart(const DragStartEvent &e) override { }
	void onDragEnd(const DragEndEvent &e) override { }
	void onDragMove(const DragMoveEvent &e) override { }
	void onDragHover(const DragHoverEvent &e) override { }
	json_t *toJson(){ return {}; }
	void fromJson(json_t *rootJ){}
	bool pasteJsonAction(json_t *rootJ) { return false; }
	void copyClipboard(){}
	bool pasteClipboardAction(){ return {}; }
	void load(std::string filename){}
	void loadAction(std::string filename){}
	void loadTemplate(){}
	void loadDialog(){}
	void save(std::string filename){}
	void saveTemplate(){}
	void saveTemplateDialog(){}
	bool hasTemplate(){ return {}; }
	void clearTemplate(){}
	void clearTemplateDialog(){}
	void saveDialog(){}
	void disconnect(){}
	void resetAction(){}
	void randomizeAction(){}
	void appendDisconnectActions(history::ComplexAction *complexAction){}
	void disconnectAction(){}
	void cloneAction(bool cloneCables = true){}
	void bypassAction(bool bypassed){}
	void removeAction(){}
	void createContextMenu(){}
	math::Vec getGridPosition(){ return {}; }
	void setGridPosition(math::Vec pos){}
	math::Vec getGridSize(){ return {}; }
	math::Rect getGridBox(){ return {}; }
	// clang-format on

private:
	std::vector<MetaModule::Element> paramElements;
	std::vector<MetaModule::Element> inputElements;
	std::vector<MetaModule::Element> outputElements;
	std::vector<MetaModule::Element> lightElements;

	std::list<Widget *> owned_widgets;

	static void update_coords(math::Rect const &box, MetaModule::Element &element);
};

} // namespace rack::app
