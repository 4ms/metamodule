#pragma once
#include "usbh_def.h"

void parse_midistream_itf_desc(USBH_DescHeader_t const *pdesc);
void parse_midistream_injack_desc(USBH_DescHeader_t const *pdesc);
void parse_midistream_outjack_desc(USBH_DescHeader_t const *pdesc);
void parse_bulk_ep_desc(USBH_DescHeader_t const *pdesc);
void parse_midistream_cs_bulk_ep_desc(USBH_DescHeader_t const *pdesc);
void scan_all_descriptors(USBH_HandleTypeDef const *phost);

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
