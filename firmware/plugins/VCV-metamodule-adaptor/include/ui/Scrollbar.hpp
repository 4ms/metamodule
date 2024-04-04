#pragma once
#include <ui/common.hpp>
#include <widget/OpaqueWidget.hpp>

namespace rack::ui
{

struct Scrollbar : widget::OpaqueWidget {
	bool vertical = false;
};

} // namespace rack::ui
