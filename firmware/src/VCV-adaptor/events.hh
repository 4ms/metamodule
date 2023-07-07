#pragma once

namespace rack
{

namespace event
{
struct Event {};
struct DoubleClick {};
struct ActionEvent {};
} // namespace event

using ActionEvent = event::ActionEvent;
using DoubleClick = event::DoubleClick;

} // namespace rack
