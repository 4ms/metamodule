#pragma once

#include "CoreModules/moduleFactory.hh"
#include "CoreModules/coreProcessor.h"
#include "util/math.hh"
#include "processors/tools/expDecay.h"

using namespace MathTools;

class SlewlimiterCore : public CoreProcessor {
	static inline const int NumInJacks = 1;
	static inline const int NumOutJacks = 1;
	static inline const int NumKnobs = 2;

	static inline const std::array<StaticString<NameChars>, NumKnobs> KnobNames{"Rise", "Fall"};
	static inline const std::array<StaticString<NameChars>, NumOutJacks> OutJackNames{"Output"};
	static inline const std::array<StaticString<NameChars>, NumInJacks> InJackNames{"Input"};
	static inline const StaticString<LongNameChars> description{"Slew Limiter"};

	// clang-format off
	virtual StaticString<NameChars> knob_name(unsigned idx) override { return (idx < NumKnobs) ? KnobNames[idx] : ""; }
	virtual StaticString<NameChars> injack_name(unsigned idx) override { return (idx < NumInJacks) ? InJackNames[idx] : ""; }
	virtual StaticString<NameChars> outjack_name(unsigned idx) override { return (idx < NumOutJacks) ? OutJackNames[idx] : ""; }
	virtual StaticString<LongNameChars> get_description() override { return description; }
	// clang-format on
public:
	virtual void update(void) override
	{
		signalOutput = slew.update(signalInput);
	}

	SlewlimiterCore() {}

	virtual void set_param(int const param_id, const float val) override
	{
		switch (param_id) {
			case 0: // rise time
slew.attackTime=map_value(val,0.0f,1.0f,1.0f,2000.0f);
				break;
			case 1: // fall time
				slew.decayTime = map_value(val, 0.0f, 1.0f, 1.0f, 2000.0f);
				break;
		}
	}
	virtual void set_samplerate(const float sr) override
	{
		slew.set_samplerate(sr);
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
		return std::make_unique<SlewlimiterCore>();
	}
	static constexpr char typeID[20] = "SLEWLIMITER";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	ExpDecay slew;
	float signalInput = 0;
	float signalOutput = 0;
};
