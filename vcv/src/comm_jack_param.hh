#pragma once
#include "CommData.hh"
#include "plugin.hh"

struct CommInputJack {
private:
	float _value = 0;
	Port &_inputPort;
	int _jackID = 0;
	bool _just_unpatched = true;
	bool _just_patched = false;

public:
	JackStatus inputJackStatus;
	std::function<float(float)> scale = [](float f) { return f; };

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

struct CommOutputJack {
private:
	float _value = 0;
	Port &_outputPort;
	int _jackID = -1;
	int64_t _moduleID = -1;

public:
	std::function<float(float)> scale = [](float f) { return f; };

	CommOutputJack(Port &outputPort, int jackID)
		: _outputPort{outputPort}
		, _jackID{jackID}
	{}

	void setModuleID(int64_t moduleID) { _moduleID = moduleID; }

	void updateOutput()
	{
		_outputPort.setChannels(1);
		_outputPort.setVoltage(_value);
	}

	void updateOutputWithCommData()
	{
		_outputPort.setChannels(5);
		_outputPort.setVoltage(_value, 0);
		_outputPort.setVoltage(_jackID, 1);
		_outputPort.setVoltage(_moduleID, 2);
		// Ensure sum of all channels = _value
		_outputPort.setVoltage(-1 * _jackID, 3);
		_outputPort.setVoltage(-1 * _moduleID, 4);
	}

	void setValue(float in) { _value = in; }

	int getID() { return _jackID; }
};

class CommParam {
	Param &_inParam;

public:
	ParamStatus paramStatus;

	CommParam(Param &inParam, int paramID)
		: _inParam{inParam}
	{
		paramStatus.paramID = paramID;
	}

	void setModuleID(int64_t moduleID) { paramStatus.moduleID = moduleID; }

	void updateValue() { paramStatus.value = _inParam.getValue(); }

	float getValue() { return paramStatus.value; }

	int getID() { return paramStatus.paramID; }
};
