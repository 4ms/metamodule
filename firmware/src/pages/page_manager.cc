#include "pages/page_manager.hh"

namespace MetaModule
{

void PageManager::init()
{
	patch_list.set_cur_patch_index(0);
	bool ok = player.load_patch(patch_list.cur_patch());
	if (!ok)
		mbox.set_message("Can't load patch");
	else
		mbox.clear_message();

	mbox.loading_new_patch = false;

	// jump_to_page(Page::PatchOverview);
	// cur_page = Page::PatchOverview;
	focus_page(PageChangeDirection::Jump);
	// update_current_page();
}

void PageManager::next_page()
{
	blur_page();
	cur_page = static_cast<Page>(static_cast<unsigned>(cur_page) + 1);
	if (cur_page >= LAST_PAGE)
		cur_page = static_cast<Page>(0);
	focus_page(PageChangeDirection::Forward);
}
void PageManager::prev_page()
{
	blur_page();
	if (static_cast<unsigned>(cur_page) == 0)
		cur_page = static_cast<Page>(static_cast<unsigned>(LAST_PAGE) - 1);
	else
		cur_page = static_cast<Page>(static_cast<unsigned>(cur_page) - 1);
	focus_page(PageChangeDirection::Back);
}

void PageManager::jump_to_page(Page p)
{
	blur_page();
	cur_page = p;
	focus_page(PageChangeDirection::Jump);
}

void PageManager::focus_page(PageChangeDirection dir)
{
	pages[cur_page]->focus(dir);

	// switch (cur_page) {
	// default:
	// case PatchOverview:
	// 	overview_page.focus(dir);
	// 	break;

	// case ArcTestJQ:
	// 	arc_test_page.focus(dir);
	// 	break;

	// case SketchesTest:
	// 	sketches_test_page.focus(dir);
	// 	break;

	// case ModulesInPatch:
	// modules_in_patch_page.focus(dir);
	// 	break;

	// case JackMap:
	// 	jack_map_page.focus(dir);
	// 	break;

	// case PotMap:
	// knob_map_page.focus(dir);
	// 	break;

	// case PatchLayout:
	// patch_layout_page.focus(dir);
	// 	break;

	// case PatchSelector:
	// 	patch_selector_page.focus(dir);
	// 	break;

	// case DebugInfo:
	// debug_info_page.focus(dir);
	// 	break;

	// case BouncingBalls:
	// 	balls_page.focus(dir);
	// 	break;
	// }
}
void PageManager::blur_page()
{
	pages[cur_page]->blur();

	// switch (cur_page) {
	// 	default:
	// case PatchOverview:
	// 	overview_page.blur();
	// 	break;

	// case ArcTestJQ:
	// 	arc_test_page.blur();
	// 	break;

	// case SketchesTest:
	// 	sketches_test_page.blur();
	// 	break;

	// case ModulesInPatch:
	// modules_in_patch_page.blur();
	// 	break;

	// case JackMap:
	// 	jack_map_page.blur();
	// 	break;

	// case PotMap:
	// knob_map_page.blur();
	// 	break;

	// case PatchLayout:
	// patch_layout_page.blur();
	// 	break;

	// case PatchSelector:
	// 	patch_selector_page.blur();
	// 	break;

	// case DebugInfo:
	// debug_info_page.blur();
	// 	break;

	// case BouncingBalls:
	// 	balls_page.blur();
	// 	break;
	// }
}

void PageManager::update_current_page()
{
	pages[cur_page]->update();
	// switch (cur_page) {
	// 	default:
	// 		// case PatchOverview:
	// 		// 	overview_page.update();
	// 		// 	break;

	// 	case ArcTestJQ:
	// 		arc_test_page.update();
	// 		break;

	// case SketchesTest:
	// 	sketches_test_page.update();
	// 	break;

	// case ModulesInPatch:
	// 	// modules_in_patch_page.draw();
	// 	break;

	// case JackMap:
	// 	jack_map_page.update();
	// 	break;

	// case PotMap:
	// 	// knob_map_page.draw();
	// 	break;

	// case PatchLayout:
	// 	// patch_layout_page.draw();
	// 	break;

	// case PatchSelector:
	// 	patch_selector_page.update();
	// 	break;

	// case DebugInfo:
	// 	// debug_info_page.draw();
	// 	break;

	// case BouncingBalls:
	// 	balls_page.update();
	// 	break;
	// }
}

} // namespace MetaModule
