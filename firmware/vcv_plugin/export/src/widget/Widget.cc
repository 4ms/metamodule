#include "widget/Widget.hpp"

namespace rack::widget
{
void Widget::setSize(math::Vec size) {
	if (size.equals(box.size))
		return;
	box.size = size;
	// Dispatch Resize event
	ResizeEvent eResize;
	onResize(eResize);
}

void Widget::requestDelete() {
}

void Widget::addChild(Widget *child) {
	if (!child || child->parent != nullptr)
		return;

	child->parent = this;
	children.push_back(child);

	AddEvent eAdd;
	child->onAdd(eAdd);
}

void Widget::addChildBottom(Widget *child) {
	if (!child || child->parent != nullptr)
		return;

	child->parent = this;
	children.push_front(child);

	AddEvent eAdd;
	child->onAdd(eAdd);
}

void Widget::addChildBelow(Widget *child, Widget *sibling) {
	if (!child || child->parent != nullptr)
		return;

	auto it = std::find(children.begin(), children.end(), sibling);
	if (it == children.end())
		return;

	child->parent = this;
	children.insert(it, child);

	AddEvent eAdd;
	child->onAdd(eAdd);
}

void Widget::addChildAbove(Widget *child, Widget *sibling) {
	if (!child || child->parent != nullptr)
		return;

	auto it = std::find(children.begin(), children.end(), sibling);
	if (it == children.end())
		return;

	child->parent = this;
	it++;
	children.insert(it, child);

	AddEvent eAdd;
	child->onAdd(eAdd);
}

void Widget::removeChild(Widget *child) {
	if (!child || child->parent != this)
		return;

	RemoveEvent eRemove;
	child->onRemove(eRemove);

	auto it = std::find(children.begin(), children.end(), child);
	assert(it != children.end());
	children.erase(it);

	child->parent = nullptr;
}

void Widget::clearChildren() {
	// printf("clearChildren() %d children\n", children.size());
	for (Widget *child : children) {
		RemoveEvent eRemove;
		child->onRemove(eRemove);

		child->parent = nullptr;
		// printf("Widget(%p)::clearChildren(): delete %p\n", this, child);
		delete child;
	}
	children.clear();
}

bool Widget::hasChild(Widget *child) {
	if (!child)
		return false;
	auto it = std::find(children.begin(), children.end(), child);
	return (it != children.end());
}

Widget::~Widget() {
	// printf("~Widget() this=%p, parent=%p\n", this, parent);
	if (!parent) {
		clearChildren();
	} else
		printf("Error: Deleting a widget with a parent\n");
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
