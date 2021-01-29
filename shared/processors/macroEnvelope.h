#pragma once

#include "processors/envelope.h"
#include "processors/tools/multiMap.h"

class MacroEnvelope {
private:
	Envelope e;
	MultiMap envelopeTime;

public:
	MacroEnvelope(bool _enableSustain)
	{
		e.set_envelope_time(0, 1);
		e.set_envelope_time(1, 100);
		e.set_envelope_time(2, 500);
		e.set_envelope_time(3, 1000);
		e.set_attack_curve(0.1f);
		e.set_decay_curve(0.0f);
		e.set_release_curve(0.3f);
		e.sustainEnable = _enableSustain;
		envelopeTime.addPreset({0.01f, 0.0f, 5.0f, 30.0f, 0.1f});
		envelopeTime.addPreset({0.1f, 0.0f, 10.0f, 20.0f, 0.05f});
		envelopeTime.addPreset({0.1f, 0.0f, 20.0f, 50.0f, 0.05f});
		envelopeTime.addPreset({0.1f, 0.0f, 30.0f, 100.0f, 0.1f});
		envelopeTime.addPreset({0.1f, 200.0f, 600.0f, 3000.0f, 0.6f});
		envelopeTime.addPreset({10.0f, 20.0f, 80.0f, 800.0f, 0.2f});
		envelopeTime.addPreset({80.0f, 60.0f, 120.0f, 2000.0f, 0.2f});
		envelopeTime.addPreset({100.0f, 0.0f, 400.0f, 60.0f, 0.5f});
		envelopeTime.addPreset({50.0f, 0.0f, 40.0f, 20.0f, 0.2f});
		envelopeTime.addPreset({200.0f, 0.0f, 400.0f, 800.0f, 0.4f});
		envelopeTime.addPreset({2000.0f, 0.0f, 1000.0f, 3000.0f, 0.8f});
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