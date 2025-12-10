#pragma once
#include "calibrate/calibration_data.hh"
#include "patch_mod_queue.hh"
#include "patch_player.hh"
#include "util/overloaded.hh"

namespace MetaModule
{

inline void handle_patch_mods(PatchModQueue &patch_mod_queue,
							  PatchPlayer &player,
							  CalData *caldata,
							  std::optional<bool> &new_cal_state) {
	PatchModRequest patch_mod{};
	if (patch_mod_queue.get_move(patch_mod)) {
		std::visit(overloaded{
					   [&player](SetStaticParam &mod) { player.apply_static_param(mod.param); },
					   [&player](ChangeKnobSet mod) { player.set_active_knob_set(mod.knobset_num); },
					   [&player](AddMapping &mod) { player.add_mapped_knob(mod.set_id, mod.map); },
					   [&player](ModifyMapping &mod) { player.edit_mapped_knob(mod.set_id, mod.map); },
					   [&player](RemoveMapping &mod) { player.remove_mapped_knob(mod.set_id, mod.map); },
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
					   [&player](RemoveJackMappings &mod) {
						   mod.type == ElementType::Input ? player.remove_injack_mappings(mod.jack) :
															player.remove_outjack_mappings(mod.jack);
					   },
					   [&](SetMidiPolyNum mod) { player.set_midi_poly_num(mod.poly_num); },

					   [&caldata](SetChanCalibration &mod) {
						   if (mod.is_input) {
							   auto chan = mod.channel % CalData::NumIns;
							   caldata->in_cal[chan] = {mod.slope, mod.offset};
						   } else {
							   auto chan = mod.channel % CalData::NumOuts;
							   caldata->out_cal[chan] = {mod.slope, mod.offset};
						   }
					   },

					   [&new_cal_state](CalibrationOnOff &mod) { new_cal_state = mod.enable; },
					   [&player](LoadModuleState &mod) { player.reset_module(mod.module_id, mod.data); },
				   },
				   patch_mod);
	}
}

} // namespace MetaModule
