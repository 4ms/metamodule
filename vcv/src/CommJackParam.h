#pragma once

#include "CommData.h"
#include "plugin.hpp"

struct CommInputJack {
private:
	float _value = 0;
	Port &_inputPort;
	int _jackID = 0;
	int _moduleID = -1;

public:
	JackStatus inputJackStatus;
	std::function<float(float)> scale = [](float f) { return f; };

	CommInputJack(Port &inputPort, int jackID)
		: _inputPort{inputPort}
		, _jackID{jackID}
	{
	}

	void setModuleID(int moduleID)
	{
		_moduleID = moduleID;
	}

	void updateInput()
	{
		inputJackStatus.sendingJackId = _jackID;
		inputJackStatus.sendingModuleId = _moduleID;
		inputJackStatus.connected = _inputPort.isConnected();
		if (inputJackStatus.connected) {
			_value = _inputPort.getPolyVoltage(0);
			inputJackStatus.receivedJackId = _inputPort.getPolyVoltage(1);
			inputJackStatus.receivedModuleId = _inputPort.getPolyVoltage(2);
		}
	}

	float getValue()
	{
		return _value;
	}

	int getID()
	{
		return _jackID;
	}
};

struct CommOutputJack {
private:
	float _value = 0;
	Port &_outputPort;
	int _jackID = -1;
	int _moduleID = -1;

public:
	std::function<float(float)> scale = [](float f) { return f; };

	CommOutputJack(Port &outputPort, int jackID)
		: _outputPort{outputPort}
		, _jackID{jackID}
	{
	}

	void setModuleID(int moduleID)
	{
		_moduleID = moduleID;
	}

	void updateOutput()
	{
		_outputPort.setChannels(3);
		_outputPort.setVoltage(_value, 0);
		_outputPort.setVoltage(_jackID, 1);
		_outputPort.setVoltage(_moduleID, 2);
	}

	void setValue(float in)
	{
		_value = in;
	}

	int getID()
	{
		return _jackID;
	}
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

	void setModuleID(int moduleID)
	{
		paramStatus.moduleID = moduleID;
	}

	void updateValue()
	{
		paramStatus.value = _inParam.getValue();
	}

	float getValue()
	{
		return paramStatus.value;
	}

	int getID()
	{
		return paramStatus.paramID;
	}
};

