#include "pages/page_manager.hh"

namespace MetaModule
{

void PageManager::init() {
	//54ms for a bunch of pages
	page_knobs.init();
	page_module.init();
	page_patch.init();

	//Todo: page manager doesn't load patches, send a load_patch command via uiaudiomailbox
	//Audio is more suited to load patches, or maybe a 3rd object (patch manager)
	patch_list.set_cur_patch_index(0);
	bool ok = player.load_patch(patch_list.get_patch(0));
	if (!ok)
		mbox.append_message("Can't load patch\r\n");
	else
		mbox.append_message("PageManager initialized. Loaded patch\r\n");

	mbox.loading_new_patch = false;

	_focus_page(PageChangeDirection::Jump);
}

void PageManager::next_page() {
	_blur_page();
	switch (cur_page) {
		case PageId::PatchSel:
			cur_page = PageId::Knobs;
			break;
		case PageId::Knobs:
			cur_page = PageId::Module;
			cur_module_idx = 1;
			page_module.load_module_page(info.patch_player.get_module_name(cur_module_idx));
			break;
		case PageId::Module:
			cur_module_idx++;
			if (cur_module_idx >= (unsigned)info.patch_player.get_num_modules()) {
				cur_page = PageId::PatchSel;
			} else {
				page_module.load_module_page(info.patch_player.get_module_name(cur_module_idx));
			}
			break;
	};
	_focus_page(PageChangeDirection::Forward);
}

void PageManager::prev_page() {
	_blur_page();
	switch (cur_page) {
		case PageId::PatchSel:
			cur_page = PageId::Module;
			cur_module_idx = info.patch_player.get_num_modules() - 1;
			page_module.load_module_page(info.patch_player.get_module_name(cur_module_idx));
			break;
		case PageId::Knobs:
			cur_page = PageId::PatchSel;
			break;
		case PageId::Module:
			cur_module_idx--;
			if (cur_module_idx == 0 || cur_module_idx >= (unsigned)info.patch_player.get_num_modules()) {
				cur_module_idx = 1;
				cur_page = PageId::Knobs;
			} else {
				page_module.load_module_page(info.patch_player.get_module_name(cur_module_idx));
			}
			break;
	};
	_focus_page(PageChangeDirection::Back);
}

void PageManager::jump_to_page(PageId page) {
	_blur_page();
	cur_page = page;
	_focus_page(PageChangeDirection::Jump);
}

PageBase *PageManager::_get_cur_page() {
	switch (cur_page) {
		case PageId::PatchSel:
			return &page_patch;
		case PageId::Knobs:
			return &page_knobs;
		case PageId::Module:
			return &page_module;
		default:
			return nullptr;
	};
}

void PageManager::_focus_page(PageChangeDirection dir) {
	if (auto p = _get_cur_page())
		p->focus(dir);
}

void PageManager::_blur_page() {
	if (auto p = _get_cur_page())
		p->blur();
}

void PageManager::update_current_page() {
	if (auto p = _get_cur_page())
		p->update();
}

} // namespace MetaModule
