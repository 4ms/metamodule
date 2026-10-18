#include "gui/helpers/screensaver_display.hh"
#include "gui/pages/module_view/module_view.hh"
#include <limits>

namespace MetaModule
{

bool ModuleViewPage::is_assigned_screensaver(DrawnElement const &drawn_element) const {
	return fullscreen_display(drawn_element.element) &&
		   patch->is_screensaver_display(this_module_id, drawn_element.gui_element.idx.light_idx);
}

void ModuleViewPage::assign_screensaver(DrawnElement const &drawn_element) {
	if (!fullscreen_display(drawn_element.element))
		return;

	patch->set_screensaver_display(this_module_id, drawn_element.gui_element.idx.light_idx);
	patches.mark_view_patch_modified();

	notify_queue.put(
		{screensaver_set_message(*patch, this_module_id, drawn_element.element), Notification::Priority::Status, 2000});

	if (choosing_screensaver)
		exit_choose_screensaver();
	else
		populate_roller();
}

void ModuleViewPage::remove_screensaver() {
	patch->clear_screensaver_display();
	patches.mark_view_patch_modified();

	notify_queue.put({"Screensaver removed", Notification::Priority::Status, 1500});

	populate_roller();
}

// List only this module's displays (like patching a cable lists only jacks)
void ModuleViewPage::enter_choose_screensaver() {
	choosing_screensaver = true;
	current_group.reset();

	// Start on the first display
	args.element_indices = std::nullopt;
	cur_selected = std::numeric_limits<decltype(cur_selected)>::max();

	change_roller_listing();

	notify_queue.put({"Select a display to use as the screensaver", Notification::Priority::Status, 2000});
}

void ModuleViewPage::exit_choose_screensaver() {
	choosing_screensaver = false;
	current_group.reset();

	change_roller_listing();
}

// Re-list the roller and button bar after entering or leaving choose mode
void ModuleViewPage::change_roller_listing() {
	// Focus the roller before hiding the focused button: otherwise LVGL moves focus
	// along the buttons, and roller_focus_cb would act on the old roller rows
	last_button_focused = nullptr;
	lv_group_focus_obj(ui_ElementRoller);

	update_button_bar();
	populate_roller();

	for (auto i = 0u; i < element_highlights.size(); i++)
		unhighlight_element(i);
	highlight_row(cur_selected);
}

} // namespace MetaModule
