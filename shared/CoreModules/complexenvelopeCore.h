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
		switch (param_id) {
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
