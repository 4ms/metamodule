#include "gui/pages/page_manager.hh"
#include "gui/slsexport/meta5/ui.h"
namespace MetaModule
{
extern "C" {
extern uint32_t LV_EVENT_GET_COMP_CHILD;
}

void PageManager::init() {
	//ui_init();
	page_patchsel.init();
	// mbox.loading_new_patch = false;
	LV_EVENT_GET_COMP_CHILD = lv_event_register_id();
	PageList::request_new_page(page_patchsel);
}

void PageManager::update_current_page() {
	if (auto newpage = PageList::get_requested_page()) {
		cur_page->blur();
		cur_page = newpage.value();
		cur_page->focus();
	}
	cur_page->update();
}

} // namespace MetaModule
