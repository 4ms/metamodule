#pragma once
// #include "pages/bouncing_balls.hh"
// #include "pages/debuginfo.hh"
// #include "pages/page_widgets.hh"
#include "pages/arc_test_jq.hh"
#include "pages/patch_overview.hh"
// #include "pages/patch_selector.hh"
#include "pages/sketches_test_jq.hh"
#include "params.hh"
#include "patch_player.hh"
#include "patchlist.hh"
#include <variant>
// #include "screen_buffer.hh"

namespace MetaModule
{

class PageManager {
	// using PageVariants = std::variant< //
	// 	ArcTestJQPage,				   //
	// 	SketchesTestPage			   //
	// 	>;

	PatchInfo info;

	std::array<std::unique_ptr<PageBase>, 3> pages = {
		std::make_unique<PatchOverviewPage>(info),
		std::make_unique<ArcTestJQPage>(info),
		std::make_unique<SketchesTestPage>(info),
	};

	// BouncingBallsPage balls_page;
	// JackMapPage jack_map_page;
	// PatchSelectorPage patch_selector_page;
	// KnobMapPage knob_map_page;
	// PatchLayoutPage patch_layout_page;
	// ModulesInPatchPage modules_in_patch_page;
	// DebugInfoPage debug_info_page;

	PatchList &patch_list;
	PatchPlayer &player;
	UiAudioMailbox &mbox;

public:
	unsigned cur_page;

	PageManager(PatchList &pl, PatchPlayer &pp, Params &p, MetaParams &m, UiAudioMailbox &mbox)
		: info{pl, pp, p, m, mbox}
		, patch_list{pl}
		, player{pp}
		, mbox{mbox}
		, cur_page{0}
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
