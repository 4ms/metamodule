#pragma once
#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "util/math.hh"

using namespace MathTools;

class AttCore : public CoreProcessor {
	static inline const int NumInJacks = 2;
	static inline const int NumOutJacks = 2;
	static inline const int NumKnobs = 2;

	static inline const std::array<StaticString<NameChars>, NumKnobs> KnobNames{"Level 1", "Level 2"};
	static inline const std::array<StaticString<NameChars>, NumOutJacks> OutJackNames{"Out 1","Out 2"};
	static inline const std::array<StaticString<NameChars>, NumInJacks> InJackNames{"In 1", "In 2"};
	static inline const StaticString<LongNameChars> description{"Attenuverter"};

	// clang-format off
	virtual StaticString<NameChars> knob_name(unsigned idx) override { return (idx < NumKnobs) ? KnobNames[idx] : ""; }
	virtual StaticString<NameChars> injack_name(unsigned idx) override { return (idx < NumInJacks) ? InJackNames[idx] : ""; }
	virtual StaticString<NameChars> outjack_name(unsigned idx) override { return (idx < NumOutJacks) ? OutJackNames[idx] : ""; }
	virtual StaticString<LongNameChars> get_description() override { return description; }
	// clang-format on

public:
	virtual void update(void) override
	{
		out1 = in1 * level1;
		out2 = in2 * level2;
	}

	AttCore() {}

	virtual void set_param(const int param_id, const float val) override
	{
		float mappedVal = map_value(val, 0.0f, 1.0f, -1.0f, 1.0f);
		switch (param_id) {
			case 0:
				level1 = mappedVal;
				break;
			case 1:
				level2 = mappedVal;
				break;
		}
	}
	virtual void set_samplerate(const float sr) override {}

	virtual void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			case 0:
				if (in1Connected)
					in1 = val;
				else
					in1 = 1.0f;
				break;
			case 1:
				if (in2Connected)
					in2 = val;
				else
					in2 = 1.0f;
				break;
		}
	}

	virtual float get_output(const int output_id) const override
	{
		float output = 0;
		switch (output_id) {
			case 0:
				output = out1;
				break;
			case 1:
				output = out2;
				break;
		}
		return output;
	}

	virtual void mark_input_unpatched(const int input_id) override
	{
		if (input_id == 0)
			in1Connected = 0;
		else if (input_id == 1)
			in2Connected = 0;
	}

	virtual void mark_input_patched(const int input_id) override
	{
		if (input_id == 0)
			in1Connected = 1;
		else if (input_id == 1)
			in2Connected = 1;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<AttCore>();
	}
	static constexpr char typeID[20] = "ATTENVERT2";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	float in1 = 0;
	float in2 = 0;
	float out1 = 0;
	float out2 = 0;
	float level1 = 0;
	float level2 = 0;

	int in1Connected = 0;
	int in2Connected = 0;
};
