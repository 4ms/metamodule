#include "doctest.h"
#include "usb/midi_jack_parse.hh"
#include <cstdint>
#include <string_view>
#include <vector>

// Tests for the USB-MIDI configuration descriptor parser: which jacks a device
// declares, and which cable number reaches each one.
//
// The descriptors here are hand-built to match real device shapes. The key
// thing being pinned down is the direction inversion: a cable that carries
// messages *to* the MetaModule (rx) is served by the device's Embedded MIDI
// *OUT* jack, and vice versa.

namespace
{

using namespace MetaModule;

// --- Descriptor builders (USB MIDI Class v1.0 byte layouts) ---------------

constexpr uint8_t Embedded = 0x01;
constexpr uint8_t External = 0x02;

struct ConfigBuilder {
	std::vector<uint8_t> bytes;

	ConfigBuilder() {
		// Configuration descriptor header; wTotalLength patched in by finish()
		bytes = {9, 0x02, 0, 0, 1, 1, 0, 0x80, 50};
	}

	ConfigBuilder &interface(uint8_t number, uint8_t num_eps, uint8_t cls, uint8_t subclass) {
		append({9, 0x04, number, 0, num_eps, cls, subclass, 0, 0});
		return *this;
	}

	ConfigBuilder &midi_streaming_itf(uint8_t number, uint8_t num_eps) {
		return interface(number, num_eps, 0x01, 0x03);
	}

	ConfigBuilder &in_jack(uint8_t type, uint8_t jack_id, uint8_t iJack = 0) {
		append({6, 0x24, 0x02, type, jack_id, iJack});
		return *this;
	}

	// An OUT jack with a single input pin, sourced from `source_id` pin 1.
	ConfigBuilder &out_jack(uint8_t type, uint8_t jack_id, uint8_t source_id, uint8_t iJack = 0) {
		append({9, 0x24, 0x03, type, jack_id, 1, source_id, 1, iJack});
		return *this;
	}

	// addr's high bit picks the direction: 0x81 = bulk IN (device -> host).
	ConfigBuilder &endpoint(uint8_t addr) {
		append({9, 0x05, addr, 0x02, 0x40, 0x00, 0, 0, 0});
		return *this;
	}

	ConfigBuilder &cs_endpoint(std::vector<uint8_t> assoc_jack_ids) {
		std::vector<uint8_t> d{uint8_t(4 + assoc_jack_ids.size()), 0x25, 0x01, uint8_t(assoc_jack_ids.size())};
		d.insert(d.end(), assoc_jack_ids.begin(), assoc_jack_ids.end());
		append(d);
		return *this;
	}

	ConfigBuilder &raw(std::vector<uint8_t> d) {
		append(d);
		return *this;
	}

	std::vector<uint8_t> const &finish() {
		bytes[2] = uint8_t(bytes.size() & 0xFF);
		bytes[3] = uint8_t(bytes.size() >> 8);
		return bytes;
	}

private:
	void append(std::vector<uint8_t> const &d) {
		bytes.insert(bytes.end(), d.begin(), d.end());
	}
};

// A plain 1-in/1-out USB MIDI interface (the shape of a simple controller):
// one embedded jack each way, wired to an external jack each way.
//   jack 1: Embedded IN   <- from us over the bulk OUT endpoint (tx cable 0)
//   jack 2: External OUT  <- jack 1   (the device's physical DIN OUT)
//   jack 3: External IN                (the device's physical DIN IN)
//   jack 4: Embedded OUT  <- jack 3   -> to us on the bulk IN endpoint (rx cable 0)
ConfigBuilder simple_device() {
	ConfigBuilder c;
	c.interface(0, 0, 0x01, 0x01); // AudioControl
	c.midi_streaming_itf(1, 2);
	c.in_jack(Embedded, 1, 3);
	c.in_jack(External, 3, 5);
	c.out_jack(Embedded, 4, 3, 6);
	c.out_jack(External, 2, 1, 4);
	c.endpoint(0x01); // bulk OUT: host -> device
	c.cs_endpoint({1});
	c.endpoint(0x81); // bulk IN: device -> host
	c.cs_endpoint({4});
	return c;
}

MidiJackCollection parse(std::vector<uint8_t> const &cfg) {
	MidiJackCollection jacks;
	parse_midi_jacks(cfg, &jacks);
	return jacks;
}

} // namespace

