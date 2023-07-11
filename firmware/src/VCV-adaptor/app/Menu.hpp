#pragma once

namespace rack::ui
{
struct Menu {
	void addChild(Menu *) {
	}
};

struct MenuSeparator : Menu {};

struct MenuLabel : Menu {};
struct MenuItem : Menu {};
} // namespace rack::ui
