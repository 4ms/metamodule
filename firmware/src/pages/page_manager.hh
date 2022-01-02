#pragma once
#include "params.hh"
#include "patch_player.hh"
#include "patchlist.hh"

// Pages:
#include "pages/knob_view.hh"
#include "pages/module_view.hh"
#include "pages/patch_selector.hh"
#include "pages/sketches_test_jq.hh"

namespace MetaModule
{

class PageManager {
	PatchInfo info;

	enum class PageId { PatchSel, Knobs, Module };

	ModuleViewPage page_module{info, "EnOsc"};
	PatchSelectorPage page_patch{info};
	KnobView3 page_knobs{info};

	// static constexpr size_t LAST_PAGE = 3;
	// std::array<std::unique_ptr<PageBase>, LAST_PAGE> pages = {
	// 	std::make_unique<GroupArcSketchesPage2>(info), std::make_unique<KnobView3>(info),
	// std::make_unique<GroupArcSketchesPage1>(info),
	// std::make_unique<GroupArcSketchesPage3>(info),
	// std::make_unique<GroupArcSketchesPage4>(info),
	// std::make_unique<Dropdown1bPage>(info),
	// std::make_unique<SMRTestPage>(info),
	// std::make_unique<SMRTestLargePage>(info),
	// std::make_unique<PatchOverviewPage>(info),
	// std::make_unique<ArcTestJQPage>(info),
	// std::make_unique<SketchesTestPage>(info),
	// std::make_unique<AudioCVInsPage>(info),
	// std::make_unique<KnobView2>(info),
	// };

	PatchList &patch_list;
	PatchPlayer &player;
	UiAudioMailbox &mbox;

public:
	PageId cur_page = PageId::PatchSel;
	unsigned cur_module_idx = 0;

	PageManager(PatchList &pl, PatchPlayer &pp, Params &p, MetaParams &m, UiAudioMailbox &mbox)
		: info{pl, pp, p, m, mbox}
		, patch_list{pl}
		, player{pp}
		, mbox{mbox} {
	}

	void init();
	void next_page();
	void prev_page();
	void jump_to_page(PageId page);
	void update_current_page();
	void set_message(std::string_view message);

private:
	void _focus_page(PageChangeDirection dir);
	void _blur_page();
	PageBase *_get_cur_page();
};

} // namespace MetaModule
