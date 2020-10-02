#pragma once

#include "math.hh"
#include "tools.h"

class Reverb2 : public AudioProcessor {
public:
	Reverb2() {}

	virtual float update(float input)
	{

		return output;
	}

	virtual void set_param(int param_id, float val)
	{
		if (param_id == 0) {
		}
		if (param_id == 1) {
		}
	}
	virtual void set_samplerate(float sr) {}

private:
};