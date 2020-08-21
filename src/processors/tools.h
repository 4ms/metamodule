#pragma once
#include <cmath>

inline float map(float x, float in_min, float in_max, float out_min, float out_max)
{
 return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

inline float constrain(float in, float min, float max)
{
    if(in<min)
    in=min;
    if(in>max)
    in=max;
    return in;
}

class ExpDecay
{
    public:

    float decayTime;

    ExpDecay()
    {
        for(int i=0;i<2;i++)
        {
            fRec0[i]=0;
        }
    }

    virtual void set_samplerate(float sr)
	{
        fConst0 = (1.0f / std::min<float>(192000.0f, std::max<float>(1.0f, float(sr))));
	}

    float update(float input)
    {
        float output=0;
		float fSlow0 = (0.00100000005f * float(decayTime));
		int iSlow1 = (fabsf(fSlow0) < 0.00000001f);//1.1920929e-07f);
		float fSlow2 = (iSlow1 ? 0.0f : expf((0.0f - (fConst0 / (iSlow1 ? 1.0f : fSlow0)))));
		float fSlow3 = (1.0f - fSlow2);
        float fTemp0 = fabsf(input);
        fRec0[0] = std::max<float>(fTemp0, ((fRec0[1] * fSlow2) + (fTemp0 * fSlow3)));
        output = float(fRec0[0]);
        fRec0[1] = fRec0[0];
        return output;
    }

    private:

    float fConst0=0;
	float fRec0[2];
};
