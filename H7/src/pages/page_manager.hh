#pragma once
#include "pages/bouncing_balls.hh"
#include "pages/debuginfo.hh"
#include "pages/page_widgets.hh"
#include "pages/patch_overview.hh"
#include "pages/patch_selector.hh"
#include "params.hh"
#include "patch_player.hh"
#include "patchlist.hh"
#include "screen_buffer.hh"

namespace MetaModule
{
enum Page : unsigned {
	PatchOverview = 0,
	ModulesInPatch,
	JackMap,
	PotMap,
	PatchLayout,
	PatchSelector,
	DebugInfo,
	BouncingBalls,

	LAST_PAGE,
};

class PageManager {
	BouncingBallsPage balls_page;
	PatchOverviewPage overview_page;
	JackMapPage jack_map_page;
	KnobMapPage knob_map_page;
	PatchLayoutPage patch_layout_page;
	ModulesInPatchPage modules_in_patch_page;
	PatchSelectorPage patch_selector_page;
	DebugInfoPage debug_info_page;

public:
	Page cur_page;

	PageManager(PatchList &pl, PatchPlayer &pp, Params &p, MetaParams &m, ScreenFrameBuffer &s)
		: cur_page{Page::PatchOverview}
		, balls_page{{pl, pp, p, m}, s}
		, overview_page{{pl, pp, p, m}, s}
		, jack_map_page{{pl, pp, p, m}, s}
		, knob_map_page{{pl, pp, p, m}, s}
		, patch_layout_page{{pl, pp, p, m}, s}
		, modules_in_patch_page{{pl, pp, p, m}, s}
		, patch_selector_page{{pl, pp, p, m}, s}
		, debug_info_page{{pl, pp, p, m}, s}
	{}

	void init();
	void next_page();
	void prev_page();
	void jump_to_page(Page p);
	void display_current_page();
};

struct DisplayPage {};

} // namespace MetaModule
