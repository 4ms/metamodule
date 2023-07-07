#pragma once
#include "VCV-adaptor/simd/Vector.hpp"

struct Port {
	float voltage = 0.f;
	bool connected = false;

	float getVoltage(int chan = 0) const {
		return voltage;
	}

	template<typename T>
	T getVoltageSimd(int firstChannel) {
		return T(voltage); // return vector with all elements set to voltage
	}

	float getVoltageSum() const {
		return getVoltage();
	}

	void setVoltage(float v, int chan = 0) {
		voltage = v;
	}

	template<typename T>
	void setVoltageSimd(T v, int firstChannel) {
		voltage = v[0];
	}

	void setVoltageSimd(float v, int firstChannel) {
		voltage = v;
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

	void setChannels(int) {
	}

	int getChannels() const {
		return connected ? 1 : 0;
	}
};

// struct PortSimd {
// 	static constexpr int MAX_CHANNELS = 4;
// 	float voltages[MAX_CHANNELS]{};
// 	bool connected = false;

// 	float getVoltage(int chan = 0) const {
// 		if (chan < MAX_CHANNELS && chan >= 0)
// 			return voltages[chan];
// 	}

// 	template<typename T>
// 	T getVoltageSimd(int firstChannel) {
// 		if (firstChannel < MAX_CHANNELS && firstChannel >= 0)
// 			return T::load(&voltages[firstChannel]);
// 	}

// 	float getVoltageSum() const {
// 		return getVoltage();
// 	}

// 	void setVoltage(float voltage, int chan = 0) {
// 		if (chan < MAX_CHANNELS && chan > 0)
// 			voltages[chan] = voltage;
// 	}

// 	template<typename T>
// 	void setVoltageSimd(T voltage, int firstChannel) {
// 		voltage.store(&voltages[firstChannel]);
// 	}

// 	bool isConnected() const {
// 		return connected;
// 	}

// 	bool isMonophonic() const {
// 		return connected;
// 	}

// 	bool isPolyphonic() const {
// 		return false;
// 	}

// 	void setChannels(int) {
// 	}

// 	int getChannels() const {
// 		return connected ? 1 : 0;
// 	}
// };
