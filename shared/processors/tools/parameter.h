#pragma once

template<typename T>
class Parameter {
public:
	void setValue(T input)
	{
		oldVal = currentVal;
		currentVal = input;

		if (oldVal != currentVal)
			changed = 1;
	}

	bool isChanged()
	{
		bool changeStatus = changed;
		changed = 0;
		return changeStatus;
	}

	T getValue()
	{
		return currentVal;
	}

private:
	T currentVal = 0;
	T oldVal;
	bool changed = 1;
};