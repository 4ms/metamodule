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
#include "gui/pages/main_menu.hh"
#include "gui/pages/module_view.hh"
#include "gui/pages/page_list.hh"
#include "gui/pages/patch_selector.hh"
#include "gui/pages/patch_view.hh"

namespace MetaModule
{

class PageManager {
	SlsComponentInit sls_comp_init;

	PatchInfo info;
	PageList page_list;

	MainMenuPage page_mainmenu{info};
	PatchSelectorPage page_patchsel{info};
	PatchViewPage page_patchview{info};
	ModuleViewPage page_module{info};
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
		: info{patch_storage, patch_playloader, params, metaparams, msg_queue, patch_mod_queue, page_list} {
	}

	void init() {
		page_list.request_initial_page(PageId::MainMenu, {});
	}

	void update_current_page() {
		if (auto newpage = page_list.get_requested_page()) {
			if (newpage->page) {
				cur_page->blur();
				cur_page = newpage->page;
				printf("Args: mod: %d, panel: %d, set: %d, patchidx: %u\n",
					   newpage->args->module_id.value_or(88),
					   newpage->args->mappedknob_id.value_or(88),
					   newpage->args->view_knobset_id.value_or(88),
					   (unsigned)newpage->args->patch_loc.value_or(PatchLocation{}).index);
				if (newpage->args->element_indices) {
					auto i = newpage->args->element_indices.value();
					printf("Ind: %d %d %d %d\n", i.param_idx, i.input_idx, i.output_idx, i.light_idx);
				}
				if (newpage->args->element_counts) {
					auto i = newpage->args->element_counts.value();
					printf("Cnt: %zu %zu %zu %zu\n", i.num_params, i.num_inputs, i.num_outputs, i.num_lights);
				}
				cur_page->focus(newpage->args);
			}
		}

		else
			cur_page->update();
	}
};

} // namespace MetaModule
