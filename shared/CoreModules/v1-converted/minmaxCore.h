#pragma once

#include "CoreModules/moduleFactory.hh"
#include "CoreModules/coreProcessor.h"
#include "util/math.hh"

using namespace MathTools;

class MinmaxCore : public CoreProcessor {
	static inline const int NumInJacks = 2;
	static inline const int NumOutJacks = 2;
	static inline const int NumKnobs = 0;

	static inline const std::array<StaticString<NameChars>, NumKnobs> KnobNames{};
	static inline const std::array<StaticString<NameChars>, NumOutJacks> OutJackNames{"Min", "Max"};
	static inline const std::array<StaticString<NameChars>, NumInJacks> InJackNames{"Input 1", "Input 2"};
	static inline const StaticString<LongNameChars> description{"Min/Max"};

	// clang-format off
	virtual StaticString<NameChars> knob_name(unsigned idx) override { return (idx < NumKnobs) ? KnobNames[idx] : ""; }
	virtual StaticString<NameChars> injack_name(unsigned idx) override { return (idx < NumInJacks) ? InJackNames[idx] : ""; }
	virtual StaticString<NameChars> outjack_name(unsigned idx) override { return (idx < NumOutJacks) ? OutJackNames[idx] : ""; }
	virtual StaticString<LongNameChars> get_description() override { return description; }
	// clang-format on
public:
	virtual void update(void) override
	{
		maxOut = max<float>(inA, inB);
		minOut = min<float>(inA, inB);
	}

	MinmaxCore() {}

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
				inA = val;
				break;
			case 1:
				inB = val;
				break;
		}
	}

	virtual float get_output(const int output_id) const override
	{
		float output = 0;
		switch (output_id) {
			case 0:
				output = minOut;
				break;
			case 1:
				output = maxOut;
				break;
		}
		return output;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<MinmaxCore>();
	}
	static constexpr char typeID[20] = "MINMAX";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	float inA = 0;
	float inB = 0;

	float maxOut = 0;
	float minOut = 0;
};
