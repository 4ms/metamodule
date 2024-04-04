#pragma once
#include <ui/MenuEntry.hpp>
#include <ui/common.hpp>

namespace rack::ui
{

struct MenuLabel : MenuEntry {
	std::string text;
};

} // namespace rack::ui
