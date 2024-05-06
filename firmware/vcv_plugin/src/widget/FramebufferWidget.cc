#include "widget/FramebufferWidget.hpp"

namespace rack::widget
{

void FramebufferWidget::addChildBelow(SvgWidget *child, Widget *sibling) {
	//we take ownership
	_bg = child;
	//TODO: set parent's size equal to _bg's size
}

FramebufferWidget::~FramebufferWidget() {
	if (_bg)
		delete _bg;
}

} // namespace rack::widget
