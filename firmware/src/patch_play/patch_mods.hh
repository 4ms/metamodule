#pragma once
#include "patch_mod_queue.hh"
#include "patch_player.hh"
#include "util/overloaded.hh"

namespace MetaModule
{

inline void handle_patch_mods(PatchModQueue &patch_mod_queue,
							  PatchPlayer &player,
							  SavedCalData &caldata,
							  std::optional<bool> &new_cal_state) {
	if (auto patch_mod = patch_mod_queue.get()) {
		std::visit(
			overloaded{[&player](SetStaticParam &mod) { player.apply_static_param(mod.param); },
					   [&player](ChangeKnobSet mod) { player.set_active_knob_set(mod.knobset_num); },
					   [&player](AddMapping &mod) { player.add_mapped_knob(mod.set_id, mod.map); },
					   [&player](EditMappingMinMax &mod) { player.edit_mapped_knob(mod.set_id, mod.map, mod.cur_val); },
					   [&player](RemoveMapping &mod) { player.remove_mapped_knob(mod.set_id, mod.map); },
					   [](ModifyMapping &mod) { /*TODO*/ },
					   [&player](AddMidiMap &mod) { player.add_midi_mapped_knob(mod.map); },
					   [&player](AddInternalCable &mod) { player.add_internal_cable(mod.in, mod.out); },
					   [&player](AddJackMapping &mod) {
						   mod.type == ElementType::Input ? player.add_injack_mapping(mod.panel_jack_id, mod.jack) :
															player.add_outjack_mapping(mod.panel_jack_id, mod.jack);
					   },
					   [&player](DisconnectJack &mod) {
						   mod.type == ElementType::Input ? player.disconnect_injack(mod.jack) :
															player.disconnect_outjack(mod.jack);
					   },
					   [&player](RemoveModule &mod) { player.remove_module(mod.module_idx); },

					   [&caldata](SetChanCalibration &mod) {
						   if (mod.input_chan && mod.channel < caldata.in_cal.size()) {
							   caldata.in_cal[mod.channel] = {mod.slope, mod.offset};
						   } else if (!mod.input_chan && mod.channel < caldata.out_cal.size()) {
							   caldata.out_cal[mod.channel] = {mod.slope, mod.offset};
						   }
					   },

					   [&new_cal_state](CalibrationOnOff &mod) {
						   new_cal_state = mod.enable;
					   }

			},
			patch_mod.value());
	}
}

} // namespace MetaModule
