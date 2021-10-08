#pragma once
// #include "pages/bouncing_balls.hh"
// #include "pages/debuginfo.hh"
// #include "pages/page_widgets.hh"
#include "pages/arc_test_jq.hh"
// #include "pages/patch_overview.hh"
// #include "pages/patch_selector.hh"
// #include "pages/sketches_test_jq.hh"
#include "params.hh"
#include "patch_player.hh"
#include "patchlist.hh"
// #include "screen_buffer.hh"

namespace MetaModule
{
enum Page : unsigned {
	// PatchOverview = 0,
	// PatchSelector,
	// BouncingBalls,
	// ModulesInPatch,
	// JackMap,
	// PotMap,
	// PatchLayout,
	// DebugInfo,
	ArcTestJQ,
	// SketchesTest,

	LAST_PAGE,
};

class PageManager {
	PatchInfo info;

	// BouncingBallsPage balls_page;
	// PatchOverviewPage overview_page;
	// JackMapPage jack_map_page;
	// PatchSelectorPage patch_selector_page;
	ArcTestJQPage arc_test_page;
	// SketchesTestPage sketches_test_page;

	// KnobMapPage knob_map_page;
	// PatchLayoutPage patch_layout_page;
	// ModulesInPatchPage modules_in_patch_page;
	// DebugInfoPage debug_info_page;
	// PageWidgets widgets;

	PatchList &patch_list;
	PatchPlayer &player;
	UiAudioMailbox &mbox;

public:
	Page cur_page;

	PageManager(PatchList &pl, PatchPlayer &pp, Params &p, MetaParams &m, UiAudioMailbox &mbox)
		: info{pl, pp, p, m, mbox} // , balls_page{info}
		// , overview_page{info}
		// , jack_map_page{info}
		// , patch_selector_page{info}
		, arc_test_page{info} // , sketches_test_page{info}

		// , knob_map_page{info}
		// , patch_layout_page{info}
		// , modules_in_patch_page{info}
		// , debug_info_page{info}

		, patch_list{pl}
		, player{pp}
		, mbox{mbox}
		, cur_page{Page::ArcTestJQ}
	{}

	void init();
	void next_page();
	void prev_page();
	void jump_to_page(Page p);
	void update_current_page();
	void set_message(std::string_view message);

private:
	void focus_page(PageChangeDirection dir);
	void blur_page();
};

} // namespace MetaModule
