#pragma once

#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "math.hh"

using namespace MathTools;

class EightstepprobCore : public CoreProcessor {
public:
	virtual void update(void) override {}

	EightstepprobCore() {}

	virtual void set_param(int const param_id, const float val) override
	{
		switch (param_id) {
		}
	}
	virtual void set_samplerate(const float sr) override {}

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
		return std::make_unique<EightstepprobCore>();
	}
	static constexpr char typeID[20] = "EIGHTSTEPPROB";
	static constexpr char description[] = "8 Step Probability Sequencer";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	float prob[8];
};
