#include <app/SvgPanel.hpp>

namespace rack::app
{

SvgPanel::SvgPanel()
	: fb(new widget::FramebufferWidget)
	, sw(new widget::SvgWidget)
	, panelBorder(new PanelBorder) {
	addChild(fb);
	fb->addChild(sw);
	fb->addChild(panelBorder);
}

} // namespace rack::app
