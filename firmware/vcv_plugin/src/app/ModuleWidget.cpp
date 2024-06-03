#include "CoreModules/elements/units.hh"
#include "metamodule/svg.hh"
#include "util/countzip.hh"
#include <app/ModuleWidget.hpp>

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

void ModuleWidget::place_at(std::vector<MetaModule::Element> &elements, int id, const MetaModule::Element &el) {
	if (id < 0)
		return;

	// Make sure vector is big enough
	if (id >= (int)elements.size())
		elements.resize(id + 1);

	elements[id] = el;
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

	// Makes same assumption as VCV Rack: That we are given ownership of the widget pointer
	owned_widgets.push_back(lightWidget);
}

void ModuleWidget::addParam(app::ParamWidget *paramWidget) {
	if (!paramWidget) {
		printf("Error: can't add a null ParamWidget\n");
		return;
	}
	update_coords(paramWidget->box, paramWidget->element);
	place_at(paramElements, paramWidget->paramId, paramWidget->element);

	// Makes same assumption as VCV Rack: That we are given ownership of the widget pointer
	owned_widgets.push_back(paramWidget);
}

void ModuleWidget::addInput(app::PortWidget *input) {
	if (!input) {
		printf("Error: can't add a null input PortWidget\n");
		return;
	}
	update_coords(input->box, input->element);
	place_at(inputElements, input->portId, input->element);

	// Makes same assumption as VCV Rack: That we are given ownership of the widget pointer
	owned_widgets.push_back(input);
}

void ModuleWidget::addOutput(app::PortWidget *output) {
	if (!output) {
		printf("Error: can't add a null output PortWidget\n");
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

void ModuleWidget::update_coords(math::Rect const &box, MetaModule::Element &element) {
	std::visit(
		[box](MetaModule::BaseElement &el) {
			el.x_mm = MetaModule::to_mm(box.pos.x);
			el.y_mm = MetaModule::to_mm(box.pos.y);
			el.coords = MetaModule::Coords::TopLeft;
		},
		element);
}

} // namespace rack::app
