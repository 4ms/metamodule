#pragma once

#include "coreProcessor.h"
#include "math.hh"
#include "CoreModules/moduleTypes.h"
#include "processors/tools/windowComparator.h"
#include "processors/tools/expDecay.h"

using namespace MathTools;

class EnvelopefollowerCore : public CoreProcessor {
	static inline const int NumInJacks = 1;
	static inline const int NumOutJacks = 1;
	static inline const int NumKnobs = 1;

	static inline const std::array<StaticString<NameChars>, NumKnobs> KnobNames{};
	static inline const std::array<StaticString<NameChars>, NumOutJacks> OutJackNames{};
	static inline const std::array<StaticString<NameChars>, NumInJacks> InJackNames{};
	static inline const StaticString<LongNameChars> description{"Envelope Follower"};

	// clang-format off
	virtual StaticString<NameChars> knob_name(unsigned idx) override { return (idx < NumKnobs) ? KnobNames[idx] : ""; }
	virtual StaticString<NameChars> injack_name(unsigned idx) override { return (idx < NumInJacks) ? InJackNames[idx] : ""; }
	virtual StaticString<NameChars> outjack_name(unsigned idx) override { return (idx < NumOutJacks) ? OutJackNames[idx] : ""; }
	virtual StaticString<LongNameChars> get_description() override { return description; }
	// clang-format on
public:
	virtual void update(void) override
	{
	float rectSignal = signalInput;
	if(rectSignal<0)
	rectSignal*=-1.0f;
	envOutput=slew.update(rectSignal);
	wc.update(envOutput);
	gateOutput=wc.get_output();
	}

	EnvelopefollowerCore()
	{
	}

	virtual void set_param(int const param_id, const float val) override
	{
		switch (param_id) {
			case 0: //threshold
			{
			float topThresh;
			float bottomThresh;
			const float errorAmount=0.1f;
			topThresh=val+errorAmount;
			if(topThresh>1.0f)
			topThresh=1.0f;
			bottomThresh=val-errorAmount;
			if(bottomThresh<0)
			bottomThresh=0;
			wc.set_highThreshold(topThresh);
			wc.set_lowThreshhold(bottomThresh);
			}
			break;
			case 1: //rise
			slew.attackTime=map_value(val,0.0f,1.0f,1.0f,2000.f);
			break;
			case 2: //fall
			slew.decayTime=map_value(val,0.0f,1.0f,1.0f,2000.0f);
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
			signalInput=val;
			break;
		}
	}

	virtual float get_output(const int output_id) const override
	{
		float output = 0;
		switch (output_id) {
			case 0:
		output = envOutput;
		break;
		case 1:
		output = gateOutput;
		break;
		}
		return output;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<EnvelopefollowerCore>();
	}
	static constexpr char typeID[20] = "ENVELOPEFOLLOWER";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
float signalInput=0;
float envOutput=0;
float gateOutput=0;
WindowComparator wc;
ExpDecay slew;
	
};
