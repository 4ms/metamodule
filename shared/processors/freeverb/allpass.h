#pragma once

#include "sys/alloc_buffer.hh"
#include "util/interp_array.hh"

template<long bufferLength>
class allpass {
public:
	allpass()
	{
		bufidx = 0;
		for(int i=0;i<bufferLength;i++)
		{
			buffer[i]=0;
		}
	}

	float process(float input)
	{
		float output = 0;
		float bufout = 0;

		bufout = buffer[bufidx];

		output = -input + bufout;
		buffer[bufidx] = input + (bufout * feedback);

		if (++bufidx >= bufferLength)
			bufidx = 0;

		return output;
	}

	void setfeedback(float val)
	{
		feedback = val;
	}

private:
	BigAlloc<std::array<float,bufferLength>> buffer;
	float feedback = 0;
	int bufidx = 0;
};