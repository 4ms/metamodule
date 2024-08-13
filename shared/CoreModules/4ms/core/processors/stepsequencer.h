#pragma once

class StepSequencer {
public:
	StepSequencer(int steps)
	{
		for (int i = 0; i < 16; i++) {
			values[i] = 0.0f;
		}
		if (numSteps <= 16)
			numSteps = steps;
	}

	void update()
	{
		if (currentClock > lastClock) {
			currentStep++;
			if (currentStep >= numSteps)
				currentStep = 0;
		}

		if (currentReset > lastReset) {
			currentStep = 0;
		}

		output = values[currentStep];
		if (currentStep == 0) {
			endOutput = 1;
		} else
			endOutput = 0;
	}

	void setStep(int stepToSet, float value)
	{
		values[stepToSet] = value;
	}

	void setLength(int _numSteps)
	{
		numSteps=_numSteps;
	}

	void updateClock(float input)
	{
		lastClock = currentClock;
		if (input > 0.0f) {
			currentClock = 1;
		} else
			currentClock = 0;
	}

	void updateReset(float input)
	{
		lastReset = currentReset;
		if (input > 0.0f) {
			currentReset = 1;
		} else
			currentReset = 0;
	}

	float output;
	float endOutput;

private:
	int numSteps = 8;
	int currentStep = 0;

	int currentClock = 0;
	int lastClock = 0;
	int currentReset = 0;
	int lastReset = 0;

	float values[16];
};