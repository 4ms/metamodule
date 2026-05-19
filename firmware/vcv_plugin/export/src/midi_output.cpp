#include "midi.hpp"
#include "midi/midi_queue.hh"
#include "midi/midi_router.hh"
#include <utility>

namespace rack::midi
{

struct Output::Internal {
	MetaModule::MidiQueue queue;
};

Output::Output()
	: internal(new Internal) {
	MetaModule::MidiRouter::subscribe_tx(&internal->queue);
	reset();
}

Output::~Output() {
	setDeviceId(-1);
	MetaModule::MidiRouter::unsubscribe_tx(&internal->queue);
	delete internal;
}

void Output::reset() {
	setDriverId(-1);
	channel = 0;
}

std::vector<int> Output::getDeviceIds() {
	return {1};
}

void Output::setDeviceId(int deviceId) {
	//
}

int Output::getDefaultDeviceId() {
	return -1;
}

std::string Output::getDeviceName(int deviceId) {
	return "USB-C MIDI";
}

std::vector<int> Output::getChannels() {
	return {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
}

void Output::sendMessage(const Message &message) {
	// Convert from rack::midi::Message to MidiMessage
	MidiMessage msg;

	auto status = MidiStatusByte::make(message.bytes[0]);

	// Set channel if it's a voice message (note on/off, cc, etc)
	channel = getChannel();
	if (channel >= 0 && uint8_t(status.command) >= 0x8 && uint8_t(status.command) <= 0xE) {
		status.channel = channel;
	}

	msg.status = status;
	msg.data.byte[0] = message.bytes[1];
	msg.data.byte[1] = message.bytes[2];

	// Set the usb code here since the Rack::midi object might have
	// knowledge about sysex packet length.
	msg.usb_hdr.cin = message.usb_code;
	msg.usb_hdr.cable_num = message.getUsbCable();

	internal->queue.put(msg);
}

} // namespace rack::midi
