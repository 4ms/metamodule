#pragma once

#include "../mapping/ParamStatus.h"

#include <rack.hpp>
using namespace rack;

class CommParam {
	Param &_inParam;

public:
	ParamStatus paramStatus;
	float scaleFactor = 1.0f;

	CommParam(Param &inParam, int paramID)
		: _inParam{inParam}
	{
		paramStatus.paramID = paramID;
	}

	void setModuleID(int64_t moduleID) { paramStatus.moduleID = moduleID; }

	// paramStatus.value is sent to CentralData (to be written with patch)
	void updateValue() { paramStatus.value = _inParam.getValue() * scaleFactor; }

	// result of getValue() is sent to the CoreModule
	float getValue() { return paramStatus.value; }

	int getID() { return paramStatus.paramID; }
};
