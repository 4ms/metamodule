#pragma once
#include "params.hh"
#include "patch_mod_queue.hh"
#include "patch_player.hh"
#include "patchlist.hh"
#include "ui_audio_mailbox.hh"

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

public:
	PageBase *cur_page = &page_patchsel;

	PageManager(PatchList &patchlist,
				PatchLoader &patch_loader,
				Params &params,
				MetaParams &metaparams,
				MessageQueue &msg_queue,
				PatchModQueue &patch_mod_queue)
		: info{patchlist, patch_loader, params, metaparams, msg_queue, patch_mod_queue} {
	}

	void init();
	void update_current_page();
};

} // namespace MetaModule
