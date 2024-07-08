#pragma once

#include "CoreModules/elements/element_counter.hh"
#include "CoreModules/elements/elements.hh"
#include "CoreModules/moduleFactory.hh"
#include "console/pr_dbg.hh"
#include "patch/patch_data.hh"
#include "patch_play/patch_mod_queue.hh"
#include <climits>
#include <ranges>
#include <span>

namespace MetaModule
{

class RandomizeParams {
	PatchModQueue &patch_mod_queue;

public:
	RandomizeParams(PatchModQueue &patch_mod_queue)
		: patch_mod_queue{patch_mod_queue} {
	}

	void randomize(uint16_t module_id, PatchData *patch) {
		if (!patch)
			return;

		auto slug = patch->module_slugs[module_id];
		auto info = ModuleFactory::getModuleInfo(slug);

		for ([[maybe_unused]] auto i = 0u; auto const &idx : info.indices) {

			if (idx.param_idx == ElementCount::Indices::NoElementMarker)
				continue;

			// TODO: ParamElement has random_enabled field
			// auto &el = info.elements[i++];
			// if (param_element(el).random_enabled)
			// 	continue;

			float val = std::rand() / (float)RAND_MAX;
			patch->set_or_add_static_knob_value(module_id, idx.param_idx, val);
			patch_mod_queue.put(
				SetStaticParam{.param = {.module_id = module_id, .param_id = idx.param_idx, .value = val}});
		}
	}

private:
};

} // namespace MetaModule
