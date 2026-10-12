#pragma once
#include "CoreModules/hub/audio_expander_defs.hh"
#include "conf/jack_sense_conf.hh"
#include <cstdint>

namespace MetaModule
{

// Bit n set: panel output n (0-7 main, 8-15 Audio Expander) has a cable plugged in
inline uint32_t patched_outputs_mask(uint32_t jack_senses, unsigned num_outputs) {
	uint32_t mask = 0;
	for (unsigned i = 0; i < num_outputs; i++) {
		auto bit = main_jacksense_output_bit(i);
		if (!bit)
			bit = AudioExpander::jacksense_output_bit(i);
		if (bit && (jack_senses & (1u << *bit)))
			mask |= 1u << i;
	}
	return mask;
}

} // namespace MetaModule
