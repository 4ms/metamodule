#pragma once

struct Port {
	float voltage = 0.f;
	bool connected = false;

	float getVoltage(int chan = 0) const {
		return voltage;
	}

	float getNormalVoltage(float normalVoltage, int chan = 0) const {
		return connected ? voltage : normalVoltage;
	}

	template<typename T>
	T getPolyVoltageSimd(int firstChannel) {
		return T(voltage); // return vector with all elements set to voltage
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
