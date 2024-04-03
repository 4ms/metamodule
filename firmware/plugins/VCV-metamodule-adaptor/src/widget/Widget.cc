#include "widget/Widget.hpp"

namespace rack::widget
{
void Widget::requestDelete() {
}

void Widget::addChild(Widget *child) {
	if (!child)
		return;
	// children.push_back(child);
	// child->parent = this;
	// if (box.size == math::Vec{}) {
	// 	box.size = child->box.size;
	// 	printf("Updating widget parent box size to child size %f %f\n", box.size.x, box.size.y);
	// }
}
void Widget::addChildBottom(Widget *child) {
	addChild(child);
}
void Widget::addChildBelow(Widget *child, Widget *sibling) {
	addChild(child);
}
void Widget::addChildAbove(Widget *child, Widget *sibling) {
	addChild(child);
}
void Widget::removeChild(Widget *child) {
	if (child) {
		std::erase(children, child);
		// child->parent = nullptr;
	}
}
void Widget::clearChildren() {
	// for (Widget *child : children) {
	// 	if (child)
	// 		delete child;
	// }
	// children.clear();
}

Widget::~Widget() {
	// clearChildren();
}
math::Rect Widget::getChildrenBoundingBox() {
	//TODO:
	return {};
}

math::Rect Widget::getVisibleChildrenBoundingBox() {
	//TODO:
	return {};
}

bool Widget::isDescendantOf(Widget *ancestor) {
	//TODO:
	return false;
}

math::Vec Widget::getRelativeOffset(math::Vec v, Widget *ancestor) {
	//TODO:
	return {};
}

math::Rect Widget::getViewport(math::Rect r) {
	//TODO:
	return {};
}

} // namespace rack::widget
