#pragma once
#include "midi/midi_message.hh"
#include "util/lockfree_fifo_spsc.hh"
#include <optional>
#include <vector>

// SimMidi: real MIDI input/output for the simulator, built on rtmidi.
//
// This is the host-side stand-in for the firmware's USB-MIDI hardware. On real
// hardware the M4 `Controls` class owns the USB-MIDI device: an ISR callback
// pushes received 4-byte packets into a LockFreeFifoSpsc, and the audio core
// drains them. SimMidi mirrors that exactly using rtmidi:
//   - rtmidi delivers incoming messages on its own thread; the callback converts
//     them to MidiMessage and pushes into an SPSC FIFO (producer thread).
//   - The audio thread drains the FIFO via get_incoming() (consumer thread) and
//     sends outgoing messages via send().
//
// If rtmidi is not compiled in (SIM_HAS_RTMIDI undefined, e.g. the submodule was
// not initialized or no platform MIDI API is available) SimMidi degrades to an
// inert no-op: is_connected() is false, get_incoming() returns nothing and send()
// does nothing, so the simulator runs exactly as before minus MIDI.

namespace MetaModule
{

class SimMidi {
public:
	struct Config {
		// Hardware port index to open. If unset, a virtual port is created instead
		// (so DAWs/controllers can connect to the running simulator). Virtual ports
		// are supported on ALSA and CoreMIDI, but not on Windows MM.
		std::optional<int> in_port{};
		std::optional<int> out_port{};
	};

	explicit SimMidi(Config config);
	~SimMidi();

	SimMidi(const SimMidi &) = delete;
	SimMidi &operator=(const SimMidi &) = delete;

	// True once at least one port (in or out) opened successfully.
	bool is_connected() const {
		return connected_;
	}

	// Consumer side (audio thread): pop one received message if available.
	std::optional<MidiMessage> get_incoming() {
		return rx_fifo_.get();
	}

	// Send an outgoing message out the MIDI port (audio thread).
	void send(MidiMessage msg);

	// Print the available MIDI input/output ports to stdout (for `--listmidi`).
	static void list_ports();

private:
	LockFreeFifoSpsc<MidiMessage, 256> rx_fifo_;
	bool connected_ = false;

	// Opaque holder for the rtmidi objects (RtMidiIn/RtMidiOut), defined only in
	// sim_midi.cc so this header stays free of RtMidi.h and its namespace. Null in
	// an inert (stub) build.
	struct Impl;
	Impl *impl_ = nullptr;

	// rtmidi input callback (runs on rtmidi's thread).
	static void rx_callback(double timestamp, std::vector<unsigned char> *message, void *userdata);
	void push_incoming(const std::vector<unsigned char> &bytes);
};

} // namespace MetaModule
