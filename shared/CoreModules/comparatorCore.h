#pragma once
#include "coreProcessor.h"
#include "math.hh"
#include "moduleTypes.h"
#include "processors/tools/windowComparator.h"

using namespace MathTools;

class ComparatorCore : public CoreProcessor {
public:
	virtual void update(void) override
	{
		auto centerThreshold = cvIn * cvAmount + threshold;
		comp.set_lowThreshhold(centerThreshold - compError);
		comp.set_highThreshold(centerThreshold + compError);
		comp.update(signalIn);
		compOut = comp.get_output();
	}

	ComparatorCore() {}

	virtual void set_param(int const param_id, const float val) override
	{
		switch (param_id) {
			case 0:
				threshold = map_value(val, 0.0f, 1.0f, -1.0f, 1.0f);
				break;
			case 1:
				cvAmount = val;
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
			case 1:
				cvIn = val;
				break;
		}
	}

	virtual float get_output(const int output_id) const override
	{
		float output = 0;
		switch (output_id) {
			case 0:
				output = compOut;
				break;
		}
		return output;
	}
	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<ComparatorCore>();
	}
	static constexpr char typeID[20] = "COMPARATOR";
	static constexpr char description[] = "Basic Comparator";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	float compOut = 0;
	float cvAmount = 0;
	float cvIn = 0;
	float signalIn = 0;
	float threshold = 0;

	const float compError = 0.1f;

	WindowComparator comp;
};
