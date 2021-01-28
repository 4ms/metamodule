#pragma once

#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "math.hh"
#include "processors/envelope.h"

using namespace MathTools;

class ComplexenvelopeCore : public CoreProcessor {
public:
	virtual void update(void) override
	{
		envelopeOutput = e.update(gateInput);
	}

	ComplexenvelopeCore() {}

	virtual void set_param(int const param_id, const float val) override
	{
		auto mappedTime = map_value(val,0.0f,1.0f,0.1f,1000.0f);
		switch (param_id) {
			case 0: // attack
			e.set_envelope_time(0,mappedTime);
				break;
			case 1: // hold
			e.set_envelope_time(1,mappedTime);
				break;
			case 2: // decay
			e.set_envelope_time(2,mappedTime);
				break;
			case 3: // sustain
			e.set_sustain(val);
				break;
			case 4: // release
			e.set_envelope_time(3,mappedTime);
				break;
		}
	}
	virtual void set_samplerate(const float sr) override {}

	virtual void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			case 0:
				gateInput = val;
				break;
		}
	}

	virtual float get_output(const int output_id) const override
	{
		float output = 0;
		switch (output_id) {
			case 0:
				output = envelopeOutput;
				break;
		}
		return output;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<ComplexenvelopeCore>();
	}
	static constexpr char typeID[20] = "COMPLEXENVELOPE";
	static constexpr char description[] = "Complex Envelope";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	float gateInput = 0;
	float envelopeOutput = 0;
	Envelope e;
};
