#pragma once
#include "VCV_adaptor/common.hpp"
#include "VCV_adaptor/engine/Light.hpp"

namespace rack::engine
{

static const int PORT_MAX_CHANNELS = 4;

struct Port {
	float voltage = 0.f;
	bool connected = false;
	// 	float voltages[PORT_MAX_CHANNELS] = {};
	// 	uint8_t channels = 0;

	// TODO?
	// Light plugLights[3];

	enum Type {
		INPUT,
		OUTPUT,
	};

	void setVoltage(float v, int channel = 0) {
		// voltages[channel] = v;
		voltage = v;
	}

	float getVoltage(int chan = 0) const {
		return voltage;
	}

	float getPolyVoltage(int channel) const {
		return isMonophonic() ? getVoltage(0) : getVoltage(channel);
	}

	float getNormalVoltage(float normalVoltage, int channel = 0) const {
		return isConnected() ? getVoltage(channel) : normalVoltage;
	}

	float getNormalPolyVoltage(float normalVoltage, int channel) const {
		return isConnected() ? getPolyVoltage(channel) : normalVoltage;
	}

	float *getVoltages(int firstChannel = 0) {
		return &voltage;
	}

	void readVoltages(float *v) const {
		v[0] = voltage;
	}

	void writeVoltages(const float *v) {
		voltage = v[0];
	}

	void clearVoltages() {
		voltage = 0;
	}

	float getVoltageSum() const {
		return voltage;
	}

	float getVoltageRMS() const {
		return connected ? std::fabs(voltage) : 0;
	}

	template<typename T>
	T getVoltageSimd(int firstChannel) const {
		return T(voltage); // return vector with all elements set to voltage
	}

	template<typename T>
	T getPolyVoltageSimd(int firstChannel) const {
		return isMonophonic() ? getVoltage(0) : getVoltageSimd<T>(firstChannel);
	}

	template<typename T>
	T getNormalVoltageSimd(T normalVoltage, int firstChannel) const {
		return isConnected() ? getVoltageSimd<T>(firstChannel) : normalVoltage;
	}

	template<typename T>
	T getNormalPolyVoltageSimd(T normalVoltage, int firstChannel) const {
		return isConnected() ? getPolyVoltageSimd<T>(firstChannel) : normalVoltage;
	}

	template<typename T>
	void setVoltageSimd(T v, int firstChannel) {
		voltage = v[0];
		// v.store(&voltages[firstChannel]);
	}

	void setChannels(int channels) {
	}

	int getChannels() const {
		return connected ? 1 : 0;
	}

	bool isConnected() const {
		return connected;
	}

	bool isMonophonic() const {
		return connected;
	}

	bool isPolyphonic() const {
		return false;
	}

	DEPRECATED float normalize(float normalVoltage) const {
		return getNormalVoltage(normalVoltage);
	}
};

struct Output : Port {};

struct Input : Port {};

} // namespace rack::engine
