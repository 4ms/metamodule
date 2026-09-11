#pragma once
#include "usb/usb_connection.hh"
#include <cstdint>
#include <span>

// Parsing of a USB-MIDI device's configuration descriptor: which jacks it has,
// what they're called, and which cable number reaches each one.
//
// This half is pure -- it takes the raw configuration descriptor bytes and
// touches no USB stack -- so it can be unit tested against synthetic
// descriptors. The USB-transfer half (reading the name strings, which needs
// control transfers) lives in usbh_midi_jacks.hh.

// MIDI devices with multiple "ports" declare one MIDI In/Out Jack descriptor per
// port, each carrying a jack_id and a string-descriptor index for the port name.
// When a controller is used on a computer the app displays those names, e.g.
// "Kontrol DAW", "Kontrol Main", "Kontrol Ext."
//
// MidiJackCollection gathers the first MaxMidiJacks jacks per direction (id,
// type, cable number and name) so they can be published to the GUI / plugin SDK.
// It also holds the little state machine used to read the name strings.
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

	// bSourceID of each stored OUT jack's first input pin (0 = none). Used to
	// walk the device's internal wiring, e.g. Embedded MIDI OUT jack <- External
	// MIDI IN jack, to borrow a name for a jack that has no iJack string.
	uint8_t out_source_id[MetaModule::System::MaxMidiJacks] = {};

	// Cable number -> index into out_jacks[] / in_jacks[], built from the
	// baAssocJackID table of the bulk endpoints. MetaModule::NoJackIdx if the
	// device associated a jack we didn't store.
	MetaModule::CableJackMap rx_cable_out_jack_idx = MetaModule::empty_cable_map();
	MetaModule::CableJackMap tx_cable_in_jack_idx = MetaModule::empty_cable_map();
	uint8_t num_rx_cables = 0;
	uint8_t num_tx_cables = 0;

	// Name-reading state machine.
	bool parsed = false; // descriptors walked, ids/types/cables/string-idxs filled in
	bool done = false;	 // all name strings collected
	uint8_t cursor = 0;	 // next jack to read a name for (in-jacks then out-jacks)

	void reset() {
		*this = MidiJackCollection{};
	}

	// How many jacks are actually stored (the declared count, capped).
	uint8_t stored_in_jacks() const {
		return (num_in_jacks < MetaModule::System::MaxMidiJacks) ? num_in_jacks : MetaModule::System::MaxMidiJacks;
	}
	uint8_t stored_out_jacks() const {
		return (num_out_jacks < MetaModule::System::MaxMidiJacks) ? num_out_jacks : MetaModule::System::MaxMidiJacks;
	}
};

// Count the MIDI IN/OUT jack descriptors a configuration declares, without
// storing anything. Either pointer may be null.
void count_midi_jacks(std::span<uint8_t const> cfg_desc, uint8_t *num_in_jacks, uint8_t *num_out_jacks);

// Walk a raw configuration descriptor and fill jack ids, types, counts, name
// string indices, and the cable-number tables. Sets jacks->parsed.
void parse_midi_jacks(std::span<uint8_t const> cfg_desc, MidiJackCollection *jacks);

// A device is free to leave an Embedded jack's iJack at 0 and put the useful
// name on the External jack it's wired to (the physical DIN socket). When that
// happens, borrow the External jack's name so a module has something to show in
// a port list. Call after the name strings have been read.
void borrow_external_jack_names(MidiJackCollection *jacks);

// Copy collected jack counts, per-jack info and cable tables into a device-state
// snapshot for publishing to the GUI / plugin SDK.
void copy_midi_jacks(MidiJackCollection const &jacks, MetaModule::UsbDeviceState &dst);
