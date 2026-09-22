#include "usb/midi_jack_parse.hh"

// Descriptor byte layouts (USB Device Class Definition for MIDI Devices v1.0):
//
//   IN jack:  [0]len [1]type(0x24) [2]subtype(0x02) [3]jack_type [4]jack_id
//             [5]iJack
//   OUT jack: [0]len [1]type(0x24) [2]subtype(0x03) [3]jack_type [4]jack_id
//             [5]bNrInputPins(p) [6..6+2p-1](p source pairs) [6+2p]iJack
// jack_type: 0x01 = Embedded, 0x02 = External.
//
// Cable numbers live on the *endpoints*, not the jacks:
//
//   Endpoint:    [0]len [1]type(0x05) [2]bEndpointAddress [3]bmAttributes ...
//   CS endpoint: [0]len [1]type(0x25) [2]subtype(0x01=MS_GENERAL)
//                [3]bNumEmbMIDIJack(n) [4..4+n-1]baAssocJackID
//
// A packet's cable number is the *index* into that endpoint's baAssocJackID
// table, so only Embedded jacks listed there are reachable by cable number.
//
// Note the direction inversion: the bulk IN endpoint (device -> MetaModule,
// i.e. the messages a module receives) associates Embedded MIDI *OUT* jacks,
// and the bulk OUT endpoint associates Embedded MIDI *IN* jacks.

namespace
{
namespace Sys = MetaModule::System;

constexpr uint8_t INTERFACE_DESC = 0x04;
constexpr uint8_t ENDPOINT_DESC = 0x05;
constexpr uint8_t CS_INTERFACE = 0x24;
constexpr uint8_t CS_ENDPOINT = 0x25;

constexpr uint8_t MIDI_IN_JACK = 0x02;
constexpr uint8_t MIDI_OUT_JACK = 0x03;
constexpr uint8_t MS_GENERAL = 0x01;

constexpr uint8_t JackTypeEmbedded = 0x01;

constexpr uint8_t AudioClass = 0x01;
constexpr uint8_t MidiStreamingSubclass = 0x03;

constexpr uint8_t ConfigDescLength = 9; // the descriptor the others follow

// Walks the descriptors that follow the configuration descriptor header,
// calling `fn(bytes)` with each one. Stops on a malformed length rather than
// running off the end: a device that reports garbage must not fault us.
template<typename Callback>
void for_each_descriptor(std::span<uint8_t const> cfg_desc, Callback fn) {
	if (cfg_desc.size() < ConfigDescLength)
		return;

	// The configuration descriptor's own wTotalLength bounds the walk, but only
	// down: it can't reach past what we actually received.
	size_t total = (size_t(cfg_desc[3]) << 8) | cfg_desc[2];
	if (total == 0 || total > cfg_desc.size())
		total = cfg_desc.size();

	size_t pos = ConfigDescLength;
	while (pos + 2 <= total) {
		uint8_t len = cfg_desc[pos];
		if (len < 2 || pos + len > total)
			break;

		fn(cfg_desc.subspan(pos, len));
		pos += len;
	}
}

// Find the stored jack with this bJackID. Returns MetaModule::NoJackIdx if the
// device associated a jack we didn't store (more than MaxMidiJacks, or an
// Element rather than a jack).
uint8_t find_jack_by_id(Sys::UsbMidiJackInfo const *jacks, uint8_t stored, uint8_t jack_id) {
	for (uint8_t i = 0; i < stored; i++) {
		if (jacks[i].valid && jacks[i].jack_id == jack_id)
			return i;
	}
	return MetaModule::NoJackIdx;
}

// Read one endpoint's baAssocJackID table into a cable -> jack-index map, and
// stamp the matching jacks with their cable number. Returns the cable count.
uint8_t parse_assoc_jack_table(std::span<uint8_t const> d,
							   Sys::UsbMidiJackInfo *jacks,
							   uint8_t stored_jacks,
							   MetaModule::CableJackMap &cable_map) {
	// Trust the descriptor's own length over bNumEmbMIDIJack
	size_t num_cables = d[3];
	if (num_cables > d.size() - 4)
		num_cables = d.size() - 4;
	if (num_cables > Sys::MaxMidiCables)
		num_cables = Sys::MaxMidiCables;

	for (uint8_t cable = 0; cable < num_cables; cable++) {
		uint8_t idx = find_jack_by_id(jacks, stored_jacks, d[4 + cable]);
		cable_map[cable] = idx;
		if (idx != MetaModule::NoJackIdx) {
			jacks[idx].cable_num = cable;
			jacks[idx].has_cable = true;
		}
	}

	return uint8_t(num_cables);
}

// Walk the endpoints of the first MIDIStreaming interface that declares any,
// which is the one USBH_MIDI_InterfaceInit() opens pipes on. Requires the jack
// arrays to be filled already, since the tables reference jacks by bJackID.
void parse_midi_cables(std::span<uint8_t const> cfg_desc, MidiJackCollection *jacks) {
	bool in_ms_itf = false;		 // currently walking a MIDIStreaming interface
	bool last_ep_was_in = false; // direction of the endpoint the CS descriptor belongs to
	bool found_any = false;		 // stop at the first MS interface that had endpoints
	bool done = false;

	for_each_descriptor(cfg_desc, [&](std::span<uint8_t const> d) {
		if (done)
			return;

		if (d[1] == INTERFACE_DESC && d.size() >= 9) {
			if (found_any) {
				done = true; // the interface we care about is finished
				return;
			}
			in_ms_itf = (d[5] == AudioClass && d[6] == MidiStreamingSubclass);

		} else if (d[1] == ENDPOINT_DESC && d.size() >= 4) {
			last_ep_was_in = (d[2] & 0x80) != 0;

		} else if (in_ms_itf && d[1] == CS_ENDPOINT && d.size() >= 4 && d[2] == MS_GENERAL) {
			if (last_ep_was_in) {
				// device -> MetaModule: Embedded MIDI OUT jacks
				if (jacks->num_rx_cables == 0)
					jacks->num_rx_cables = parse_assoc_jack_table(
						d, jacks->out_jacks, jacks->stored_out_jacks(), jacks->rx_cable_out_jack_idx);
			} else {
				// MetaModule -> device: Embedded MIDI IN jacks
				if (jacks->num_tx_cables == 0)
					jacks->num_tx_cables = parse_assoc_jack_table(
						d, jacks->in_jacks, jacks->stored_in_jacks(), jacks->tx_cable_in_jack_idx);
			}
			found_any = true;
		}
	});
}

} // namespace

