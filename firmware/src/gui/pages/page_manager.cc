#include "gui/pages/page_manager.hh"
#include "gui/slsexport/meta5/ui.h"
namespace MetaModule
{

void PageManager::init() {
	PageList::request_new_page(page_patchsel);
}

void PageManager::update_current_page() {
	static unsigned delay_load = 0;
	static PageBase *next_page = nullptr;

	if (auto newpage = PageList::get_requested_page()) {
		cur_page->blur();
		next_page = newpage.value();
		next_page->prepare_focus();

		// TODO: check if LVGL is done rendering before calling focus()
		// For now, a fixed delay works
		delay_load = 1;

	} else if (next_page && delay_load) {
		delay_load--;
		cur_page = next_page;

		if (delay_load == 0)
			cur_page->focus();
	}

	cur_page->update();
}

} // namespace MetaModule
