#pragma once
#include "math.hpp"

namespace rack
{

namespace widget
{
struct Widget;
}

enum {
	GLFW_MOUSE_BUTTON_LEFT,
	GLFW_MOUSE_BUTTON_MIDDLE,
	GLFW_MOUSE_BUTTON_RIGHT,
};

namespace event
{

struct Event {
	unsigned button;
	math::Vec mouseDelta;

	void consume(widget::Widget *) const {
	}

	void stopPropagating() const {
	}

	bool isPropagating() const {
		return false;
	}

	void setTarget(widget::Widget *w) const {
	}

	widget::Widget *getTarget() const {
		return nullptr;
	}

	void unconsume() const {
	}

	bool isConsumed() const {
		return false;
	}
};

struct DoubleClick : Event {};
struct ActionEvent : Event {};
struct HoverEvent : Event {};
struct HoverKeyEvent : Event {};
struct ButtonEvent : Event {};
struct DragStartEvent : Event {};
struct DragEndEvent : Event {};
struct DragMoveEvent : Event {};
struct DragHoverEvent : Event {};
struct DoubleClickEvent : Event {};

using Action = ActionEvent;
using DragStart = DragStartEvent;
using DragEnd = DragEndEvent;
using DragMove = DragMoveEvent;
using DragHover = DragHoverEvent;
} // namespace event

using ActionEvent = event::ActionEvent;
using DoubleClick = event::DoubleClick;
using HoverEvent = event::HoverEvent;
using HoverKeyEvent = event::HoverKeyEvent;
using ButtonEvent = event::ButtonEvent;
using DragStartEvent = event::DragStartEvent;
using DragEndEvent = event::DragEndEvent;
using DragMoveEvent = event::DragMoveEvent;
using DragHoverEvent = event::DragHoverEvent;
using DoubleClickEvent = event::DoubleClickEvent;

} // namespace rack
