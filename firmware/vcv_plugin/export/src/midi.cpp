#include <tuple>
#include <utility>

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
	setDeviceId(0);
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

	if (device) {
		std::string deviceName = device->getName();
		if (!deviceName.empty())
			json_object_set_new(rootJ, "deviceName", json_string(deviceName.c_str()));
	}

	json_object_set_new(rootJ, "channel", json_integer(getChannel()));
	return rootJ;
}

void Port::fromJson(json_t *rootJ) {
	setDriverId(-1);

	json_t *driverJ = json_object_get(rootJ, "driver");
	if (driverJ)
		setDriverId(json_integer_value(driverJ));

	if (driver) {
		json_t *deviceNameJ = json_object_get(rootJ, "deviceName");
		if (deviceNameJ) {
			std::string deviceName = json_string_value(deviceNameJ);
			// Search for device ID with equal name
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

std::vector<int> Input::getDeviceIds() {
	return {};
}

int Input::getDefaultDeviceId() {
	return -1;
}

void Input::setDeviceId(int deviceId) {
}

std::string Input::getDeviceName(int deviceId) {
	return "";
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

Output::Output() {
	reset();
}

Output::~Output() {
	setDeviceId(-1);
}

void Output::reset() {
	setDriverId(-1);
	channel = 0;
}

std::vector<int> Output::getDeviceIds() {
	return {};
}

void Output::setDeviceId(int deviceId) {
}

int Output::getDefaultDeviceId() {
	return -1;
}

std::string Output::getDeviceName(int deviceId) {
	return "";
}

std::vector<int> Output::getChannels() {
	return {};
}

void Output::sendMessage(const Message &message) {
}

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
