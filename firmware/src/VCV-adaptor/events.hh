#pragma once

namespace rack
{

namespace event
{
struct Event {};
struct DoubleClick {};
struct ActionEvent {};
struct HoverEvent {};
struct HoverKeyEvent {};
struct ButtonEvent {};
struct DragStartEvent {};
struct DragEndEvent {};
struct DragMoveEvent {};
struct DragHoverEvent {};
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

} // namespace rack
