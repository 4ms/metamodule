#pragma once
#include "audio_processor.hh"

//Todo: put in tools.h

template<typename T>
T clip(T val, T min, T max)
{
	return val < min ? min : val > max ? max : val;
}

struct SimpleVCA : public AudioProcessor {
	virtual float update(float in)
	{
		return in * cv;
	}

	virtual void set_samplerate(float sr) {}
	virtual void set_param(int param_id, float val)
	{
		if (param_id == 0)
			cv = clip(val, 0.F, 1.F);
	}

	SimpleVCA()
	{
		cv = 0.0F;
	}

private:
	float cv;
};

