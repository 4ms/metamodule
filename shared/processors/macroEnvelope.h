#pragma once

#include "processors/envelope.h"
#include "processors/tools/multiMap.h"

class MacroEnvelope {
private:
	Envelope e;
	MultiMap envelopeTime;

public:
	MacroEnvelope(bool _enableSustain, bool _enableHold)
	{
		e.set_envelope_time(0, 1);
		e.set_envelope_time(1, 100);
		e.set_envelope_time(2, 500);
		e.set_envelope_time(3, 1000);
		e.sustainEnable = _enableSustain;
		envelopeTime.addPreset({0.1f, 1.0f, 12.0f, 100.0f, 0.1f});
		envelopeTime.addPreset({0.1f, 1.0f, 60.0f, 600.0f, 0.1f});
		envelopeTime.addPreset({0.1f, 300.0f, 200.0f, 1200.0f, 0.3f});
		envelopeTime.addPreset({0.1f, 1.0f, 1000.0f, 50.0f, 0.9f});
		envelopeTime.addPreset({100.0f, 50.0f, 60.0f, 50.0f, 0.4f});
		envelopeTime.addPreset({1000.0f, 300.0f, 200.0f, 2000.0f, 0.2f});
	}

	float update(float gateIn)
	{
		return e.update(gateIn);
	}

	void set_samplerate(float sr)
	{
		e.set_samplerate(sr);
	}

	void set_time(float val)
	{
		std::vector<float> finalTimes = envelopeTime.update(val);
		for (int i = 0; i < 4; i++) {
			e.set_envelope_time(i, finalTimes[i]);
		}
		e.set_sustain(finalTimes[4]);
	}
};