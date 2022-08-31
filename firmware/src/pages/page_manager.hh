#pragma once
#include "params.hh"
#include "patch_player.hh"
#include "patchlist.hh"

// Pages:
// #include "pages/knob_view.hh"
#include "pages/knob_edit.hh"
#include "pages/module_view.hh"
#include "pages/page_list.hh"
#include "pages/patch_selector.hh"
#include "pages/patch_view.hh"

namespace MetaModule
{

class PageManager {
	PatchInfo info;

	ModuleViewPage page_module{info, "EnOsc"};
	PatchSelectorPage page_patchsel{info};
	PatchViewPage page_patchview{info};
	KnobEditPage knob_edit_page{info};
	// KnobView3 page_knobs{info};

	PatchList &patch_list;
	PatchPlayer &player;
	UiAudioMailbox &mbox;

public:
	PageBase *cur_page = &page_patchsel;

	PageManager(PatchList &pl, PatchPlayer &pp, Params &p, MetaParams &m, UiAudioMailbox &mbox)
		: info{pl, pp, p, m, mbox}
		, patch_list{pl}
		, player{pp}
		, mbox{mbox} {
	}

	void init();
	void update_current_page();

private:
};

} // namespace MetaModule
