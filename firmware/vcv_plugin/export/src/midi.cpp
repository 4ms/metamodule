#include <tuple>
#include <utility>

#include "midi/midi_message.hh" // MetaModule::Midi::Port
#include <context.hpp>
#include <engine/Engine.hpp>
#include <midi.hpp>
#include <string.hpp>
#include <system.hpp>

namespace rack::midi
{

static std::vector<std::pair<int, Driver *>> drivers;

std::string Message::toString() const {
	std::string s;
	for (size_t i = 0; i < bytes.size(); i++) {
		if (i > 0)
			s += " ";
		uint8_t b = bytes[i];
		// We could use string::f() here, but use faster method instead.
		// s += string::f("%02x", b);
		uint8_t b1 = (b & 0x0f) >> 0;
		uint8_t b2 = (b & 0xf0) >> 4;
		s += b2 < 0xa ? ('0' + b2) : ('a' + b2 - 0xa);
		s += b1 < 0xa ? ('0' + b1) : ('a' + b1 - 0xa);
	}
	return s;
}

////////////////////
// Device
////////////////////

void InputDevice::subscribe(Input *input) {
}

void InputDevice::unsubscribe(Input *input) {
}

void InputDevice::onMessage(const Message &message) {
}

void OutputDevice::subscribe(Output *output) {
}

void OutputDevice::unsubscribe(Output *output) {
}

////////////////////
// Port
////////////////////

Port::Port()
	: driverId{0}
	, context(contextGet()) {
}

Port::~Port() = default;

Driver *Port::getDriver() {
	return driver;
}

int Port::getDriverId() {
	return driverId;
}

void Port::setDriverId(int driverId) {
	this->driverId = 0;
	// There's only one driver, so changing it just resets the device choice.
	// Use the default rather than 0, which is a real port (USB).
	setDeviceId(getDefaultDeviceId());
}

Device *Port::getDevice() {
	return device;
}

int Port::getDeviceId() {
	return deviceId;
}

int Port::getChannel() {
	return channel;
}

void Port::setChannel(int channel) {
	this->channel = channel;
}

std::string Port::getChannelName(int channel) {
	if (channel < 0)
		return "All channels";
	else
		return string::f("Channel %d", channel + 1);
}

json_t *Port::toJson() {
	json_t *rootJ = json_object();
	json_object_set_new(rootJ, "driver", json_integer(getDriverId()));

	// METAMODULE: there are no Device objects -- a device is a physical MIDI
	// port -- so ask the port itself for the name rather than Device::getName().
	std::string deviceName = getDeviceName(getDeviceId());
	if (!deviceName.empty())
		json_object_set_new(rootJ, "deviceName", json_string(deviceName.c_str()));

	json_object_set_new(rootJ, "channel", json_integer(getChannel()));
	return rootJ;
}

void Port::fromJson(json_t *rootJ) {
	setDriverId(-1);

	json_t *driverJ = json_object_get(rootJ, "driver");
	if (driverJ)
		setDriverId(json_integer_value(driverJ));

	// METAMODULE: match by name as Rack does, but without needing a Driver.
	// AllDevices is named too, so it round-trips like any other choice.
	json_t *deviceNameJ = json_object_get(rootJ, "deviceName");
	if (deviceNameJ) {
		std::string deviceName = json_string_value(deviceNameJ);

		if (getDeviceName(AllDevices) == deviceName) {
			setDeviceId(AllDevices);
		} else {
			for (int deviceId : getDeviceIds()) {
				if (getDeviceName(deviceId) == deviceName) {
					setDeviceId(deviceId);
					break;
				}
			}
		}
	}

	json_t *channelJ = json_object_get(rootJ, "channel");
	if (channelJ)
		channel = json_integer_value(channelJ);
}

////////////////////
// Input
////////////////////

Input::Input() {
	reset();
}

Input::~Input() = default;

void Input::reset() {
}

// METAMODULE: a MIDI "device" is one of the hardware's physical MIDI ports.
// Modules pick one through the standard Rack device API, and messages from the
// others are filtered out (see InputQueue::tryPop).
std::vector<int> Input::getDeviceIds() {
	return {MetaModule::Midi::USB, MetaModule::Midi::TRS, MetaModule::Midi::DIN5};
}

int Input::getDefaultDeviceId() {
	return AllDevices;
}

void Input::setDeviceId(int deviceId) {
	this->deviceId = deviceId;
}

std::string Input::getDeviceName(int deviceId) {
	switch (deviceId) {
		case MetaModule::Midi::USB:
			return "USB";
		case MetaModule::Midi::TRS:
			return "TRS";
		case MetaModule::Midi::DIN5:
			return "DIN5";
		default:
			return "All";
	}
}

std::vector<int> Input::getChannels() {
	return {};
}

////////////////////
// InputQueue
////////////////////

// See midi_input_queue.cpp

////////////////////
// Output
////////////////////

// See midi_output.cpp

////////////////////
// midi
////////////////////

void init() {
}

void destroy() {
}

void addDriver(int driverId, Driver *driver) {
	//TODO: main firmware calls this on init to add the drivers
}

std::vector<int> getDriverIds() {
	return {};
}

Driver *getDriver(int driverId) {
	return nullptr;
}

} // namespace rack::midi
