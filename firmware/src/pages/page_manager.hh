#pragma once
#include "pages/arc_test_jq.hh"
// #include "pages/bouncing_balls.hh"
// #include "pages/debuginfo.hh"
// #include "pages/page_widgets.hh"
// #include "pages/patch_overview.hh"
// #include "pages/patch_selector.hh"
#include "pages/sketches_test_jq.hh"
#include "params.hh"
#include "patch_player.hh"
#include "patchlist.hh"

namespace MetaModule
{

class PageManager {
	PatchInfo info;

	static constexpr size_t LAST_PAGE = 3;
	std::array<std::unique_ptr<PageBase>, LAST_PAGE> pages = {
		std::make_unique<ArcTestJQPage>(info),
		// std::make_unique<SketchesTestPage>(info),
		std::make_unique<KnobView1>(info),
		// std::make_unique<KnobView2>(info),
		// std::make_unique<KnobView3>(info),
	};
	// BouncingBallsPage balls_page;
	// PatchOverviewPage overview_page;
	// JackMapPage jack_map_page;
	// PatchSelectorPage patch_selector_page;
	// KnobMapPage knob_map_page;
	// PatchLayoutPage patch_layout_page;
	// ModulesInPatchPage modules_in_patch_page;
	// DebugInfoPage debug_info_page;
	// PageWidgets widgets;

	PatchList &patch_list;
	PatchPlayer &player;
	UiAudioMailbox &mbox;

public:
	unsigned cur_page = 0;

	PageManager(PatchList &pl, PatchPlayer &pp, Params &p, MetaParams &m, UiAudioMailbox &mbox)
		: info{pl, pp, p, m, mbox}
		, patch_list{pl}
		, player{pp}
		, mbox{mbox}
	{}

	void init();
	void next_page();
	void prev_page();
	void jump_to_page(unsigned p);
	void update_current_page();
	void set_message(std::string_view message);

private:
	void focus_page(PageChangeDirection dir);
	void blur_page();
};

} // namespace MetaModule
