#include "Widget.hh"
#include "svg.hh"

namespace rack::widget
{
void Widget::addChild(Widget *child) {
	//TODO: take ownership of the pointer, and delete it in ~Widget()
}
void Widget::addChildBottom(Widget *child) {
	//TODO: take ownership of the pointer, and delete it in ~Widget()
}
void Widget::addChildBelow(Widget *child, Widget *sibling) {
	//TODO: take ownership of the pointer, and delete it in ~Widget()
}
void Widget::addChildAbove(Widget *child, Widget *sibling) {
	//TODO: take ownership of the pointer, and delete it in ~Widget()
}
void Widget::removeChild(Widget *child) {
}
void Widget::clearChildren() {
}

void SvgWidget::setSvg(std::shared_ptr<window::Svg> svg) {
	svg_filename = svg->filename;
	box.size = get_svg_size(svg_filename);
	// printf("SvgWidget::setSvg(): svg_filename = %s\n", svg_filename.c_str());
}

void FramebufferWidget::addChildBelow(SvgWidget *child, Widget *sibling) {
	_bg = child;
	//TODO: take ownership of the pointer, and delete it in ~Widget()
}

FramebufferWidget::~FramebufferWidget() {
	if (_bg)
		delete _bg;
}

void TransformWidget::translate(math::Vec delta) {
	printf("translate transformation not supported\n");
}

void TransformWidget::rotate(float angle) {
	printf("rotate transformation not supported\n");
}

void TransformWidget::rotate(float angle, math::Vec origin) {
	printf("rotate transformation not supported\n");
}

void TransformWidget::scale(math::Vec s) {
	printf("scale transformation not supported\n");
}

} // namespace rack::widget
