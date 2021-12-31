#pragma once

#include "CoreModules/moduleFactory.hh"
#include "CoreModules/coreProcessor.h"
#include "util/math.hh"
#include "processors/tools/clockPhase.h"

using namespace MathTools;

class ClkmultiplierCore : public CoreProcessor {
	static inline const int NumInJacks = 2;
	static inline const int NumOutJacks = 1;
	static inline const int NumKnobs = 1;

	static inline const std::array<StaticString<NameChars>, NumKnobs> KnobNames{"Multiply"};
	static inline const std::array<StaticString<NameChars>, NumOutJacks> OutJackNames{"Output"};
	static inline const std::array<StaticString<NameChars>, NumInJacks> InJackNames{"Clock In", "CV"};
	static inline const StaticString<LongNameChars> description{"Clock Multiplier"};

	// clang-format off
	virtual StaticString<NameChars> knob_name(unsigned idx) override { return (idx < NumKnobs) ? KnobNames[idx] : ""; }
	virtual StaticString<NameChars> injack_name(unsigned idx) override { return (idx < NumInJacks) ? InJackNames[idx] : ""; }
	virtual StaticString<NameChars> outjack_name(unsigned idx) override { return (idx < NumOutJacks) ? OutJackNames[idx] : ""; }
	virtual StaticString<LongNameChars> get_description() override { return description; }
	// clang-format on
public:
	virtual void update(void) override
	{
		float finalMultiply = constrain(multiplyOffset + multiplyCV, 0.0f, 1.0f);
		cp.setMultiply(map_value(finalMultiply, 0.0f, 1.0f, 1.0f, 16.99f));
		cp.update();
		if (cp.getWrappedPhase() < pulseWidth) {
			clockOutput = 1;
		} else {
			clockOutput = 0;
		}
	}

	ClkmultiplierCore() {}

	virtual void set_param(int const param_id, const float val) override
	{
		switch (param_id) {
			case 0:
				multiplyOffset = val;
				break;
		}
	}
	virtual void set_samplerate(const float sr) override {}

	virtual void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			case 0:
				cp.updateClock(val);
				break;
			case 1:
				multiplyCV = val;
		}
	}

	virtual float get_output(const int output_id) const override
	{
		float output = 0;
		switch (output_id) {
			case 0:
				output = clockOutput;
				break;
		}
		return output;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<ClkmultiplierCore>();
	}
	static constexpr char typeID[20] = "CLKMULTIPLIER";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	float pulseWidth = 0.5f;
	int clockOutput = 0;
	float multiplyOffset = 0;
	float multiplyCV = 0;

	ClockPhase cp;
};
