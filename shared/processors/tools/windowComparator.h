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
			output = true;
		if (input < lowThresh)
			output = false;
	}

	bool get_output() {
		return output;
	}

	void set_lowThreshhold(float lowVal) {
		lowThresh = lowVal;
	}

	void set_highThreshold(float highVal) {
		highThresh = highVal;
	}

private:
	float lowThresh = 0.1f;
	float highThresh = 0.5f;
	bool output = false;
};
