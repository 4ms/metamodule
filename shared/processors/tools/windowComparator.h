#pragma once

class WindowComparator {
public:
	WindowComparator() = default;

	WindowComparator(float lowThreshold, float highThreshold)
		: lowThresh{lowThreshold}
		, highThresh{highThreshold} {
	}

	void update(float input) {
		if (input > highThresh)
			out = true;
		if (input < lowThresh)
			out = false;
	}

	bool output() {
		return out;
	}

	void setLowThreshhold(float lowVal) {
		lowThresh = lowVal;
	}

	void setHighThreshold(float highVal) {
		highThresh = highVal;
	}

private:
	float lowThresh = 0.1f;
	float highThresh = 0.5f;
	bool out = false;
};
