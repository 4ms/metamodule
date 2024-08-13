#pragma once

class SchmittTrigger {
public:
	SchmittTrigger() = default;

	SchmittTrigger(float lowThreshold, float highThreshold)
		: lowThresh{lowThreshold}
		, highThresh{highThreshold} {
		if (lowThresh > highThresh)
			highThresh = lowThresh;
	}

	bool update(float input) {
		if (input > highThresh)
			out = true;
		else if (input < lowThresh)
			out = false;
		return out;
	}

	bool output() {
		return out;
	}

	void setLowThreshhold(float lowVal) {
		lowThresh = lowVal;
		if (lowThresh > highThresh)
			highThresh = lowThresh;
	}

	void setHighThreshold(float highVal) {
		highThresh = highVal;
		if (lowThresh > highThresh)
			highThresh = lowThresh;
	}

private:
	float lowThresh = 0.1f;
	float highThresh = 0.5f;
	bool out = false;
};
