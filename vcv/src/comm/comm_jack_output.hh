#pragma once

#include <rack.hpp>

struct CommOutputJack {
private:
	float _value = 0;
	rack::Port &_outputPort;
	int _jackID = -1;
	int64_t _moduleID = -1;

public:
	float scaleFactor = 5.f; // CoreModule ouput of -1 to +1 => -5V to +5V in VCV

	CommOutputJack(rack::Port &outputPort, int jackID)
		: _outputPort{outputPort}
		, _jackID{jackID} {
	}

	void setModuleID(int64_t moduleID) {
		_moduleID = moduleID;
	}

	void updateOutput() {
		_outputPort.setChannels(1);
		_outputPort.setVoltage(_value);
	}

	void updateOutputWithCommData() {
		_outputPort.setChannels(5);
		_outputPort.setVoltage(_value, 0);
		_outputPort.setVoltage(_jackID, 1);
		_outputPort.setVoltage(_moduleID, 2);
		// Ensure sum of all channels = _value
		_outputPort.setVoltage(-1 * _jackID, 3);
		_outputPort.setVoltage(-1 * _moduleID, 4);
	}

	void setValue(float in) {
		_value = in;
	}

	int getID() {
		return _jackID;
	}
};
