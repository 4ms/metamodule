#pragma once

class ClockPhase {
public:
	void updateClock(float val)
	{
		lastClock = currentClock;
		currentClock = val > 0.0f;

		if (currentClock > lastClock) {
			duration = sinceClock;
			sinceClock = 0;
			wholeCount++;
		}
	}

	void updateReset(float val)
	{
		lastReset = currentReset;
		currentReset = val > 0.0f;
		if (currentReset > lastReset)
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
		multiply = val;
	}

	void setDivide(int val)
	{
		divide = val;
	}

private:
	int currentClock = 0;
	int lastClock = 0;

	int currentReset = 0;
	int lastReset = 0;

	long wholeCount = 0;

	long sinceClock = 0;

	float phase = 0;

	long duration = 1000;

	float tempPhase = 0;

	int multiply = 1;

	int divide = 1;
};