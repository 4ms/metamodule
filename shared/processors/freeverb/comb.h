#pragma once

#include "denormals.h"

class comb {
public:
	comb()
	{
		filterstore = 0;
		bufidx = 0;
	}

	void setbuffer(float *buf, int size)
	{
		buffer = buf;
		bufsize = size;
		for(int i=0;i<size;i++)
		{
			buffer[i]=0;
		}
	}

	void mute()
	{
		for (int i = 0; i < bufsize; i++)
			buffer[i] = 0;
	}

	void setdamp(float val)
	{
		damp1 = val;
		damp2 = 1 - val;
	}

	void setfeedback(float val)
	{
		feedback = val;
	}

	float process(float input)
	{
		float output;

		output = buffer[bufidx];
		undenormalise(output);

		filterstore = (output * damp2) + (filterstore * damp1);
		undenormalise(filterstore);

		buffer[bufidx] = input + (filterstore * feedback);

		if (++bufidx >= bufsize)
			bufidx = 0;

		return output;
	}

private:
	float feedback = 0;
	float filterstore = 0;
	float damp1 = 0;
	float damp2 = 0;
	float *buffer = nullptr;
	int bufsize = 1;
	int bufidx = 0;
};
