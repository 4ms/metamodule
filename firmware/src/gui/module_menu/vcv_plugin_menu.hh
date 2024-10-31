#pragma once
#include "console/pr_dbg.hh"
#include "gui/module_menu/base_plugin_menu.hh"
#include "gui/styles.hh"
#include <app/ModuleWidget.hpp>
#include <helpers.hpp>
#include <ui/MenuItem.hpp>

namespace MetaModule
{

struct RackModuleMenu : BasePluginModuleMenu {
	RackModuleMenu(std::shared_ptr<rack::app::ModuleWidget> module_widget)
		: module_widget{module_widget} {
	}

	std::vector<std::string> get_items() override {
		std::vector<std::string> item_strings;

		if (auto mw = module_widget.lock()) {

			// Initialize the first time
			if (!menu_owner) {
				menu_owner = std::make_unique<rack::widget::Widget>();
				refresh_root_menu(mw);
				exited = false;
			}

			if (current_menu) {
				add_menu_items(current_menu->children, item_strings);
			}
		}

		return item_strings;
	}

	void back_event() override {
		if (auto mw = module_widget.lock()) {
			if (current_menu && current_menu->parentMenu) {
				current_menu = current_menu->parentMenu;
				refresh_menu(mw);
				return;
			}
		}
		current_menu = nullptr;
		menu_owner.reset();
		exited = true;
	}

	bool is_done() override {
		return exited;
	}

	void click_item(unsigned idx) override {
		if (!current_menu)
			return;

		if (auto mw = module_widget.lock()) {
			//find the child that was clicked
			for (auto i = 0u; auto child : current_menu->children) {
				if (auto menu_item = dynamic_cast<rack::ui::MenuItem *>(child)) {
					if (i++ == idx) {
						auto has_submenu = click_submenu(menu_item);
						if (!has_submenu) {
							click_action_item(menu_item);
							refresh_menu(mw);
						}
						break;
					}
				}
			}
		}
	}

private:
	bool click_submenu(rack::ui::MenuItem *menu_item) {
		if (auto submenu = menu_item->createChildMenu()) {
			// point child to parent so we can traverse back
			submenu->parentMenu = current_menu;
			// mark which entry created the submenu so we can refresh the submenu
			current_menu->activeEntry = menu_item;
			current_menu->setChildMenu(submenu);
			// Make the submenu our current menu
			current_menu = submenu;
			return true;
		}
		return false;
	}

	void click_action_item(rack::ui::MenuItem *menu_item) {
		current_menu->activeEntry = nullptr;
		current_menu->setChildMenu(nullptr); //deletes any existing childMenu

		menu_item->doAction();
	}

	void refresh_root_menu(std::shared_ptr<rack::app::ModuleWidget> mw) {
		menu_owner->clearChildren();
		auto root_menu = rack::createMenu();
		menu_owner->addChild(root_menu);
		current_menu = root_menu;
		current_menu->parentMenu = nullptr;
		mw->appendContextMenu(current_menu);
	}

	void refresh_menu(std::shared_ptr<rack::app::ModuleWidget> mw) {
		if (current_menu->parentMenu == nullptr) {
			refresh_root_menu(mw);
			return;
		}

		// Refresh the menu via the parent activeEntry item
		if (auto parentMenu = current_menu->parentMenu) {
			if (auto parentItem = dynamic_cast<rack::ui::MenuItem *>(parentMenu->activeEntry)) {
				if (auto refreshed_current_menu = parentItem->createChildMenu()) {
					parentMenu->setChildMenu(refreshed_current_menu);
					refreshed_current_menu->parentMenu = parentMenu;
					current_menu = refreshed_current_menu;
				}
			}
		}
	}

	void add_menu_items(std::list<rack::widget::Widget *> children, std::vector<std::string> &menu) {
		if (module_widget.lock()) {

			unsigned num_children = 0;
			for (auto child : children) {
				if (auto rack_item = dynamic_cast<rack::ui::MenuItem *>(child)) {
					child->step();

					// Reasonable limit to size of menu:
					if (num_children++ < 256) {
						auto &item = menu.emplace_back();
						// Checkmarks go on left side
						if (rack_item->rightText.ends_with(CHECKMARK_STRING))
							item = Gui::yellow_text(CHECKMARK_STRING);

						item += rack_item->text;

						if (rack_item->rightText.length() && !rack_item->rightText.ends_with(CHECKMARK_STRING))
							item += " " + Gui::yellow_text(rack_item->rightText);
					}
				}
			}
		}
	}

	std::weak_ptr<rack::app::ModuleWidget> module_widget{};
	std::unique_ptr<rack::widget::Widget> menu_owner;

	rack::ui::Menu *current_menu{}; //can't use smart pointer because must point to a raw pointer in rack API

	bool exited = false;
};

} // namespace MetaModule
