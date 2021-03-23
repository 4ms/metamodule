#include "pages/page_manager.hh"
#include "pages/bouncing_balls.hh"
#include "pages/patch_overview.hh"

namespace MetaModule
{

void PageManager::display_current_page()
{
	switch (cur_page) {
		default:
		case PatchOverview:
			PatchOverviewPage::draw(this);
			screen.fill(bgcolor);
			// draw_bouncing_ball();
			// draw_audio_load();
			// draw_pot_values();
			// draw_patch_name();
			// draw_jack_senses();
			// // draw_knob_map();
			// draw_jack_map();
			break;
		case ModulesInPatch:
			break;
		case JackMap:
			break;
		case PotMap:
			break;
		case PatchLayout:
			break;
		case PatchSelector:
			break;
		case DebugInfo:
			break;
		case BouncingBalls:
			BouncingBallsPage::draw(this);
			break;
	}
}
} // namespace MetaModule