void count_midi_jacks(std::span<uint8_t const> cfg_desc, uint8_t *num_in_jacks, uint8_t *num_out_jacks) {
	uint8_t in_jacks = 0;
	uint8_t out_jacks = 0;

	// Only CS_INTERFACE descriptors inside a MIDIStreaming interface are jacks:
	// CDC functional and audio-class terminal descriptors share type 0x24, and
	// their subtypes collide with MIDI_IN_JACK/MIDI_OUT_JACK.
	bool in_ms_itf = false;

	for_each_descriptor(cfg_desc, [&](std::span<uint8_t const> d) {
		if (d[1] == INTERFACE_DESC && d.size() >= 9) {
			in_ms_itf = (d[5] == AudioClass && d[6] == MidiStreamingSubclass);
			return;
		}
		if (!in_ms_itf || d[1] != CS_INTERFACE || d.size() < 3)
			return;
		if (d[2] == MIDI_IN_JACK)
			in_jacks++;
		else if (d[2] == MIDI_OUT_JACK)
			out_jacks++;
	});

	if (num_in_jacks)
		*num_in_jacks = in_jacks;
	if (num_out_jacks)
		*num_out_jacks = out_jacks;
}

void parse_midi_jacks(std::span<uint8_t const> cfg_desc, MidiJackCollection *jacks) {

	// See count_midi_jacks(): jacks only live inside a MIDIStreaming interface
	bool in_ms_itf = false;

	for_each_descriptor(cfg_desc, [&](std::span<uint8_t const> d) {
		if (d[1] == INTERFACE_DESC && d.size() >= 9) {
			in_ms_itf = (d[5] == AudioClass && d[6] == MidiStreamingSubclass);
			return;
		}
		if (!in_ms_itf || d[1] != CS_INTERFACE || d.size() < 3)
			return;

		if (d[2] == MIDI_IN_JACK && d.size() >= 6) {
			uint8_t idx = jacks->num_in_jacks++;
			if (idx < Sys::MaxMidiJacks) {
				jacks->in_jacks[idx].jack_id = d[4];
				jacks->in_jacks[idx].is_embedded = (d[3] == JackTypeEmbedded);
				jacks->in_jacks[idx].valid = true;
				jacks->in_string_idx[idx] = d[5];
			}

		} else if (d[2] == MIDI_OUT_JACK && d.size() >= 6) {
			uint8_t idx = jacks->num_out_jacks++;
			if (idx < Sys::MaxMidiJacks) {
				uint8_t num_input_pins = d[5];
				size_t str_off = 6 + 2 * size_t(num_input_pins); // iJack sits after the pin list
				jacks->out_jacks[idx].jack_id = d[4];
				jacks->out_jacks[idx].is_embedded = (d[3] == JackTypeEmbedded);
				jacks->out_jacks[idx].valid = true;
				jacks->out_string_idx[idx] = (str_off < d.size()) ? d[str_off] : 0;
				// First input pin's bSourceID (see out_source_id)
				jacks->out_source_id[idx] = (num_input_pins > 0 && d.size() > 6) ? d[6] : 0;
			}
		}
	});

	parse_midi_cables(cfg_desc, jacks);

	jacks->parsed = true;
}

