#include "pages/page_manager.hh"
#include "pages/bouncing_balls.hh"
#include "pages/debuginfo.hh"
#include "pages/page_widgets.hh"
#include "pages/patch_overview.hh"
#include "pages/patch_selector.hh"

namespace MetaModule
{

void PageManager::init()
{
	cur_page = Page::PatchOverview;
	display_current_page();
}

void PageManager::next_page()
{
	cur_page = static_cast<Page>(static_cast<unsigned>(cur_page) + 1);
	if (cur_page >= LAST_PAGE)
		cur_page = PatchOverview;
}
void PageManager::prev_page()
{
	if (static_cast<unsigned>(cur_page) == 0)
		cur_page = static_cast<Page>(static_cast<unsigned>(LAST_PAGE) - 1);
	else
		cur_page = static_cast<Page>(static_cast<unsigned>(cur_page) - 1);
}

void PageManager::jump_to_page(Page p)
{
	cur_page = p;
}

void PageManager::display_current_page()
{
	switch (cur_page) {
		default:
		case PatchOverview:
			PatchOverviewPage::draw(this);
			break;

		case ModulesInPatch:
			ModulesInPatchPage::draw(this);
			break;

		case JackMap:
			JackMapPage::draw(this);
			break;

		case PotMap:
			KnobMapPage::draw(this);
			break;

		case PatchLayout:
			PatchLayoutPage::draw(this);
			break;

		case PatchSelector:
			PatchSelectorPage::draw(this);
			break;

		case DebugInfo:
			DebugInfoPage::draw(this);
			break;

		case BouncingBalls:
			BouncingBallsPage::draw(this);
			break;
	}
}

} // namespace MetaModule
