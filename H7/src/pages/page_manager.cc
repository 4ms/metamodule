#include "pages/page_manager.hh"
#include "pages/bouncing_balls.hh"
#include "pages/debuginfo.hh"
#include "pages/page_widgets.hh"
#include "pages/patch_overview.hh"

namespace MetaModule
{

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
