#include "usbh_midi_jacks.hh"
#include "pr_dbg.hh"
#include "usbh_ctlreq.h"
#include "usbh_def.h"
#include <cstdint>

void count_midi_jacks(USBH_HandleTypeDef const *phost, uint8_t *num_in_jacks, uint8_t *num_out_jacks) {
	uint8_t in_jacks = 0;
	uint8_t out_jacks = 0;

	unsigned desc_total_length = phost->device.CfgDesc.wTotalLength;
	auto *pdesc = reinterpret_cast<USBH_DescHeader_t const *>(phost->device.CfgDesc_Raw);
	uint16_t ptr = USB_LEN_CFG_DESC;

	while (ptr < desc_total_length) {
		pdesc = USBH_GetNextDesc((uint8_t *)(void *)pdesc, &ptr);

		if (pdesc->bDescriptorType == 0x24) { // Class-specific MIDIStreaming descriptor
			uint8_t subtype = ((uint8_t const *)pdesc)[2];
			if (subtype == 0x02) // MIDI_IN_JACK
				in_jacks++;
			else if (subtype == 0x03) // MIDI_OUT_JACK
				out_jacks++;
		}
	}

	if (num_in_jacks)
		*num_in_jacks = in_jacks;
	if (num_out_jacks)
		*num_out_jacks = out_jacks;
}

// MIDI jack descriptor byte layouts (Class Definition for MIDI Devices v1.0):
//   IN jack:  [0]len [1]type(0x24) [2]subtype(0x02) [3]jack_type [4]jack_id
//             [5]iJack
//   OUT jack: [0]len [1]type(0x24) [2]subtype(0x03) [3]jack_type [4]jack_id
//             [5]bNrInputPins(p) [6..6+2p-1](p source pairs) [6+2p]iJack
// jack_type: 0x01 = Embedded, 0x02 = External.
namespace
{
constexpr uint8_t CS_INTERFACE = 0x24;
constexpr uint8_t MIDI_IN_JACK = 0x02;
constexpr uint8_t MIDI_OUT_JACK = 0x03;
constexpr uint8_t JackTypeEmbedded = 0x01;
} // namespace

void parse_midi_jacks(USBH_HandleTypeDef const *phost, MidiJackCollection *jacks) {
	namespace Sys = MetaModule::System;

	unsigned desc_total_length = phost->device.CfgDesc.wTotalLength;
	auto *pdesc = reinterpret_cast<USBH_DescHeader_t const *>(phost->device.CfgDesc_Raw);
	uint16_t ptr = USB_LEN_CFG_DESC;

	while (ptr < desc_total_length) {
		pdesc = USBH_GetNextDesc((uint8_t *)(void *)pdesc, &ptr);

		if (pdesc->bDescriptorType != CS_INTERFACE)
			continue;

		auto const *b = reinterpret_cast<uint8_t const *>(pdesc);
		uint8_t subtype = b[2];

		if (subtype == MIDI_IN_JACK && pdesc->bLength >= 6) {
			uint8_t idx = jacks->num_in_jacks++;
			if (idx < Sys::MaxMidiJacks) {
				jacks->in_jacks[idx].jack_id = b[4];
				jacks->in_jacks[idx].is_embedded = (b[3] == JackTypeEmbedded);
				jacks->in_jacks[idx].valid = true;
				jacks->in_string_idx[idx] = b[5];
			}

		} else if (subtype == MIDI_OUT_JACK && pdesc->bLength >= 6) {
			uint8_t idx = jacks->num_out_jacks++;
			if (idx < Sys::MaxMidiJacks) {
				uint8_t num_input_pins = b[5];
				uint8_t str_off = 6 + 2 * num_input_pins; // iJack sits after the pin list
				jacks->out_jacks[idx].jack_id = b[4];
				jacks->out_jacks[idx].is_embedded = (b[3] == JackTypeEmbedded);
				jacks->out_jacks[idx].valid = true;
				jacks->out_string_idx[idx] = (str_off < pdesc->bLength) ? b[str_off] : 0;
			}
		}
	}

	jacks->parsed = true;
}

USBH_StatusTypeDef collect_midi_jack_names(USBH_HandleTypeDef *phost, MidiJackCollection *jacks) {
	namespace Sys = MetaModule::System;

	if (jacks->done)
		return USBH_OK;

	uint8_t stored_in = (jacks->num_in_jacks < Sys::MaxMidiJacks) ? jacks->num_in_jacks : Sys::MaxMidiJacks;
	uint8_t stored_out = (jacks->num_out_jacks < Sys::MaxMidiJacks) ? jacks->num_out_jacks : Sys::MaxMidiJacks;
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
			pr_dbg("MIDI %s jack %d: (no name) valid:%d emb:%d\n",
				   c < stored_in ? "in" : "out",
				   jack->jack_id,
				   jack->valid,
				   jack->is_embedded);
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
			pr_dbg("MIDI %s jack %d: '%s' valid:%d emb:%d\n",
				   c < stored_in ? "in" : "out",
				   jack->jack_id,
				   jack->name.c_str(),
				   jack->valid,
				   jack->is_embedded);
		}

		jacks->cursor++;
	}

	jacks->done = true;
	return USBH_OK;
}

void copy_midi_jacks(MidiJackCollection const &jacks, MetaModule::UsbDeviceState &dst) {
	dst.status.num_midi_in_jacks = jacks.num_in_jacks;
	dst.status.num_midi_out_jacks = jacks.num_out_jacks;
	for (unsigned i = 0; i < MetaModule::System::MaxMidiJacks; i++) {
		dst.midi_in_jacks[i] = jacks.in_jacks[i];
		dst.midi_out_jacks[i] = jacks.out_jacks[i];
	}
}
