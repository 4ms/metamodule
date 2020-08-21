#pragma once

#include "audio_processor.hh"
#include "tools.h"

class VCA : public AudioProcessor {
public:

	virtual float update(float input)
	{

        input=input*preGain;
        if(input>5)
        input=5;
        if(input<-5)
        input=-5;
		float output = input*postGain;
		return output;
	}

	VCA()
	{
		preGain = 0;
		postGain = 1;
	}

	virtual void set_param(int param_id, float val)
	{
		if (param_id == 0)
			postGain = val;
		if (param_id == 1)
			preGain = map(val,0,1,1,5);
	}
	virtual void set_samplerate(float sr)
	{
		
	}

private:
	float preGain;
    float postGain;
};

