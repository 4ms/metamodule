#include "pages/page_manager.hh"

namespace MetaModule
{

void PageManager::init() {
	page_patchsel.init();

	//Todo: page manager doesn't load patches, send a load_patch command via uiaudiomailbox
	//Audio is more suited to load patches, or maybe a 3rd object (patch manager)
	unsigned patchid = 7;
	patch_list.set_cur_patch_index(patchid);
	auto patchname = patch_list.get_patch_name(patchid);
	printf("Attempting load patch %d, %s\n", patchid, patchname.data());

	bool ok = player.load_patch(patch_list.get_patch(patchid));
	if (!ok)
		printf("Failed to load patch\n");
	// mbox.append_message("Can't load patch\r\n");
	else
		printf("PageManager initialized. Loaded patch\r\n");
	// mbox.append_message("PageManager initialized. Loaded patch\r\n");

	mbox.loading_new_patch = false;

	PageList::request_new_page(page_patchsel);
}

void PageManager::update_current_page() {
	if (auto newpage = PageList::get_requested_page()) {
		cur_page = newpage.value();
		cur_page->focus();
	}
	cur_page->update();
}

} // namespace MetaModule
