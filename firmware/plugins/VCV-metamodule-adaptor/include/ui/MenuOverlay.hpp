#pragma once
#include <ui/common.hpp>
#include <widget/OpaqueWidget.hpp>

namespace rack::ui
{

struct MenuOverlay : widget::OpaqueWidget {
	NVGcolor bgColor;
};

} // namespace rack::ui
