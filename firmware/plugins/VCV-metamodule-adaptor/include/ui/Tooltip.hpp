#pragma once
#include <ui/common.hpp>
#include <widget/Widget.hpp>

namespace rack::ui
{

struct Tooltip : widget::Widget {
	std::string text;
};

} // namespace rack::ui
