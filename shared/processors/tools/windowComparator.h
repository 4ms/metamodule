#pragma once

class WindowComparator {
public:
	bool update(float input)
	{
		if (input > highThresh)
			output = true;
		if (input < lowThresh)
			output = false;

		return output;
	}

private:
	const float lowThresh = 0.1f;
	const float highThresh = 0.5f;
	bool output = false;
};