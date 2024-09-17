#include "CoreModules/elements/element_counter.hh"
#include "console/pr_dbg.hh"
#include "metamodule/svg.hh"
#include "module_widget_adaptor.hh"
#include "util/countzip.hh"
#include "util/zip.hh"
#include <app/ModuleWidget.hpp>

static constexpr inline bool LogWidgetPlacements = false;

static void log_widget(std::string_view preface, rack::widget::Widget const *widget);

namespace rack::app
{

ModuleWidget::ModuleWidget() {
	adaptor = std::make_unique<MetaModule::ModuleWidgetAdaptor>();
}

ModuleWidget::~ModuleWidget() = default;

void ModuleWidget::setPanel(app::SvgPanel *newpanel) {
	if (!newpanel)
		return;
	panel.reset(newpanel);

	if (newpanel->svg) {
		svg_filename = newpanel->svg->filename;
		box.size = get_svg_size(svg_filename);
	}
}

void ModuleWidget::setPanel(std::shared_ptr<window::Svg> svg) {
	auto *panel = new SvgPanel;
	panel->setBackground(svg);
	setPanel(panel);
}

widget::Widget *ModuleWidget::getPanel() {
	return panel.get();
}

//
// Params
//

void ModuleWidget::addParam(app::Knob *widget) {
	log_widget("addParam(Knob)", widget);
	adaptor->addParam(widget);
	Widget::addChild(widget);
}

void ModuleWidget::addParam(app::SvgKnob *widget) {
	log_widget("addParam(SvgKnob)", widget);
	adaptor->addParam(widget);
	Widget::addChild(widget);
}

void ModuleWidget::addParam(rack::componentlibrary::Rogan *widget) {
	log_widget("addParam(Rogan)", widget);
	adaptor->addParam(widget);
	Widget::addChild(widget);
}

void ModuleWidget::addParam(app::SliderKnob *widget) {
	log_widget("addParam(SliderKnob)", widget);
	adaptor->addParam(widget);
	Widget::addChild(widget);
}

void ModuleWidget::addParam(app::SvgSlider *widget) {
	log_widget("addParam(SvgSlider)", widget);
	// Modify the widget's box to match the background
	// widget->box.pos = widget->box.pos + widget->background->box.pos;
	adaptor->addParam(widget);
	Widget::addChild(widget);
}

void ModuleWidget::addParam(app::SvgSwitch *widget) {
	log_widget("addParam(SvgSwitch)", widget);
	adaptor->addParam(widget);
	Widget::addChild(widget);
}

void ModuleWidget::addParam(app::ParamWidget *widget) {
	// Most-specialized to least:
	if (auto w = dynamic_cast<rack::componentlibrary::Rogan *>(widget))
		addParam(w);
	else if (auto w = dynamic_cast<app::SvgKnob *>(widget))
		addParam(w);
	else if (auto w = dynamic_cast<app::SvgSlider *>(widget))
		addParam(w);
	else if (auto w = dynamic_cast<app::SliderKnob *>(widget))
		addParam(w);
	else if (auto w = dynamic_cast<app::Knob *>(widget))
		addParam(w);
	else if (auto w = dynamic_cast<app::SvgSwitch *>(widget))
		addParam(w);
	else {
		log_widget("addParam(unknown ParamWidget)", widget);
		Widget::addChild(widget);
	}
}

//
// Param + Light
//

void ModuleWidget::addLightSwitch(app::SvgSwitch *widget, app::ModuleLightWidget *light) {
	log_widget("addLightSwitch()", widget);
	adaptor->addLightParam(widget, light);
	Widget::addChild(widget);
}

void ModuleWidget::addLightSlider(app::SvgSlider *widget, app::ModuleLightWidget *light) {
	log_widget("addLightSwitch()", widget);
	adaptor->addLightParam(widget, light);
	Widget::addChild(light);
}

//
// Lights
//

void ModuleWidget::addChild(app::ModuleLightWidget *widget) {
	log_widget("addChild(ModuleLightWidget)", widget);
	adaptor->addLight(widget);
	Widget::addChild(widget);
}

void ModuleWidget::addSvgLight(std::string_view image, app::ModuleLightWidget *widget) {
	log_widget("addSvgLight()", widget);
	adaptor->addSvgLight(widget, image);
	Widget::addChild(widget);
}

//
// Ports
//

void ModuleWidget::addInput(app::PortWidget *widget) {
	if (auto w = dynamic_cast<app::SvgPort *>(widget)) {
		addInput(w);
	} else {
		log_widget("addInput(PortWidget)", widget);
		adaptor->addInput(widget);
		Widget::addChild(widget);
	}
}

void ModuleWidget::addInput(app::SvgPort *widget) {
	log_widget("addOutput(SvgPort)", widget);
	adaptor->addInput(widget);
	Widget::addChild(widget);
}

void ModuleWidget::addOutput(app::PortWidget *widget) {
	if (auto w = dynamic_cast<app::SvgPort *>(widget)) {
		addOutput(w);
	} else {
		log_widget("addOutput(PortWidget)", widget);
		adaptor->addOutput(widget);
		Widget::addChild(widget);
	}
}

void ModuleWidget::addOutput(app::SvgPort *widget) {
	log_widget("addOutput(SvgPort)", widget);
	adaptor->addOutput(widget);
	Widget::addChild(widget);
}

//
// Image-only
//

void ModuleWidget::addChild(app::SvgScrew *widget) {
	log_widget("addChild(SvgScrew)", widget);
	Widget::addChild(widget);
}

void ModuleWidget::addChild(Widget *widget) {
	log_widget("Skipped: addChild(unknown Widget)", widget);
	Widget::addChild(widget);
}

void ModuleWidget::addChild(widget::MetaModuleDisplay *widget) {
	adaptor->addTextDisplay(widget);
	Widget::addChild(widget);
}

void ModuleWidget::addChild(widget::SvgWidget *widget) {
	log_widget("addChild(SvgWidget)", widget);
	adaptor->addImage(widget);
	Widget::addChild(widget);
}

void ModuleWidget::addChild(app::SvgButton *widget) {
	log_widget("addChild(SvgButton)", widget);
	widget->sw->box.pos = widget->box.pos;
	adaptor->addImage(widget->sw);
	Widget::addChild(widget);
}

//
// Panel
//

void ModuleWidget::addChild(SvgPanel *child) {
	setPanel(child);
}

void ModuleWidget::addChildBottom(SvgPanel *child) {
	setPanel(child);
}

template<class T, typename F>
T *getFirstDescendantOfTypeWithCondition(widget::Widget *w, F f) {
	T *t = dynamic_cast<T *>(w);
	if (t && f(t))
		return t;

	for (widget::Widget *child : w->children) {
		T *foundT = getFirstDescendantOfTypeWithCondition<T>(child, f);
		if (foundT)
			return foundT;
	}
	return nullptr;
}

ParamWidget *ModuleWidget::getParam(int paramId) {
	return getFirstDescendantOfTypeWithCondition<ParamWidget>(
		this, [&](ParamWidget *pw) -> bool { return pw->paramId == paramId; });
}

PortWidget *ModuleWidget::getInput(int portId) {
	return getFirstDescendantOfTypeWithCondition<PortWidget>(
		this, [&](PortWidget *pw) -> bool { return pw->type == engine::Port::INPUT && pw->portId == portId; });
}

PortWidget *ModuleWidget::getOutput(int portId) {
	return getFirstDescendantOfTypeWithCondition<PortWidget>(
		this, [&](PortWidget *pw) -> bool { return pw->type == engine::Port::OUTPUT && pw->portId == portId; });
}

template<class T, typename F>
void doIfTypeRecursive(widget::Widget *w, F f) {
	T *t = dynamic_cast<T *>(w);
	if (t)
		f(t);

	for (widget::Widget *child : w->children) {
		doIfTypeRecursive<T>(child, f);
	}
}

std::vector<ParamWidget *> ModuleWidget::getParams() {
	std::vector<ParamWidget *> pws;
	doIfTypeRecursive<ParamWidget>(this, [&](ParamWidget *pw) { pws.push_back(pw); });
	return pws;
}

std::vector<PortWidget *> ModuleWidget::getPorts() {
	std::vector<PortWidget *> pws;
	doIfTypeRecursive<PortWidget>(this, [&](PortWidget *pw) { pws.push_back(pw); });
	return pws;
}

std::vector<PortWidget *> ModuleWidget::getInputs() {
	std::vector<PortWidget *> pws;
	doIfTypeRecursive<PortWidget>(this, [&](PortWidget *pw) {
		if (pw->type == engine::Port::INPUT)
			pws.push_back(pw);
	});
	return pws;
}

std::vector<PortWidget *> ModuleWidget::getOutputs() {
	std::vector<PortWidget *> pws;
	doIfTypeRecursive<PortWidget>(this, [&](PortWidget *pw) {
		if (pw->type == engine::Port::OUTPUT)
			pws.push_back(pw);
	});
	return pws;
}

} // namespace rack::app

static void log_widget(std::string_view preface, rack::widget::Widget const *widget) {
	if (!widget)
		pr_err("%s: Null widget\n", preface.data());

	if constexpr (LogWidgetPlacements) {
		auto box = widget->box;
		pr_trace("%s at (%f, %f) size (%f, %f)\n", preface.data(), box.pos.x, box.pos.y, box.size.x, box.size.y);
	}
}
