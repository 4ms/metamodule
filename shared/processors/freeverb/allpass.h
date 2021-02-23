#pragma once

#include "sys/alloc_buffer.hh"
#include "util/interp_array.hh"

class allpass {
public:
	allpass()
	{
		bufidx = 0;
		for(int i=0;i<maxLength;i++)
		{
			buffer[i]=0;
		}
	}

	void setLength(long length)
	{
		bufferLength=length;
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

	void setFeedback(float val)
	{
		feedback = val;
	}

private:
    static constexpr int maxLength = 6000;
    long bufferLength = maxLength;
	BigAlloc<std::array<float,maxLength>> buffer;
	float feedback = 0;
	int bufidx = 0;
};