#pragma once

#include "windowComparator.h"

class ClockToSamples {
public:
	void update(float signalInput)
	{
		wc.update(signalInput);
		lastClock = currentClock;
		currentClock = wc.get_output();
		if (currentClock > lastClock) {
			lastDuration = currentDuration;
			currentDuration = sinceClock;
			pulseCount++;
			float ratio = currentDuration / lastDuration;
			if (ratio > (1 - error) && ratio < (1 + error)) {
				if(pulseCount==2)
				{
					finalDuration=currentDuration;
				}
				else if(pulseCount>2)
				finalDuration = (finalDuration + currentDuration) / 2.0f;
			}
			else
			{
				pulseCount=1;
			}
			
			sinceClock = 0;
		}
		sinceClock++;
	}

	float getSamples()
	{
		return finalDuration;
	}

private:
	WindowComparator wc;
	float lastClock = 0;
	float currentClock = 0;
	long sinceClock = 0;
	float currentDuration = 0;
	float lastDuration = 0;
	int pulseCount = 0;
	const float error = 0.1f;
	float finalDuration = 0;
};