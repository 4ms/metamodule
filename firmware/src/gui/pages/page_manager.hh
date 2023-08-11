#pragma once
#include "gui/message_queue.hh"
#include "param_cache.hh"
#include "patch_file/patch_storage_proxy.hh"
#include "patch_play/patch_mod_queue.hh"
#include "patch_play/patch_playloader.hh"

#include "gui/pages/knob_edit.hh"
#include "gui/pages/module_view.hh"
#include "gui/pages/page_list.hh"
#include "gui/pages/patch_selector.hh"
#include "gui/pages/patch_view.hh"

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

	PageManager(PatchStorageProxy &patch_storage,
				PatchPlayLoader &patch_playloader,
				ParamsState &params,
				MetaParams &metaparams,
				MessageQueue &msg_queue,
				PatchModQueue &patch_mod_queue)
		: info{patch_storage, patch_playloader, params, metaparams, msg_queue, patch_mod_queue} {
	}

	void init();
	void update_current_page();
};

} // namespace MetaModule
