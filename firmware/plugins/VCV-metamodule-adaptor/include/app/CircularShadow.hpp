#pragma once
#include <app/common.hpp>
#include <widget/TransparentWidget.hpp>

namespace rack
{
namespace app
{

struct CircularShadow : widget::TransparentWidget {
	float blurRadius;
	float opacity;
};

} // namespace app
} // namespace rack
