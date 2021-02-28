#pragma once
#include "processors/fadeloop.hh"

template<unsigned long MAX_LENGTH>
class AllPass : public FadeLoop<float, MAX_LENGTH> {
public:
	AllPass() {}

	float process(float input)
	{
		float bufout = this->read();
		this->write(input + bufout * feedback);
		return -input + bufout;
	}

	void setLength(unsigned long length)
	{
		this->change_delay(length);
	}

	void setFeedback(float val)
	{
		feedback = val;
	}

	void setFadeSpeed(float val)
	{
		this->set_fade_speed(val);
	}

private:
	float feedback = 0;
};
