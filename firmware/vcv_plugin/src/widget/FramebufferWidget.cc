#include "widget/FramebufferWidget.hpp"

namespace rack::widget
{

void FramebufferWidget::addChildBelow(SvgWidget *child, Widget *sibling) {
	//we take ownership
	_bg = child;
	printf("FramebufferWidget::_bg = %p\n", _bg);
}

FramebufferWidget::~FramebufferWidget() {
	if (_bg)
		delete _bg;
}

} // namespace rack::widget
