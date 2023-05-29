#pragma once

struct Port {
	float voltage = 0.f;
	bool connected = false;
	float getVoltage() const {
		return voltage;
	}
	float getVoltage(int) const {
		return getVoltage();
	}
	template<typename T>
	T getVoltageSimd(int firstChannel) const {
		return getVoltage();
	}
	float getVoltageSum() const {
		return getVoltage();
	}

	void setVoltage(float voltage, int channel = 0) {
		this->voltage = voltage;
	}
	template<typename T>
	void setVoltageSimd(T voltage, int firstChannel) {
		setVoltage(voltage, 0);
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