void borrow_external_jack_names(MidiJackCollection *jacks) {
	uint8_t stored_in = jacks->stored_in_jacks();
	uint8_t stored_out = jacks->stored_out_jacks();

	// Embedded OUT jack <-(bSourceID)- External IN jack
	for (uint8_t i = 0; i < stored_out; i++) {
		auto &jack = jacks->out_jacks[i];
		if (!jack.is_embedded || jack.name.length() > 0 || jacks->out_source_id[i] == 0)
			continue;

		uint8_t src = find_jack_by_id(jacks->in_jacks, stored_in, jacks->out_source_id[i]);
		if (src != MetaModule::NoJackIdx && !jacks->in_jacks[src].is_embedded)
			jack.name.copy(jacks->in_jacks[src].name.c_str());
	}

	// Embedded IN jack -(bSourceID)-> External OUT jack
	for (uint8_t i = 0; i < stored_in; i++) {
		auto &jack = jacks->in_jacks[i];
		if (!jack.is_embedded || jack.name.length() > 0)
			continue;

		for (uint8_t j = 0; j < stored_out; j++) {
			if (!jacks->out_jacks[j].is_embedded && jacks->out_source_id[j] == jack.jack_id) {
				jack.name.copy(jacks->out_jacks[j].name.c_str());
				break;
			}
		}
	}
}

void copy_midi_jacks(MidiJackCollection const &jacks, MetaModule::UsbDeviceState &dst) {
	dst.status.num_midi_in_jacks = jacks.num_in_jacks;
	dst.status.num_midi_out_jacks = jacks.num_out_jacks;
	dst.status.num_midi_rx_cables = jacks.num_rx_cables;
	dst.status.num_midi_tx_cables = jacks.num_tx_cables;

	for (unsigned i = 0; i < Sys::MaxMidiJacks; i++) {
		dst.midi_in_jacks[i] = jacks.in_jacks[i];
		dst.midi_out_jacks[i] = jacks.out_jacks[i];
	}

	for (unsigned i = 0; i < Sys::MaxMidiCables; i++) {
		dst.rx_cable_out_jack_idx[i] = jacks.rx_cable_out_jack_idx[i];
		dst.tx_cable_in_jack_idx[i] = jacks.tx_cable_in_jack_idx[i];
	}
}
