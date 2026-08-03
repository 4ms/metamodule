#include "usbh_midi_jacks.hh"
#include "pr_dbg.hh"
#include "usbh_ctlreq.h"
#include "usbh_def.h"
#include <cstdint>

namespace
{
// The raw config descriptor as received. wTotalLength is the device's claim
// about its own length; CfgDesc_Raw is what actually fit in the buffer, so the
// parser is given the smaller of the two.
std::span<uint8_t const> config_descriptor(USBH_HandleTypeDef const *phost) {
	size_t len = phost->device.CfgDesc.wTotalLength;
	if (len > sizeof(phost->device.CfgDesc_Raw))
		len = sizeof(phost->device.CfgDesc_Raw);
	return {phost->device.CfgDesc_Raw, len};
}
} // namespace

void count_midi_jacks(USBH_HandleTypeDef const *phost, uint8_t *num_in_jacks, uint8_t *num_out_jacks) {
	count_midi_jacks(config_descriptor(phost), num_in_jacks, num_out_jacks);
}

void parse_midi_jacks(USBH_HandleTypeDef const *phost, MidiJackCollection *jacks) {
	parse_midi_jacks(config_descriptor(phost), jacks);
}

USBH_StatusTypeDef collect_midi_jack_names(USBH_HandleTypeDef *phost, MidiJackCollection *jacks) {
	namespace Sys = MetaModule::System;

	if (jacks->done)
		return USBH_OK;

	uint8_t stored_in = jacks->stored_in_jacks();
	uint8_t stored_out = jacks->stored_out_jacks();
	uint8_t total = stored_in + stored_out;

	while (jacks->cursor < total) {
		uint8_t c = jacks->cursor;

		Sys::UsbMidiJackInfo *jack;
		uint8_t string_idx;
		if (c < stored_in) {
			jack = &jacks->in_jacks[c];
			string_idx = jacks->in_string_idx[c];
		} else {
			uint8_t j = c - stored_in;
			jack = &jacks->out_jacks[j];
			string_idx = jacks->out_string_idx[j];
		}

		// Jacks with no name string: nothing to fetch, move on.
		if (string_idx == 0) {
			jacks->cursor++;
			pr_dbg("MIDI %s jack %d: (no name) valid:%d emb:%d cable:%d\n",
				   c < stored_in ? "in" : "out",
				   jack->jack_id,
				   jack->valid,
				   jack->is_embedded,
				   jack->has_cable ? int(jack->cable_num) : -1);
			continue;
		}

		// USBH_Get_StringDesc is polled: USBH_BUSY until the control transfer
		// finishes. Stay on this jack until it resolves.
		uint8_t namebuf[64];
		namebuf[0] = 0;
		USBH_StatusTypeDef status = USBH_Get_StringDesc(phost, string_idx, namebuf, sizeof(namebuf));
		if (status == USBH_BUSY)
			return USBH_BUSY;

		// On success copy the name; on failure leave it empty. Either way the jack
		// is done -- a single bad name string must not stall the connection.
		if (status == USBH_OK) {
			jack->name.copy(reinterpret_cast<char const *>(namebuf));
			pr_dbg("MIDI %s jack %d: '%s' valid:%d emb:%d cable:%d\n",
				   c < stored_in ? "in" : "out",
				   jack->jack_id,
				   jack->name.c_str(),
				   jack->valid,
				   jack->is_embedded,
				   jack->has_cable ? int(jack->cable_num) : -1);
		}

		jacks->cursor++;
	}

	// Now that the names are in, fill in any that had to be borrowed from an
	// External jack.
	borrow_external_jack_names(jacks);

	jacks->done = true;
	return USBH_OK;
}
