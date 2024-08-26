#pragma once
#include <cstdint>
struct PotState {
	int16_t cur_val = 0;
	int16_t prev_val = 0;		  // old_i_smoothed_potadc
	int16_t track_moving_ctr = 0; // track_moving_pot
	int16_t delta = 0;			  // pot_delta
	int16_t latched_val = 0;
	bool is_catching_up = false;
	bool moved_while_bank_down = false; // flag_pot_changed_infdown
	bool moved_while_rev_down = false;	// flag_pot_changed_revdown
										// bool moved = false;					// flag_pot_changed
};