TEST_CASE("Simple 1x1 device: jacks are found and cables map to the embedded jacks") {
	auto jacks = parse(simple_device().finish());

	CHECK(jacks.parsed);
	CHECK(jacks.num_in_jacks == 2);
	CHECK(jacks.num_out_jacks == 2);
	CHECK(jacks.num_rx_cables == 1);
	CHECK(jacks.num_tx_cables == 1);

	// rx cable 0 -> the Embedded MIDI OUT jack (id 4), i.e. what sends to us
	CHECK(jacks.rx_cable_out_jack_idx[0] == 0);
	CHECK(jacks.out_jacks[0].jack_id == 4);
	CHECK(jacks.out_jacks[0].is_embedded);
	CHECK(jacks.out_jacks[0].has_cable);
	CHECK(jacks.out_jacks[0].cable_num == 0);

	// tx cable 0 -> the Embedded MIDI IN jack (id 1), i.e. what we send to
	CHECK(jacks.tx_cable_in_jack_idx[0] == 0);
	CHECK(jacks.in_jacks[0].jack_id == 1);
	CHECK(jacks.in_jacks[0].is_embedded);
	CHECK(jacks.in_jacks[0].has_cable);
	CHECK(jacks.in_jacks[0].cable_num == 0);

	// External jacks are not reachable over USB, so they get no cable number
	CHECK(jacks.in_jacks[1].jack_id == 3);
	CHECK(!jacks.in_jacks[1].is_embedded);
	CHECK(!jacks.in_jacks[1].has_cable);
	CHECK(jacks.out_jacks[1].jack_id == 2);
	CHECK(!jacks.out_jacks[1].is_embedded);
	CHECK(!jacks.out_jacks[1].has_cable);
}

TEST_CASE("Multi-port device: cable number is the index into baAssocJackID, not the jack id") {
	// Three ports each way. The assoc tables deliberately list the jack ids out
	// of declaration order, so a parser that assumed "cable N = Nth jack" fails.
	ConfigBuilder c;
	c.midi_streaming_itf(0, 2);
	c.in_jack(Embedded, 11);
	c.in_jack(Embedded, 12);
	c.in_jack(Embedded, 13);
	c.out_jack(Embedded, 21, 0);
	c.out_jack(Embedded, 22, 0);
	c.out_jack(Embedded, 23, 0);
	c.endpoint(0x02);
	c.cs_endpoint({13, 11, 12});
	c.endpoint(0x82);
	c.cs_endpoint({23, 22, 21});

	auto jacks = parse(c.finish());

	CHECK(jacks.num_rx_cables == 3);
	CHECK(jacks.num_tx_cables == 3);

	// rx: assoc list {23, 22, 21} -> out_jacks are stored as [21, 22, 23]
	CHECK(jacks.rx_cable_out_jack_idx[0] == 2); // cable 0 -> jack 23
	CHECK(jacks.rx_cable_out_jack_idx[1] == 1); // cable 1 -> jack 22
	CHECK(jacks.rx_cable_out_jack_idx[2] == 0); // cable 2 -> jack 21
	CHECK(jacks.out_jacks[2].cable_num == 0);
	CHECK(jacks.out_jacks[1].cable_num == 1);
	CHECK(jacks.out_jacks[0].cable_num == 2);

	// tx: assoc list {13, 11, 12} -> in_jacks are stored as [11, 12, 13]
	CHECK(jacks.tx_cable_in_jack_idx[0] == 2); // cable 0 -> jack 13
	CHECK(jacks.tx_cable_in_jack_idx[1] == 0); // cable 1 -> jack 11
	CHECK(jacks.tx_cable_in_jack_idx[2] == 1); // cable 2 -> jack 12
	CHECK(jacks.in_jacks[2].cable_num == 0);
	CHECK(jacks.in_jacks[0].cable_num == 1);
	CHECK(jacks.in_jacks[1].cable_num == 2);
}

TEST_CASE("Device with only a bulk IN endpoint (e.g. a keyboard) has rx cables but no tx cables") {
	ConfigBuilder c;
	c.midi_streaming_itf(0, 1);
	c.out_jack(Embedded, 2, 0);
	c.endpoint(0x81);
	c.cs_endpoint({2});

	auto jacks = parse(c.finish());

	CHECK(jacks.num_rx_cables == 1);
	CHECK(jacks.num_tx_cables == 0);
	CHECK(jacks.out_jacks[0].has_cable);
	CHECK(jacks.rx_cable_out_jack_idx[0] == 0);
}

