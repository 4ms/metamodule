#include "CoreModules/elements/element_strings.hh"
#include "CoreModules/elements/units.hh"
#include "console/pr_dbg.hh"
#include "make_element_names.hh"
#include "metamodule/make_element.hh"
#include "metamodule/svg.hh"
#include "util/countzip.hh"
#include <app/ModuleWidget.hpp>

namespace MetaModule
{
static void update_element(rack::widget::Widget *widget, std::string_view name);
static void update_coords(rack::math::Rect const &box, MetaModule::Element &element);
} // namespace MetaModule

namespace rack::app
{

void ModuleWidget::setPanel(app::SvgPanel *newpanel) {
	if (!newpanel)
		return;
	if (panel)
		delete panel;
	panel = newpanel;

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

ModuleWidget::~ModuleWidget() {
	printf("~MW() this=%p\n", this);
	for (auto w : owned_widgets) {
		if (!w->parent) {
			printf("~MW(): delete child %p\n", w);
			delete w;
		} else
			pr_err("~MW(): Cannot delete owned widget with a parent\n");
	}
	if (panel)
		delete panel;
}

static void place_at(std::vector<MetaModule::Element> &elements, int id, const MetaModule::Element &el) {
	if (id < 0)
		return;

	// Make sure vector is big enough
	if (id >= (int)elements.size())
		elements.resize(id + 1);

	elements[id] = el;
}

template<typename ParamT>
void create_element(ParamT *widget) {
	widget->element = MetaModule::make_element(widget, {});
	MetaModule::update_element(widget, getParamName(widget->module, widget->paramId));
}

template<typename ParamT>
void addParamImpl(ModuleWidget *mw, ParamT *widget) {
	if (!widget) {
		pr_err("Error: can't add a null ParamWidget\n");
		return;
	}
	create_element<ParamT>(widget);
	place_at(mw->paramElements, widget->paramId, widget->element);
	pr_dbg("MW widget %p = %s\n", widget, MetaModule::base_element(widget->element).short_name.data());
	mw->owned_widgets.push_back(widget);
}

void ModuleWidget::addParam(app::Knob *widget) {
	pr_dbg("addParam(Knob)\n");
	addParamImpl(this, widget);
}

void ModuleWidget::addParam(app::SvgKnob *widget) {
	auto box = widget->box;
	pr_dbg("addParam(Svgknob) at (%f, %f) size (%f, %f)\n", box.pos.x, box.pos.y, box.size.x, box.size.y);
	addParamImpl(this, widget);
}

void ModuleWidget::addParam(app::ParamWidget *widget) {
	pr_warn("addParam(ParamWidget) unknown: skipped\n");
	if (widget)
		owned_widgets.push_back(widget);
}

void ModuleWidget::addChild(Widget *widget) {
	if (widget)
		owned_widgets.push_back(widget);
}

void ModuleWidget::addChild(app::ModuleLightWidget *widget) {
	if (!widget)
		return;
	update_coords(widget->box, widget->element);
	place_at(lightElements, widget->firstLightId, widget->element);

	pr_dbg("MW light widget %p\n", widget);
	owned_widgets.push_back(widget);
}

void ModuleWidget::addInput(app::PortWidget *widget) {
	if (!widget) {
		pr_err("Error: can't add a null input PortWidget\n");
		return;
	}
	update_coords(widget->box, widget->element);
	place_at(inputElements, widget->portId, widget->element);

	owned_widgets.push_back(widget);
}

void ModuleWidget::addOutput(app::PortWidget *widget) {
	if (!widget) {
		pr_err("Error: can't add a null output PortWidget\n");
		return;
	}
	update_coords(widget->box, widget->element);
	place_at(outputElements, widget->portId, widget->element);

	owned_widgets.push_back(widget);
}

void ModuleWidget::addChild(SvgPanel *child) {
	setPanel(child);
}

void ModuleWidget::addChildBottom(SvgPanel *child) {
	addChild(child);
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

namespace MetaModule
{

void update_element(rack::widget::Widget *widget, std::string_view name) {
	std::visit(
		[&name, &widget](MetaModule::BaseElement &el) {
			el.x_mm = MetaModule::to_mm(widget->box.pos.x);
			el.y_mm = MetaModule::to_mm(widget->box.pos.y);
			el.width_mm = MetaModule::to_mm(widget->box.size.x);
			el.height_mm = MetaModule::to_mm(widget->box.size.y);
			el.coords = MetaModule::Coords::TopLeft;
			el.short_name = name;
		},
		widget->element);
}

void update_coords(rack::math::Rect const &box, MetaModule::Element &element) {
	std::visit(
		[box](MetaModule::BaseElement &el) {
			el.x_mm = MetaModule::to_mm(box.pos.x);
			el.y_mm = MetaModule::to_mm(box.pos.y);
			el.width_mm = MetaModule::to_mm(box.size.x);
			el.height_mm = MetaModule::to_mm(box.size.y);
			el.coords = MetaModule::Coords::TopLeft;
		},
		element);
}

} // namespace MetaModule
