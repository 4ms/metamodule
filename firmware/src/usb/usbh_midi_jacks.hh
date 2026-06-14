#pragma once
#include "usbh_ctlreq.h"
#include "usbh_def.h"

void parse_midistream_itf_desc(USBH_DescHeader_t const *pdesc);
void parse_midistream_injack_desc(USBH_DescHeader_t const *pdesc);
void parse_midistream_outjack_desc(USBH_DescHeader_t const *pdesc);
void parse_bulk_ep_desc(USBH_DescHeader_t const *pdesc);
void parse_midistream_cs_bulk_ep_desc(USBH_DescHeader_t const *pdesc);
void scan_all_descriptors(USBH_HandleTypeDef const *phost);

// Count the MIDI IN and OUT jacks declared in the device's MIDIStreaming
// descriptors. Quiet (no printing); safe on any device (writes 0 for non-MIDI).
// Used to report jack counts in the USB connection status. Header-inline so it
// links wherever it's referenced (usbh_midi_jacks.cc isn't in every core's
// source list).
inline void count_midi_jacks(USBH_HandleTypeDef const *phost, uint8_t *num_in_jacks, uint8_t *num_out_jacks) {
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

// Notes of MIDI devices with multiple "ports":
// One MIDI device might have multiple MIDI Out Jacks or In Jacks.
// Each Jack has a MIDIIn/OutJackDescriptor, which provides the jack_id and
// a string index for the name.
// When a controller is used on a computer, the app will display these jacks names, e.g.
// "Kontrol DAW", "Kontrol Main", "Kontrol Ext."
//
// We should collect the names and jack IDs, and store that in the MIDI class handle.
// Then the GUI could allow the user to display, browse, and choose a Jack.
//
// TODO: figure out how to change jacks? It seems like they all have the same endpoint addr?
