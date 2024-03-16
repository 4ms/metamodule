#include "app/ModuleWidget.hpp"
#include "svg.hh"

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
	for (auto &w : owned_widgets) {
		delete w;
	}
	if (panel)
		delete panel;
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
