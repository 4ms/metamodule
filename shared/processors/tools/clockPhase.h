#pragma once

#include "windowComparator.h"

class ClockPhase {
public:
	void updateClock(float val)
	{
		lastClock = currentClock.get_output();
		currentClock.update(val);

		if (currentClock.get_output() > lastClock) {
			multiply = queueMultiply;
			divide = queueDivide;
			duration = sinceClock;
			sinceClock = 0;
			wholeCount++;
		}
	}

	void updateReset(float val)
	{
		lastReset = currentReset.get_output();
		currentReset.update(val);
		if (currentReset.get_output() > lastReset)
			wholeCount = 0;
	}

	void update()
	{
		tempPhase = (float)sinceClock / (float)duration;
		if (tempPhase < 1.0f) {
			auto ratio = (float)multiply / (float)divide;
			phase = (wholeCount + tempPhase) * ratio;
		}
		sinceClock = sinceClock + 1;
	}

	float getPhase()
	{
		return (phase);
	}

	float getWrappedPhase()
	{
		return (phase - (long)phase);
	}

	long getCount()
	{
		return wholeCount;
	}

	void setMultiply(int val)
	{
		queueMultiply = val;
	}

	void setDivide(int val)
	{
		queueDivide = val;
	}

private:
	WindowComparator currentClock;
	int lastClock = 0;

	WindowComparator currentReset;
	int lastReset = 0;

	long wholeCount = 0;

	long sinceClock = 0;

	float phase = 0;

	long duration = 1000;

	float tempPhase = 0;

	int multiply = 1;

	int divide = 1;

	int queueDivide = 1;
	int queueMultiply = 1;
};