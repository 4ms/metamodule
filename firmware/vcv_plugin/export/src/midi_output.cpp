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

// METAMODULE: a MIDI "device" is one of the hardware's physical MIDI ports.
std::vector<int> Output::getDeviceIds() {
	return {MetaModule::Midi::USB, MetaModule::Midi::TRS, MetaModule::Midi::DIN5};
}

void Output::setDeviceId(int deviceId) {
	this->deviceId = deviceId;
}

int Output::getDefaultDeviceId() {
	// Patches saved before the expander existed have no stored port, and their
	// MIDI went out the USB-C jack. Keep that the default so they load unchanged.
	return MetaModule::Midi::USB;
}

std::string Output::getDeviceName(int deviceId) {
	switch (deviceId) {
		case MetaModule::Midi::USB:
			return "USB";
		case MetaModule::Midi::TRS:
			return "TRS";
		case MetaModule::Midi::DIN5:
			return "DIN5";
		default:
			// Not a port, so it never matches a stored name in Port::fromJson,
			// and Port::toJson skips writing it.
			return "";
	}
}

std::vector<int> Output::getChannels() {
	return {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
}

void Output::sendMessage(const Message &message) {
	using namespace MetaModule;
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

	// Tag with the destination jack the module is set to, so the router and the
	// M4 can send it out that port and no other.
	internal->queue.data.put({msg, uint8_t(getDeviceId())});
}

} // namespace rack::midi
