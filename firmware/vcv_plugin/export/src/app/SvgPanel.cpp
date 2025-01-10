#include <app/SvgPanel.hpp>

namespace rack::app
{

void PanelBorder::draw(const DrawArgs &args) {
	//nothing
}

SvgPanel::SvgPanel()
	: fb(new widget::FramebufferWidget)
	, sw(new widget::SvgWidget)
	, panelBorder(new PanelBorder) {
	addChild(fb);
	fb->addChild(sw);
	fb->addChild(panelBorder);
}

void SvgPanel::step() {
	Widget::step();
}

void SvgPanel::setBackground(std::shared_ptr<window::Svg> svg) {
	if (svg == this->svg)
		return;
	this->svg = svg;

	sw->setSvg(svg);

	fb->box.size = sw->box.size;
	panelBorder->box.size = fb->box.size;
	box.size = fb->box.size;

	fb->setDirty();
}

} // namespace rack::app
