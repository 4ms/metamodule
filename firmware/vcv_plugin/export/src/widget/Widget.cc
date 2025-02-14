#include "widget/Widget.hpp"

namespace rack::widget
{

math::Rect Widget::getBox() {
	return box;
}

void Widget::setBox(math::Rect box) {
	setPosition(box.pos);
	setSize(box.size);
}

math::Vec Widget::getPosition() {
	return box.pos;
}

void Widget::setPosition(math::Vec pos) {
	box.pos = pos;
}

math::Vec Widget::getSize() {
	return {box.size};
}

void Widget::setSize(math::Vec size) {
	if (size.equals(box.size))
		return;
	box.size = size;
	// Dispatch Resize event
	ResizeEvent eResize;
	onResize(eResize);
}

widget::Widget *Widget::getParent() {
	return parent;
}

bool Widget::isVisible() {
	return visible;
}

void Widget::setVisible(bool visible) {
	this->visible = visible;
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

void Widget::draw(const DrawArgs &args) {
	// Iterate children
	for (Widget *child : children) {
		// Don't draw if invisible
		if (!child->isVisible())
			continue;
		// Don't draw if child is outside clip box
		if (!args.clipBox.intersects(child->box))
			continue;

		drawChild(child, args);
	}
}

void Widget::drawLayer(const DrawArgs &args, int layer) {
	// Iterate children
	for (Widget *child : children) {
		// Don't draw if invisible
		if (!child->isVisible())
			continue;
		// Don't draw if child is outside clip box
		if (!args.clipBox.intersects(child->box))
			continue;

		drawChild(child, args, layer);
	}
}

void Widget::drawChild(Widget *child, const DrawArgs &args, int layer) {
	DrawArgs childArgs = args;
	// Intersect child clip box with self
	childArgs.clipBox = childArgs.clipBox.intersect(child->box);
	// Offset clip box by child pos
	childArgs.clipBox.pos = childArgs.clipBox.pos.minus(child->box.pos);

	nvgSave(args.vg);
	nvgTranslate(args.vg, child->box.pos.x, child->box.pos.y);

	if (layer == 0) {
		child->draw(childArgs);
	} else {
		child->drawLayer(childArgs, layer);
	}

	nvgRestore(args.vg);
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

float Widget::getRelativeZoom(Widget *ancestor) {
	return 1.f;
}

math::Rect Widget::getViewport(math::Rect r) {
	//TODO:
	return {};
}

void Widget::step() {
}

} // namespace rack::widget
