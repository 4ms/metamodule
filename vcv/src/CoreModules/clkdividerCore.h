#pragma once

#include "coreProcessor.h"
#include "math.hh"
#include "CoreModules/moduleTypes.h"


using namespace MathTools;

class ClkdividerCore : public CoreProcessor {
public:
	virtual void update(void) override
	{
		if(clockIn>lastClockIn)
		{
			durationSamples=sinceClock;
			sinceClock=0;
			wholeCount+=1;
		}
		tempPhase=sinceClock/(float)durationSamples;
		if(tempPhase<1)
		{
		phase = (float)(wholeCount+tempPhase)/(float)clkDivide;
		}
		auto wrapPhase = phase - (unsigned long)phase;
		if(wrapPhase<pulseWidth)
		{
			clockOutput=1;
		}
		else
		{
			clockOutput=0;
		}
		sinceClock++;
	}

	ClkdividerCore()
	{
	}

	virtual void set_param(int const param_id, const float val) override
	{
		switch (param_id) {
			case 0:
			clkDivide=map_value(val,0.0f,1.0f,1.0f,8.99f);
			break;
		}
	}
	virtual void set_samplerate(const float sr) override
	{
	}

	virtual void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			case 0:
			{
			lastClockIn=clockIn;
			clockIn=(val>0.0f);
			}
			break;
			
		}
	}

	virtual float get_output(const int output_id) const override
	{
		float output = 0;
		switch (output_id) {
			case 0:
		output = clockOutput;
		break;
		}
		return output;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<ClkdividerCore>();
	}
	static constexpr char typeID[20] = "CLKDIVIDER";
	static constexpr char description[] = "clock divider";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:

int clkDivide = 4;
float cvIn=0;
float phase=0;
int wholeCount=0;
float tempPhase=0;
int clockIn=0;
int lastClockIn=0;
int resetIn=0;
int lastResetIn=0;
float sinceClock=0;
float pulseWidth=0.5f;
unsigned long durationSamples=0;
int clockOutput=0;
};