TEST_CASE("Endpoints outside a MIDIStreaming interface are ignored") {
	// A composite device: an audio streaming interface with its own endpoint
	// comes first, then the MIDI interface. The audio endpoint must not be
	// mistaken for a MIDI one.
	ConfigBuilder c;
	c.interface(0, 1, 0x01, 0x02); // AudioStreaming, not MidiStreaming
	c.endpoint(0x83);
	c.raw({7, 0x25, 0x01, 0x00, 0x00, 0x00, 0x00}); // audio's own CS endpoint desc
	c.midi_streaming_itf(1, 1);
	c.out_jack(Embedded, 5, 0);
	c.endpoint(0x81);
	c.cs_endpoint({5});

	auto jacks = parse(c.finish());

	CHECK(jacks.num_rx_cables == 1);
	CHECK(jacks.rx_cable_out_jack_idx[0] == 0);
	CHECK(jacks.out_jacks[0].jack_id == 5);
	CHECK(jacks.out_jacks[0].cable_num == 0);
}

TEST_CASE("A cable naming a jack we didn't store still counts, but maps to no jack") {
	// The device associates jack id 99, which it never declared.
	ConfigBuilder c;
	c.midi_streaming_itf(0, 1);
	c.out_jack(Embedded, 2, 0);
	c.endpoint(0x81);
	c.cs_endpoint({2, 99});

	auto jacks = parse(c.finish());

	CHECK(jacks.num_rx_cables == 2);
	CHECK(jacks.rx_cable_out_jack_idx[0] == 0);
	CHECK(jacks.rx_cable_out_jack_idx[1] == NoJackIdx);
}

TEST_CASE("More jacks than MaxMidiJacks: counts keep rising but storage is capped") {
	ConfigBuilder c;
	c.midi_streaming_itf(0, 0);
	for (unsigned i = 0; i < System::MaxMidiJacks + 4; i++)
		c.out_jack(Embedded, uint8_t(i + 1), 0);

	auto jacks = parse(c.finish());

	CHECK(jacks.num_out_jacks == System::MaxMidiJacks + 4);
	CHECK(jacks.stored_out_jacks() == System::MaxMidiJacks);
	CHECK(jacks.out_jacks[System::MaxMidiJacks - 1].valid);
	CHECK(jacks.out_jacks[System::MaxMidiJacks - 1].jack_id == System::MaxMidiJacks);
}

TEST_CASE("More cables than MaxMidiCables are clamped") {
	ConfigBuilder c;
	c.midi_streaming_itf(0, 1);
	std::vector<uint8_t> assoc;
	for (unsigned i = 0; i < System::MaxMidiCables + 3; i++) {
		c.out_jack(Embedded, uint8_t(i + 1), 0);
		assoc.push_back(uint8_t(i + 1));
	}
	c.endpoint(0x81);
	c.cs_endpoint(assoc);

	auto jacks = parse(c.finish());

	CHECK(jacks.num_rx_cables == System::MaxMidiCables);
}

TEST_CASE("Truncated and malformed descriptors don't run off the end") {
	SUBCASE("descriptor with a zero length") {
		ConfigBuilder c;
		c.midi_streaming_itf(0, 0);
		c.out_jack(Embedded, 1, 0);
		c.raw({0, 0x24, 0x03, Embedded, 2}); // bLength = 0
		c.out_jack(Embedded, 3, 0);

		auto jacks = parse(c.finish());
		CHECK(jacks.num_out_jacks == 1); // stops at the bad one
	}

	SUBCASE("descriptor claiming to be longer than what's left") {
		ConfigBuilder c;
		c.midi_streaming_itf(0, 0);
		c.out_jack(Embedded, 1, 0);
		c.raw({40, 0x24, 0x03, Embedded, 2, 0}); // claims 40 bytes, only 6 present

		auto jacks = parse(c.finish());
		CHECK(jacks.num_out_jacks == 1);
	}

	SUBCASE("wTotalLength larger than the bytes we actually have") {
		auto cfg = simple_device().finish();
		cfg[2] = 0xFF; // claim 255 bytes
		cfg[3] = 0x00;

		auto jacks = parse(cfg);
		CHECK(jacks.num_in_jacks == 2);
		CHECK(jacks.num_out_jacks == 2);
		CHECK(jacks.num_rx_cables == 1);
	}

	SUBCASE("CS endpoint descriptor whose bNumEmbMIDIJack overruns its own length") {
		ConfigBuilder c;
		c.midi_streaming_itf(0, 1);
		c.out_jack(Embedded, 2, 0);
		c.endpoint(0x81);
		c.raw({5, 0x25, 0x01, 4, 2}); // says 4 jacks, has room for 1

		auto jacks = parse(c.finish());
		CHECK(jacks.num_rx_cables == 1);
		CHECK(jacks.rx_cable_out_jack_idx[0] == 0);
	}

	SUBCASE("empty and stub configurations") {
		MidiJackCollection jacks;
		parse_midi_jacks(std::span<uint8_t const>{}, &jacks);
		CHECK(jacks.num_in_jacks == 0);
		CHECK(jacks.num_rx_cables == 0);

		std::vector<uint8_t> short_cfg{9, 0x02, 9, 0};
		MidiJackCollection jacks2;
		parse_midi_jacks(short_cfg, &jacks2);
		CHECK(jacks2.num_out_jacks == 0);
	}
}

