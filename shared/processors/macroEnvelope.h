#pragma once

#include "processors/envelope.h"

class MacroEnvelope {
private:
	Envelope e;

public:
	MacroEnvelope()
	{
		e.set_envelope_time(0, 1);
		e.set_envelope_time(1, 100);
		e.set_envelope_time(2, 500);
		e.set_envelope_time(3, 1000);
	}

	float update(float gateIn)
	{
		return e.update(gateIn);
	}

	void set_samplerate(float sr)
	{
		e.set_samplerate(sr);
	}
};