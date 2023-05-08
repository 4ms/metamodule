#pragma once

#include "../mapping/JackStatus.h"

#include <rack.hpp>
using namespace rack;

struct CommInputJack {
private:
	float _value = 0;
	Port &_inputPort;
	int _jackID = 0;
	bool _just_unpatched = true;
	bool _just_patched = false;

public:
	JackStatus inputJackStatus;
	float scaleFactor = 1.f / 5.f; //-5V to +5V in VCV => -1..+1 in CoreModule

	CommInputJack(Port &inputPort, int jackID)
		: _inputPort{inputPort}
		, _jackID{jackID}
		, inputJackStatus{.sendingJackId = jackID, .connected = false}
	{
		// initially mark jacks as connected, so when module is added it triggers an just_unpatched event
		inputJackStatus.connected = true;
	}

	void setModuleID(int64_t moduleID) { inputJackStatus.sendingModuleId = moduleID; }

	void updateInput()
	{
		_just_unpatched = (inputJackStatus.connected && !_inputPort.isConnected());
		_just_patched = (!inputJackStatus.connected && _inputPort.isConnected());
		inputJackStatus.connected = _inputPort.isConnected();
		if (inputJackStatus.connected)
			_value = _inputPort.getPolyVoltage(0);
	}

	void updateWithCommData()
	{
		if (inputJackStatus.connected) {
			inputJackStatus.receivedJackId = _inputPort.getPolyVoltage(1);
			inputJackStatus.receivedModuleId = _inputPort.getPolyVoltage(2);
		}
	}

	float getValue() { return _value; }

	int getID() { return _jackID; }

	bool isJustPatched()
	{
		if (_just_patched) {
			_just_patched = false;
			return true;
		}
		return false;
	}

	bool isJustUnpatched()
	{
		if (_just_unpatched) {
			_just_unpatched = false;
			return true;
		}
		return false;
	}
};