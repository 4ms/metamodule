#pragma once

class WindowComparator {
public:
	void update(float input)
	{
		if (input > highThresh)
			output = true;
		if (input < lowThresh)
			output = false;
	}

	bool get_output()
	{
		return output;
	}

	void set_lowThreshhold(float lowVal)
	{
		lowThresh = lowVal;
	}

	void set_highThreshold(float highVal)
	{
		highThresh = highVal;
	}

private:
	float lowThresh = 0.1f;
	float highThresh = 0.5f;
	bool output = false;
};