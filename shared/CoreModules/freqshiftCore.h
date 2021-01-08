#pragma once

#include "coreProcessor.h"
#include "math.hh"
#include "CoreModules/moduleTypes.h"

using namespace MathTools;

class FreqshiftCore : public CoreProcessor {
public:
	virtual void update(void) override
	{
	
	}

	FreqshiftCore()
	{
	}

	virtual void set_param(int const param_id, const float val) override
	{
		switch (param_id) {
			
		}
	}
	virtual void set_samplerate(const float sr) override
	{
	}

	virtual void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			
		}
	}

	virtual float get_output(const int output_id) const override
	{
		float output = 0;
		switch (output_id) {
		
		}
		return output;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<FreqshiftCore>();
	}
	static constexpr char typeID[20] = "FREQSHIFT";
	static constexpr char description[] = "Frequency Shifter";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	
};
