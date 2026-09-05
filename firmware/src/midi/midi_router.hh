#pragma once
#include "midi/midi_message.hh"
#include "midi/midi_queue.hh"
#include <optional>

namespace MetaModule
{

struct MidiRouter {

	// MIDI RX:
	static void subscribe_rx(MidiQueue *listener);
	static void unsubscribe_rx(MidiQueue *listener);

	// When hardware receives a MIDI message, it calls this
	// to forward the msg to all listeners, tagged with the port it arrived on
	static void push_incoming_message(MidiMessage msg, uint8_t port);

	// MIDI TX:
	static void subscribe_tx(MidiQueue *listener);
	static void unsubscribe_tx(MidiQueue *listener);

	// Used by MidiSync since it's always subscribed,
	// but shouldn't count towards has_patch_subscribers().
	static void subscribe_tx_system(MidiQueue *outqueue);
	static void unsubscribe_tx_system(MidiQueue *outqueue);

	// Pop the latest message ready to be sent out via hardware
	static std::optional<PortedMidiMessage> pop_outgoing_message();

	// True if the there are any patch-level input or output subscribers
	static bool has_patch_subscribers();
};

} // namespace MetaModule
