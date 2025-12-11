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

	// Set channel
	channel = getChannel();
	if (channel >= 0 && status.command != MidiCommand::Sys) {
		status.channel = channel;
	}

	msg.status = status;
	msg.data.byte[0] = message.bytes[1];
	msg.data.byte[1] = message.bytes[2];

	if (status.command == MidiCommand::Sys) {
		msg.usb_hdr.cin = UsbCableCodeByte::cin_from_status_byte(status);
	} else
		msg.usb_hdr.cin = std::to_underlying(status.command);

	msg.usb_hdr.cable_num = message.getUsbCable();

	internal->queue.put(msg);
}

} // namespace rack::midi
