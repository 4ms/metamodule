#pragma once
#include <Quantity.hpp>
#include <context.hpp>
#include <ui/common.hpp>
#include <widget/OpaqueWidget.hpp>

namespace rack::ui
{

struct Slider : widget::OpaqueWidget {
	Quantity *quantity = nullptr;
};

} // namespace rack::ui
