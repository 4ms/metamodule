#pragma once
#include "CoreModules/coreProcessor.h"
#include "util/math.hh"
#include "CoreModules/moduleFactory.hh"
#include "processors/tools/windowComparator.h"

using namespace MathTools;

class ComparatorCore : public CoreProcessor {
	static inline const int NumInJacks = 2;
	static inline const int NumOutJacks = 1;
	static inline const int NumKnobs = 2;

	static inline const std::array<StaticString<NameChars>, NumKnobs> KnobNames{"Threshold","CV"};
	static inline const std::array<StaticString<NameChars>, NumOutJacks> OutJackNames{"Output"};
	static inline const std::array<StaticString<NameChars>, NumInJacks> InJackNames{"Input","CV"};
	static inline const StaticString<LongNameChars> description{"Comparator"};

	// clang-format off
	virtual StaticString<NameChars> knob_name(unsigned idx) override { return (idx < NumKnobs) ? KnobNames[idx] : ""; }
	virtual StaticString<NameChars> injack_name(unsigned idx) override { return (idx < NumInJacks) ? InJackNames[idx] : ""; }
	virtual StaticString<NameChars> outjack_name(unsigned idx) override { return (idx < NumOutJacks) ? OutJackNames[idx] : ""; }
	virtual StaticString<LongNameChars> get_description() override { return description; }
	// clang-format on
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
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	float compOut = 0;
	float cvAmount = 0;
	float cvIn = 0;
	float signalIn = 0;
	float threshold = 0;

	const float compError = 0.02f;

	WindowComparator comp;
};
