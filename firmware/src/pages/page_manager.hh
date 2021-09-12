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
	PageWidgets widgets;
	PatchList &patch_list;
	PatchPlayer &player;
	UiAudioMailbox &mbox;

public:
	Page cur_page;

	PageManager(PatchList &pl, PatchPlayer &pp, Params &p, MetaParams &m, UiAudioMailbox &mbox, ScreenFrameBuffer &s)
		: balls_page{{pl, pp, p, m, mbox}, s}
		, overview_page{{pl, pp, p, m, mbox}, s}
		, jack_map_page{{pl, pp, p, m, mbox}, s}
		, knob_map_page{{pl, pp, p, m, mbox}, s}
		, patch_layout_page{{pl, pp, p, m, mbox}, s}
		, modules_in_patch_page{{pl, pp, p, m, mbox}, s}
		, patch_selector_page{{pl, pp, p, m, mbox}, s}
		, debug_info_page{{pl, pp, p, m, mbox}, s}
		, patch_list{pl}
		, player{pp}
		, mbox{mbox}
		, cur_page{Page::PatchOverview}
	{}

	void init();
	void next_page();
	void prev_page();
	void jump_to_page(Page p);
	void display_current_page();
	void set_message(std::string_view message);

private:
	void start_page();
};

struct DisplayPage {};

} // namespace MetaModule
