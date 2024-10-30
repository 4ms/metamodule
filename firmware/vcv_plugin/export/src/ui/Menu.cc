#include "console/pr_dbg.hh"
#include <ui/Menu.hpp>

namespace rack::ui
{

Menu::Menu() = default;

Menu::~Menu() {
	setChildMenu(nullptr);
}

void Menu::setChildMenu(Menu *menu) {
	if (childMenu) {
		childMenu->parent->removeChild(childMenu);
		delete childMenu;
		childMenu = nullptr;
	}
	if (menu) {
		childMenu = menu;
		if (!parent)
			pr_err("rack::ui::Menu object has no parent! Memory will be leaked\n");
		else
			parent->addChild(childMenu);
	}
}

void Menu::step() {
}

void Menu::draw(const widget::Widget::DrawArgs &args) {
}

void Menu::onHoverScroll(const widget::Widget::HoverScrollEvent &e) {
}

} // namespace rack::ui
