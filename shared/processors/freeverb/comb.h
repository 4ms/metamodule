#pragma once

template<long bufferLength>
class comb {
public:
	comb()
	{
		filterstore = 0;
		bufidx = 0;
		for(int i=0;i<bufferLength;i++)
		{
			buffer[i]=0;
		}
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

		filterstore = (output * damp2) + (filterstore * damp1);

		buffer[bufidx] = input + (filterstore * feedback);

		if (++bufidx >= bufferLength)
			bufidx = 0;

		return output;
	}

private:
	float feedback = 0;
	float filterstore = 0;
	float damp1 = 0;
	float damp2 = 0;
	BigAlloc<std::array<float,bufferLength>> buffer;
	int bufidx = 0;
};