TEST_CASE("count_midi_jacks agrees with parse_midi_jacks") {
	auto cfg = simple_device().finish();

	uint8_t num_in = 0;
	uint8_t num_out = 0;
	count_midi_jacks(cfg, &num_in, &num_out);

	auto jacks = parse(cfg);
	CHECK(num_in == jacks.num_in_jacks);
	CHECK(num_out == jacks.num_out_jacks);
}

TEST_CASE("An unnamed Embedded jack borrows the name of the External jack it's wired to") {
	// The device names only its physical sockets, which is where the useful
	// label often is: "DIN OUT", "DIN IN".
	auto jacks = parse(simple_device().finish());

	// Stand in for the name-string reads that collect_midi_jack_names() does.
	jacks.in_jacks[0].name.copy("");		// Embedded IN (jack 1): unnamed
	jacks.in_jacks[1].name.copy("DIN IN");	// External IN (jack 3)
	jacks.out_jacks[0].name.copy("");		// Embedded OUT (jack 4): unnamed
	jacks.out_jacks[1].name.copy("DIN OUT"); // External OUT (jack 2)

	borrow_external_jack_names(&jacks);

	// Embedded OUT jack 4 is sourced from External IN jack 3
	CHECK(std::string_view{jacks.out_jacks[0].name.c_str()} == "DIN IN");
	// Embedded IN jack 1 feeds External OUT jack 2
	CHECK(std::string_view{jacks.in_jacks[0].name.c_str()} == "DIN OUT");
}

TEST_CASE("A jack with its own name keeps it") {
	auto jacks = parse(simple_device().finish());

	jacks.in_jacks[0].name.copy("Keys");
	jacks.in_jacks[1].name.copy("DIN IN");
	jacks.out_jacks[0].name.copy("Pads");
	jacks.out_jacks[1].name.copy("DIN OUT");

	borrow_external_jack_names(&jacks);

	CHECK(std::string_view{jacks.in_jacks[0].name.c_str()} == "Keys");
	CHECK(std::string_view{jacks.out_jacks[0].name.c_str()} == "Pads");
	// External jacks are left alone either way
	CHECK(std::string_view{jacks.in_jacks[1].name.c_str()} == "DIN IN");
	CHECK(std::string_view{jacks.out_jacks[1].name.c_str()} == "DIN OUT");
}

TEST_CASE("copy_midi_jacks publishes counts, jacks and cable maps") {
	auto jacks = parse(simple_device().finish());
	jacks.out_jacks[0].name.copy("Port 1");

	UsbDeviceState state;
	copy_midi_jacks(jacks, state);

	CHECK(state.status.num_midi_in_jacks == 2);
	CHECK(state.status.num_midi_out_jacks == 2);
	CHECK(state.status.num_midi_rx_cables == 1);
	CHECK(state.status.num_midi_tx_cables == 1);
	CHECK(state.rx_cable_out_jack_idx[0] == 0);
	CHECK(state.tx_cable_in_jack_idx[0] == 0);
	CHECK(std::string_view{state.midi_out_jacks[0].name.c_str()} == "Port 1");
	CHECK(state.midi_out_jacks[0].cable_num == 0);
	CHECK(state.midi_out_jacks[0].has_cable);

	// Cable slots the device never declared stay marked as empty
	CHECK(state.rx_cable_out_jack_idx[1] == NoJackIdx);
	CHECK(state.tx_cable_in_jack_idx[1] == NoJackIdx);
}
