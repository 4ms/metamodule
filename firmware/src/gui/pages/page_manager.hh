#pragma once
#include "gui/message_queue.hh"
#include "gui/slsexport/comp_init.hh"
#include "metaparams.hh"
#include "params_state.hh"
#include "patch_file/patch_storage_proxy.hh"
#include "patch_play/patch_mod_queue.hh"
#include "patch_play/patch_playloader.hh"

#include "gui/pages/cable_edit_page.hh"
#include "gui/pages/knobmap.hh"
#include "gui/pages/knobset_view.hh"
#include "gui/pages/module_view.hh"
#include "gui/pages/page_list.hh"
#include "gui/pages/patch_selector.hh"
#include "gui/pages/patch_view.hh"

namespace MetaModule
{

class PageManager {
	SlsComponentInit sls_comp_init;

	PatchInfo info;
	ModuleViewPage page_module{info};
	PatchSelectorPage page_patchsel{info};
	PatchViewPage page_patchview{info};
	KnobSetViewPage page_knobsetview{info};
	KnobMapPage page_knobmap{info};
	CableEditPage page_cableedit{info};

public:
	PageBase *cur_page = &page_patchsel;

	PageManager(PatchStorageProxy &patch_storage,
				PatchPlayLoader &patch_playloader,
				ParamsMidiState &params,
				MetaParams &metaparams,
				MessageQueue &msg_queue,
				PatchModQueue &patch_mod_queue)
		: info{patch_storage, patch_playloader, params, metaparams, msg_queue, patch_mod_queue} {
	}

	void init() {
		PageList::request_new_page(page_patchsel);
	}

	void update_current_page() {
		if (auto newpage = PageList::get_requested_page()) {
			cur_page->blur();
			cur_page = newpage.value();
			cur_page->focus();
		}

		else
			cur_page->update();
	}
};

} // namespace MetaModule
