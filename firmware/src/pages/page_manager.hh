#pragma once
#include "params.hh"
#include "patch_player.hh"
#include "patchlist.hh"

// Pages:
// #include "pages/knob_view.hh"
#include "pages/module_view.hh"
#include "pages/patch_selector.hh"

namespace MetaModule
{

class PageManager {
	PatchInfo info;

	enum class PageId { PatchSel, Module };

	ModuleViewPage page_module{info, "EnOsc"};
	PatchSelectorPage page_patch{info};
	// KnobView3 page_knobs{info};

	PatchList &patch_list;
	PatchPlayer &player;
	UiAudioMailbox &mbox;

public:
	PageId cur_page = PageId::Module;
	unsigned cur_module_idx = 1;

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
