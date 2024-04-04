#pragma once
#include <ui/Scrollbar.hpp>
#include <ui/common.hpp>
#include <widget/OpaqueWidget.hpp>

namespace rack::ui
{

struct ScrollWidget : widget::OpaqueWidget {
	widget::Widget *container{};
	Scrollbar *horizontalScrollbar{};
	Scrollbar *verticalScrollbar{};

	math::Vec offset;
	math::Rect containerBox;
	bool hideScrollbars = false;

	math::Vec getScrollOffset() {
		return offset;
	}
	void scrollTo(math::Rect r) {
	}
	math::Rect getContainerOffsetBound() {
		return {};
	}
	math::Vec getHandleOffset() {
		return {};
	}
	math::Vec getHandleSize() {
		return {};
	}
	bool isScrolling() {
		return {};
	}
};

} // namespace rack::ui
