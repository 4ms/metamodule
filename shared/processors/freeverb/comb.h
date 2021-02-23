#pragma once

class comb {
public:
	comb()
	{
		filterstore = 0;
		bufidx = 0;
		for(int i=0;i<maxLength;i++)
		{
			buffer[i]=0;
		}
	}

	void setDamp(float val)
	{
		damp1 = val;
		damp2 = 1 - val;
	}

	void setFeedback(float val)
	{
		feedback = val;
	}

	void setLength(long length)
	{
		bufferLength=length;
	}

	float process(float input)
	{
		float output;

		output = buffer[bufidx];

		filterstore = (output * damp2) + (filterstore * damp1);

		buffer[bufidx] = input + (filterstore * feedback);

		if (++bufidx >= bufferLength)
			bufidx = 0;

		return output;
	}

private:
    long bufferLength=maxLength;
	float feedback = 0;
	float filterstore = 0;
	float damp1 = 0;
	float damp2 = 0;
	static constexpr int maxLength = 6000;
	BigAlloc<std::array<float,maxLength>> buffer;
	int bufidx = 0;
};
