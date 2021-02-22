#pragma once

#include "denormals.h"

class allpass {
public:
	allpass()
	{
		bufidx = 0;
	}

	float process(float input)
	{
		float output = 0;
		float bufout = 0;

		bufout = buffer[bufidx];
		undenormalise(bufout);

		output = -input + bufout;
		buffer[bufidx] = input + (bufout * feedback);

		if (++bufidx >= bufsize)
			bufidx = 0;

		return output;
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

	void setfeedback(float val)
	{
		feedback = val;
	}

private:
	float feedback = 0;
	float *buffer = nullptr;
	int bufsize = 0;
	int bufidx = 0;
};