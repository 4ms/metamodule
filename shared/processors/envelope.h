#pragma once

#include "processors/tools/windowComparator.h"
#include "util/math.hh"

using namespace MathTools;

class Envelope {
private:
	int stage = 0;
	int sampleRate = 48000;
	uint32_t phaccu = 0;
	uint32_t lastPhaccu = 0;
	uint32_t increment = 0;
	static constexpr uint32_t max_ = 0xFFFFFFFF;
	float envTimes[4] = {1000, 1000, 1000, 1000};
	float sustainLevel = 0.5f;
	float lastSample = 0;
	float envOut =0;

	bool lastGate;
	WindowComparator gateInput;

public:
	Envelope() {}
	float update(float input)
	{
		lastGate = gateInput.get_output();
		gateInput.update(input);
		if (gateInput.get_output() > lastGate) {
			phaccu = 0;
			stage = 0;
		}
		if (gateInput.get_output() < lastGate) {
			phaccu = 0;
			stage = 4;
		}
		int stageSelect = 0;
		if (stage < 3)
			stageSelect = stage;
		else {
			stageSelect = 3;
		}

		increment = 1000.0f / envTimes[stageSelect] * (max_ / sampleRate);

		lastPhaccu = phaccu;
		phaccu += increment;
		if (phaccu < lastPhaccu) // overflow
		{
			if (stage < 3 || stage==4)
				stage++;
		}
		if (stage == 0) {
			envOut = (float)phaccu / (float)max_;
		} else if (stage == 1) {
		} else if (stage == 2) {
			envOut = map_value((float)phaccu / (float)max_, 0.0f, 1.0f, 1.0f, sustainLevel);
		} else if (stage == 3) {
			envOut = sustainLevel;
		} else if (stage == 4) {
			envOut = map_value((float)phaccu / (float)max_, 0.0f, 1.0f, lastSample, 0.0f);
		}

		if(stage<4)
		lastSample=envOut;
		
		return envOut;
	}

	void set_envelope_time(int _envStage, float milliseconds)
	{
		envTimes[_envStage] = milliseconds;
	}

	void set_samplerate(float sr)
	{
		sampleRate = sr;
	}

    void set_sustain(float _sustainLevel)
    {
        sustainLevel = _sustainLevel;
    }
};