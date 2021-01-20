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

private:
	const float lowThresh = 0.1f;
	const float highThresh = 0.5f;
	bool output = false;
};