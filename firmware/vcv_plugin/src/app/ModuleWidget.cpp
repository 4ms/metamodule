#include "add_widget_helpers.hh"
#include "console/pr_dbg.hh"
#include "metamodule/svg.hh"
#include "util/countzip.hh"
#include <app/ModuleWidget.hpp>

static void log_widget(std::string_view preface, rack::widget::Widget const *widget);

namespace rack::app
{

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

ModuleWidget::~ModuleWidget() = default;

void ModuleWidget::addParam(app::Knob *widget) {
	log_widget("addParam(Knob)", widget);
	MetaModule::addParamImpl(this, widget);
}

void ModuleWidget::addParam(app::SvgKnob *widget) {
	log_widget("addParam(SvgKnob)", widget);
	MetaModule::addParamImpl(this, widget);
}

void ModuleWidget::addParam(app::SliderKnob *widget) {
	log_widget("addParam(SliderKnob)", widget);
	MetaModule::addParamImpl(this, widget);
}

void ModuleWidget::addParam(app::SvgSlider *widget) {
	log_widget("addParam(SvgSlider)", widget);
	MetaModule::addParamImpl(this, widget);
	// TODO: handle switches
}

void ModuleWidget::addParam(app::SvgSwitch *widget) {
	log_widget("addParam(SvgSwitch)", widget);
	MetaModule::addParamImpl(this, widget);
}

void ModuleWidget::addParam(app::ParamWidget *widget) {
	log_widget("Skipped: addParam(unknown ParamWidget)", widget);
	Widget::addChild(widget);
}

void ModuleWidget::addChild(Widget *widget) {
	log_widget("Skipped: addChild(unknown Widget)", widget);
	Widget::addChild(widget);
}

void ModuleWidget::addChild(app::ModuleLightWidget *widget) {
	log_widget("addChild(ModuleLightWidget)", widget);
	MetaModule::addLightImpl(this, widget);
}

void ModuleWidget::addInput(app::PortWidget *widget) {
	log_widget("addInput(PortWidget)", widget);
	MetaModule::addInputImpl(this, widget);
}

void ModuleWidget::addInput(app::SvgPort *widget) {
	log_widget("addOutput(SvgPort)", widget);
	MetaModule::addInputImpl(this, widget);
}

void ModuleWidget::addOutput(app::PortWidget *widget) {
	log_widget("addOutput(PortWidget)", widget);
	MetaModule::addOutputImpl(this, widget);
}

void ModuleWidget::addOutput(app::SvgPort *widget) {
	log_widget("addOutput(SvgPort)", widget);
	MetaModule::addOutputImpl(this, widget);
}

void ModuleWidget::addLightSwitch(app::SvgSwitch *widget, app::ModuleLightWidget *light) {
	addParam(widget);
	light->box = widget->box;
	addChild(light);
}

void ModuleWidget::addLightSlider(app::SvgSlider *widget, app::ModuleLightWidget *light) {
	addParam(widget);
	light->box = widget->box;
	// light->parent = nullptr;
	addChild(light);
}

void ModuleWidget::addChild(SvgPanel *child) {
	setPanel(child);
}

void ModuleWidget::addChildBottom(SvgPanel *child) {
	setPanel(child);
}

app::ParamWidget *ModuleWidget::getParam(int paramId) {
	return nullptr;
}

app::PortWidget *ModuleWidget::getInput(int portId) {
	return nullptr;
}

app::PortWidget *ModuleWidget::getOutput(int portId) {
	return nullptr;
}

void ModuleWidget::populate_elements(std::vector<MetaModule::Element> &elements,
									 std::vector<ElementCount::Indices> &indices) {
	elements.clear();
	indices.clear();

	auto num_elems = paramElements.size() + inputElements.size() + outputElements.size() + lightElements.size();
	elements.reserve(num_elems);
	indices.reserve(num_elems);

	elements.insert(elements.end(), paramElements.begin(), paramElements.end());
	elements.insert(elements.end(), inputElements.begin(), inputElements.end());
	elements.insert(elements.end(), outputElements.begin(), outputElements.end());
	elements.insert(elements.end(), lightElements.begin(), lightElements.end());

	auto None = ElementCount::Indices::NoElementMarker;

	for (auto [i, el] : enumerate(paramElements))
		indices.push_back({.param_idx = (uint8_t)i, .light_idx = None, .input_idx = None, .output_idx = None});

	for (auto [i, el] : enumerate(inputElements))
		indices.push_back({.param_idx = None, .light_idx = None, .input_idx = (uint8_t)i, .output_idx = None});

	for (auto [i, el] : enumerate(outputElements))
		indices.push_back({.param_idx = None, .light_idx = None, .input_idx = None, .output_idx = (uint8_t)i});

	for (auto [i, el] : enumerate(lightElements))
		indices.push_back({.param_idx = None, .light_idx = (uint8_t)i, .input_idx = None, .output_idx = None});
}

std::vector<ParamWidget *> ModuleWidget::getParams() {
	return {};
}
std::vector<PortWidget *> ModuleWidget::getPorts() {
	return {};
}
std::vector<PortWidget *> ModuleWidget::getInputs() {
	return {};
}
std::vector<PortWidget *> ModuleWidget::getOutputs() {
	return {};
}
} // namespace rack::app

static void log_widget(std::string_view preface, rack::widget::Widget const *widget) {
	if (!widget)
		pr_err("%s: Null widget\n", preface.data());
	auto box = widget->box;
	pr_dbg("%s at (%f, %f) size (%f, %f)\n", preface.data(), box.pos.x, box.pos.y, box.size.x, box.size.y);
}
