#pragma once
#include <widget/Widget.hpp>


namespace rack {
namespace widget {


/** A Widget that stops propagation of all recursive PositionEvents (such as ButtonEvent) but gives a chance for children to consume first.
Also consumes HoverEvent and ButtonEvent for left-clicks.
*/
struct OpaqueWidget : Widget {
	void onHover(const HoverEvent& e) override;
	void onButton(const ButtonEvent& e) override;
	void onHoverKey(const HoverKeyEvent& e) override;
	void onHoverText(const HoverTextEvent& e) override;
	void onHoverScroll(const HoverScrollEvent& e) override;
	void onDragHover(const DragHoverEvent& e) override;
	void onPathDrop(const PathDropEvent& e) override;
};


} // namespace widget
} // namespace rack
