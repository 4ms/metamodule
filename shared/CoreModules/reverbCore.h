#pragma once

#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "math.hh"
#include "processors/freeverb/allpass.h"
#include "processors/freeverb/comb.h"

using namespace MathTools;

class ReverbCore : public CoreProcessor {
public:
	virtual void update(void) override
	{
		float wetSignal = 0;

		wetSignal += combFilter1.process(signalIn);
		wetSignal += combFilter2.process(signalIn);
		wetSignal += combFilter3.process(signalIn);
		wetSignal += combFilter4.process(signalIn);

		wetSignal /= static_cast<float>(numComb);

		wetSignal = apFilter1.process(wetSignal);
		wetSignal = apFilter2.process(wetSignal);
		wetSignal = apFilter3.process(wetSignal);
		wetSignal = apFilter4.process(wetSignal);

		signalOut = interpolate(signalIn, wetSignal, mix);
	}

	ReverbCore()
	{
		apFilter1.setfeedback(0.5f);
		apFilter2.setfeedback(0.5f);
		apFilter3.setfeedback(0.5f);
		apFilter4.setfeedback(0.5f);

		combFilter1.setfeedback(0);
		combFilter2.setfeedback(0);
		combFilter3.setfeedback(0);
		combFilter4.setfeedback(0);


	}

	virtual void set_param(int const param_id, const float val) override
	{
		switch (param_id) {
			case 0: // size
					combFilter1.setfeedback(val);
					combFilter2.setfeedback(val);
					combFilter3.setfeedback(val);
					combFilter4.setfeedback(val);

				break;
			case 1: // damp
					combFilter1.setdamp(val);
					combFilter2.setdamp(val);
					combFilter3.setdamp(val);
					combFilter4.setdamp(val);
				break;
			case 2:
				mix = val;
				break;
		}
	}
	virtual void set_samplerate(const float sr) override {}

	virtual void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			case 0:
				signalIn = val;
				break;
		}
	}

	virtual float get_output(const int output_id) const override
	{
		float output = 0;
		switch (output_id) {
			case 0:
				output = signalOut;
				break;
		}
		return output;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<ReverbCore>();
	}
	static constexpr char typeID[20] = "REVERB";
	static constexpr char description[] = "Reverb";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	float signalIn = 0;
	float signalOut = 0;

	static const int numComb = 4;
	static const int numAll = 4;

	comb<3000> combFilter1;
    comb<4003> combFilter2;
	comb<4528> combFilter3;
	comb<5217> combFilter4;

	allpass<1248> apFilter1;
	allpass<812> apFilter2;
	allpass<358> apFilter3;
	allpass<125> apFilter4;

	float mix = 0;
};
