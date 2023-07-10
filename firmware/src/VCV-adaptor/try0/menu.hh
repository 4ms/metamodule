#pragma once

#include <string_view>
namespace rack
{

struct Menu {
	void addChild(Menu *) {
	}
};

struct MenuSeparator : Menu {};

inline Menu *createSubmenuItem(std::string_view, std::string_view, auto) {
	return nullptr;
}

inline Menu *createBoolPtrMenuItem(std::string_view, std::string_view, bool *) {
	return nullptr;
}

} // namespace rack
