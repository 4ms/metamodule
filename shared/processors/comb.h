#pragma once
#include "processors/fadeloop.hh"

template<unsigned long MAX_LENGTH>
class Comb : public FadeLoop<float, MAX_LENGTH> {
public:
	Comb() {}

	float process(float input)
	{
		float output = this->read();
		filterstore = (output * damp2) + (filterstore * damp1);
		this->write(input + (filterstore * feedback));
		return output;
	}

	void setLength(unsigned long length)
	{
		this->change_delay(length);
	}

	void setFeedback(float val)
	{
		feedback = val;
	}

	void setDamp(float val)
	{
		damp1 = val;
		damp2 = 1 - val;
	}

	void setFadeSpeed(float val)
	{
		this->set_fade_speed(val);
	}

private:
	float feedback = 0;
	float filterstore = 0;
	float damp1 = 0;
	float damp2 = 0;
};

