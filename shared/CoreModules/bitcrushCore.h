#pragma once

#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "processors/bit_crush.h"
#include "util/math.hh"

using namespace MathTools;

class BitcrushCore : public CoreProcessor {
public:
	virtual void update(void) override
	{
		signalOutput = bc.update(signalInput);
	}

	BitcrushCore() {}

	virtual void set_param(int const param_id, const float val) override
	{
		bc.set_param(param_id, val);
	}
	virtual void set_samplerate(const float sr) override
	{
		bc.set_samplerate(sr);
	}

	virtual void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			case 0:
				signalInput = val;
				break;
		}
	}

	virtual float get_output(const int output_id) const override
	{
		float output = 0;
		switch (output_id) {
			case 0:
				output = signalOutput;
				break;
		}
		return output;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<BitcrushCore>();
	}
	static constexpr char typeID[20] = "BITCRUSH";
	static constexpr char description[] = "Bit Crusher";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	BitCrusher bc;

	float signalInput = 0;
	float signalOutput = 0;
};
