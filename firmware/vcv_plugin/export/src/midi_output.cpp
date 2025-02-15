#include "midi.hpp"
#include "midi/midi_queue.hh"
#include "midi/midi_router.hh"

namespace rack::midi
{

Output::Output() {
}

Output::~Output() {
}

void Output::reset() {
}

std::vector<int> getDeviceIds() {
	return {1};
}

int getDefaultDeviceId() {
	return 1;
}

void setDeviceId(int deviceId) {
	//ignored
}

std::string getDeviceName(int deviceId) {
	return "USB-C MIDI";
}

std::vector<int> getChannels() {
	return {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
}

void sendMessage(const Message &message) {
	// TODO
}

} // namespace rack::midi
