#pragma once
#include "usb/usb_connection.hh"
#include "usbh_def.h"

void count_midi_jacks(USBH_HandleTypeDef const *phost, uint8_t *num_in_jacks, uint8_t *num_out_jacks);

// MIDI devices with multiple "ports" declare one MIDI In/Out Jack descriptor per
// port, each carrying a jack_id and a string-descriptor index for the port name.
// When a controller is used on a computer the app displays those names, e.g.
// "Kontrol DAW", "Kontrol Main", "Kontrol Ext."
//
// MidiJackCollection gathers the first MaxMidiJacks jacks per direction (id, type
// and name) so they can be published to the GUI / plugin SDK. It also holds the
// little state machine used to read the name strings: collecting names requires
// GET_DESCRIPTOR(STRING) control transfers, which the USB host stack runs
// asynchronously (polled, one transfer at a time), so this is filled in over
// several USBH_Process iterations during the MIDI class-request phase.
struct MidiJackCollection {
	MetaModule::System::UsbMidiJackInfo in_jacks[MetaModule::System::MaxMidiJacks];
	MetaModule::System::UsbMidiJackInfo out_jacks[MetaModule::System::MaxMidiJacks];

	// Total jacks the device declares (may exceed MaxMidiJacks; the arrays above
	// only hold the first MaxMidiJacks of each).
	uint8_t num_in_jacks = 0;
	uint8_t num_out_jacks = 0;

	// Name string-descriptor index per stored jack (0 = no name string).
	uint8_t in_string_idx[MetaModule::System::MaxMidiJacks] = {};
	uint8_t out_string_idx[MetaModule::System::MaxMidiJacks] = {};

	// Name-reading state machine.
	bool parsed = false; // descriptors walked, ids/types/string-idxs filled in
	bool done = false;	 // all name strings collected
	uint8_t cursor = 0;	 // next jack to read a name for (in-jacks then out-jacks)

	void reset() {
		*this = MidiJackCollection{};
	}
};

// Walk the configuration descriptor and fill jack ids, types, counts and name
// string indices. Synchronous (reads the already-fetched descriptor); no USB
// transfers. Sets jacks->parsed.
void parse_midi_jacks(USBH_HandleTypeDef const *phost, MidiJackCollection *jacks);

// Drive the name-string reads. Call repeatedly (it issues one control transfer at
// a time): returns USBH_BUSY while a name is still being fetched, USBH_OK once all
// names are collected. Best-effort -- a jack whose name read fails is left with an
// empty name rather than failing the whole connection. Requires parse_midi_jacks()
// to have run first.
USBH_StatusTypeDef collect_midi_jack_names(USBH_HandleTypeDef *phost, MidiJackCollection *jacks);

// Copy collected jack counts and per-jack info into a device-state snapshot for
// publishing to the GUI / plugin SDK.
void copy_midi_jacks(MidiJackCollection const &jacks, MetaModule::UsbDeviceState &dst);
