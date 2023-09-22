#pragma once

#include "windowComparator.h"

class ClockPhase {
public:
	void updateClock(float val) {
		lastClock = currentClock.output();
		currentClock.update(val);

		if (currentClock.output() > lastClock) {
			multiply = queueMultiply;
			divide = queueDivide;
			duration = sinceClock;
			sinceClock = 0;
			wholeCount++;
		}
	}

	void updateReset(float val) {
		lastReset = currentReset.output();
		currentReset.update(val);
		if (currentReset.output() > lastReset)
			wholeCount = 0;
	}

	void update() {
		tempPhase = (float)sinceClock / (float)duration;
		if (tempPhase < 1.0f) {
			auto ratio = multiply / divide;
			phase = (wholeCount + tempPhase) * ratio;
		}
		sinceClock++;
	}

	float getPhase() {
		return (phase);
	}

	float getWrappedPhase() {
		return (phase - (long)phase);
	}

	long getCount() {
		return wholeCount;
	}

	void setMultiply(int val) {
		queueMultiply = static_cast<float>(val);
	}

	void setDivide(int val) {
		queueDivide = static_cast<float>(val);
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
	float multiply = 1;
	float divide = 1;
	float queueDivide = 1;
	float queueMultiply = 1;
};
