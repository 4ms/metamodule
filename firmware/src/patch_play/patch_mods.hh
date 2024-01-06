#pragma once
#include "patch_mod_queue.hh"
#include "patch_player.hh"

namespace MetaModule
{

inline void handle_patch_mods(PatchModQueue &patch_mod_queue, PatchPlayer &player) {
	if (auto patch_mod = patch_mod_queue.get()) {
		std::visit(overloaded{
					   [&player](SetStaticParam &mod) { player.apply_static_param(mod.param); },
					   [&player](ChangeKnobSet mod) { player.set_active_knob_set(mod.knobset_num); },
					   [&player](AddMapping &mod) { player.add_mapped_knob(mod.set_id, mod.map); },
					   [&player](EditMappingMinMax &mod) { player.edit_mapped_knob(mod.set_id, mod.map, mod.cur_val); },
					   [&player](RemoveMapping &mod) { player.remove_mapped_knob(mod.set_id, mod.map); },
					   [&player](AddMidiMap &mod) { player.add_midi_mapped_knob(mod.map); },
					   [&player](AddInternalCable &mod) { player.add_internal_cable(mod.in, mod.out); },
					   [](ModifyMapping &mod) { /*TODO*/ },
				   },
				   patch_mod.value());
	}
}

} // namespace MetaModule
