#pragma once

#include "CoreModules/elements/element_counter.hh"
#include "CoreModules/elements/elements.hh"
#include "CoreModules/moduleFactory.hh"
#include "console/pr_dbg.hh"
#include "patch/patch_data.hh"
#include "patch_play/modules_helpers.hh"
#include "patch_play/patch_mod_queue.hh"
#include <climits>
#include <ranges>
#include <span>

namespace MetaModule
{

class ResetParams {
	PatchModQueue &patch_mod_queue;

public:
	ResetParams(PatchModQueue &patch_mod_queue)
		: patch_mod_queue{patch_mod_queue} {
	}

	void reset(uint16_t module_id, PatchData *patch) {
		if (!patch)
			return;

		auto slug = patch->module_slugs[module_id];
		auto info = ModuleFactory::getModuleInfo(slug);

		// Set params to default values
		for (unsigned i = 0; auto const &element : info.elements) {
			if (auto def_val = get_normalized_default_value(element); def_val.has_value()) {
				auto param_id = info.indices[i].param_idx;
				patch->set_or_add_static_knob_value(module_id, param_id, def_val.value());
				patch_mod_queue.put(
					SetStaticParam{.param = {.module_id = module_id, .param_id = param_id, .value = def_val.value()}});
			}
			i++;
		}
	}

private:
};

} // namespace MetaModule
