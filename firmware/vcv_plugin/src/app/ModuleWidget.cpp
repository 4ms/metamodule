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
	for (auto w : owned_widgets) {
		if (w)
			delete w;
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
	// MetaModule::BaseElement b;
	// b.x_mm = widget->box.pos.x;
	// b.y_mm = widget->box.pos.y;
	// b.coords = MetaModule::Coords::TopLeft;
	// b.width_mm = widget->box.size.x;
	// b.height_mm = widget->box.size.y;
	// b.short_name = getParamName(widget->module, widget->paramId);
	widget->element = MetaModule::make_element(widget, {});
	MetaModule::update_element(widget, getParamName(widget->module, widget->paramId));
}

template<typename ParamT>
void addParamImpl(ModuleWidget *mw, ParamT *paramWidget) {
	if (!paramWidget) {
		pr_err("Error: can't add a null ParamWidget\n");
		return;
	}
	create_element(paramWidget);
	place_at(mw->paramElements, paramWidget->paramId, paramWidget->element);
	mw->owned_widgets.push_back(paramWidget);
}

void ModuleWidget::addParam(app::Knob *paramWidget) {
	pr_dbg("Adding knob\n");
	addParamImpl(this, paramWidget);
}

void ModuleWidget::addParam(app::SvgKnob *paramWidget) {
	auto box = paramWidget->box;
	pr_dbg("addParam(Svgknob) at (%f, %f) size (%f, %f)\n", box.pos.x, box.pos.y, box.size.x, box.size.y);
	addParamImpl(this, paramWidget);
}

void ModuleWidget::addParam(app::ParamWidget *paramWidget) {
	pr_warn("ParamWidget skipped\n");
}

void ModuleWidget::addChild(Widget *w) {
	if (!w)
		return;
	delete w;
}

void ModuleWidget::addChild(app::ModuleLightWidget *lightWidget) {
	if (!lightWidget)
		return;
	update_coords(lightWidget->box, lightWidget->element);
	place_at(lightElements, lightWidget->firstLightId, lightWidget->element);

	owned_widgets.push_back(lightWidget);
}

void ModuleWidget::addInput(app::PortWidget *input) {
	if (!input) {
		pr_err("Error: can't add a null input PortWidget\n");
		return;
	}
	update_coords(input->box, input->element);
	place_at(inputElements, input->portId, input->element);

	owned_widgets.push_back(input);
}

void ModuleWidget::addOutput(app::PortWidget *output) {
	if (!output) {
		pr_err("Error: can't add a null output PortWidget\n");
		return;
	}
	update_coords(output->box, output->element);
	place_at(outputElements, output->portId, output->element);

	// Makes same assumption as VCV Rack: That we are given ownership of the widget pointer
	owned_widgets.push_back(output);
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
