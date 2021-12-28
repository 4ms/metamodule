#include "pages/page_manager.hh"

namespace MetaModule
{

void PageManager::init() {
	//54ms for a bunch of pages
	for (auto &page : pages)
		page->init();

	//Todo: page manager doesn't load patches, send a load_patch command via uiaudiomailbox
	//Audio is more suited to load patches, or maybe a 3rd object (patch manager)
	patch_list.set_cur_patch_index(0);
	bool ok = player.load_patch(patch_list.cur_patch());
	if (!ok)
		mbox.set_message("Can't load patch");
	else
		mbox.clear_message();

	mbox.loading_new_patch = false;

	focus_page(PageChangeDirection::Jump);
}

void PageManager::next_page() {
	blur_page();
	cur_page++;
	if (cur_page >= LAST_PAGE)
		cur_page = 0;
	focus_page(PageChangeDirection::Forward);
}
void PageManager::prev_page() {
	blur_page();
	if (cur_page == 0)
		cur_page = LAST_PAGE - 1;
	else
		cur_page--;
	focus_page(PageChangeDirection::Back);
}

void PageManager::jump_to_page(unsigned p) {
	blur_page();
	cur_page = p;
	focus_page(PageChangeDirection::Jump);
}

void PageManager::focus_page(PageChangeDirection dir) {
	pages[cur_page]->focus(dir);
}

void PageManager::blur_page() {
	pages[cur_page]->blur();
}

void PageManager::update_current_page() {
	pages[cur_page]->update();
}

} // namespace MetaModule
