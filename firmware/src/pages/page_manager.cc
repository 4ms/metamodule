#include "pages/page_manager.hh"

namespace MetaModule
{

void PageManager::init()
{
	patch_list.set_cur_patch_index(0);
	bool ok = player.load_patch(patch_list.cur_patch());
	// if (!ok)
	// 	mbox.set_message("Can't load patch");
	// else
	// 	mbox.clear_message();

	mbox.loading_new_patch = false;

	jump_to_page(Page::PatchSelector);
	display_current_page();
}

void PageManager::next_page()
{
	cur_page = static_cast<Page>(static_cast<unsigned>(cur_page) + 1);
	if (cur_page >= LAST_PAGE)
		cur_page = Page::PatchOverview;
	start_page();
}
void PageManager::prev_page()
{
	if (static_cast<unsigned>(cur_page) == 0)
		cur_page = static_cast<Page>(static_cast<unsigned>(LAST_PAGE) - 1);
	else
		cur_page = static_cast<Page>(static_cast<unsigned>(cur_page) - 1);
	start_page();
}

void PageManager::jump_to_page(Page p)
{
	cur_page = p;
	start_page();
}

void PageManager::start_page()
{
	switch (cur_page) {
		default:
		case PatchOverview:
			// overview_page.start();
			break;

		case ModulesInPatch:
			// modules_in_patch_page.start();
			break;

		case JackMap:
			// jack_map_page.start();
			break;

		case PotMap:
			// knob_map_page.start();
			break;

		case PatchLayout:
			// patch_layout_page.start();
			break;

		case PatchSelector:
			patch_selector_page.start();
			break;

		case DebugInfo:
			// debug_info_page.start();
			break;

		case BouncingBalls:
			// balls_page.start();
			break;
	}
}

void PageManager::display_current_page()
{
	switch (cur_page) {
		default:
		case PatchOverview:
			overview_page.draw();
			break;

		case ModulesInPatch:
			modules_in_patch_page.draw();
			break;

		case JackMap:
			jack_map_page.draw();
			break;

		case PotMap:
			knob_map_page.draw();
			break;

		case PatchLayout:
			patch_layout_page.draw();
			break;

		case PatchSelector:
			patch_selector_page.draw();
			break;

		case DebugInfo:
			debug_info_page.draw();
			break;

		case BouncingBalls:
			balls_page.draw();
			break;
	}
}

} // namespace MetaModule
