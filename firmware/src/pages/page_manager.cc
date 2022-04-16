#include "pages/page_manager.hh"

namespace MetaModule
{

void PageManager::init() {
	//54ms for a bunch of pages
	// page_knobs.init();
	page_module.init();
	page_patchsel.init();
	page_patchview.init();

	//Todo: page manager doesn't load patches, send a load_patch command via uiaudiomailbox
	//Audio is more suited to load patches, or maybe a 3rd object (patch manager)
	patch_list.set_cur_patch_index(0);
	bool ok = player.load_patch(patch_list.get_patch(0));
	if (!ok)
		mbox.append_message("Can't load patch\r\n");
	else
		mbox.append_message("PageManager initialized. Loaded patch\r\n");

	mbox.loading_new_patch = false;

	PageList::request_new_page(page_patchsel);
}

// 	page_module.load_module_page(info.patch_player.get_module_name(cur_module_idx));

void PageManager::update_current_page() {
	if (auto newpage = PageList::get_requested_page()) {
		cur_page = newpage.value();
		cur_page->focus();
	}
	cur_page->update();
}

} // namespace MetaModule
