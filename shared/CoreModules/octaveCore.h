#pragma once

#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "math.hh"

using namespace MathTools;

class OctaveCore : public CoreProcessor {
	static inline const int NumInJacks = 2;
	static inline const int NumOutJacks = 1;
	static inline const int NumKnobs = 1;

	static inline const std::array<StaticString<NameChars>, NumKnobs> KnobNames{"Octave"};
	static inline const std::array<StaticString<NameChars>, NumOutJacks> OutJackNames{"Output"};
	static inline const std::array<StaticString<NameChars>, NumInJacks> InJackNames{"Pitch In", "Octave CV"};
	static inline const StaticString<LongNameChars> description{"Octave"};

	// clang-format off
	virtual StaticString<NameChars> knob_name(unsigned idx) override { return (idx < NumKnobs) ? KnobNames[idx] : ""; }
	virtual StaticString<NameChars> injack_name(unsigned idx) override { return (idx < NumInJacks) ? InJackNames[idx] : ""; }
	virtual StaticString<NameChars> outjack_name(unsigned idx) override { return (idx < NumOutJacks) ? OutJackNames[idx] : ""; }
	virtual StaticString<LongNameChars> get_description() override { return description; }
	// clang-format on
public:
	virtual void update(void) override
	{
		auto cvSum = constrain<float>(octaveOffset + cvInput, 0.0f, 1.0f);
		int octave = map_value(cvSum, 0.0f, 1.0f, 0, 5);
		voltOutput = voltInput + octave;
	}

	OctaveCore() {}

	virtual void set_param(int const param_id, const float val) override
	{
		switch (param_id) {
			case 0:
				octaveOffset = val;
				break;
		}
	}
	virtual void set_samplerate(const float sr) override {}

	virtual void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			case 0:
				voltInput = val;
				break;
			case 1:
				cvInput = val;
				break;
		}
	}

	virtual float get_output(const int output_id) const override
	{
		float output = 0;
		switch (output_id) {
			case 0:
				output = voltOutput;
				break;
		}
		return output;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<OctaveCore>();
	}
	static constexpr char typeID[20] = "OCTAVE";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	float octaveOffset = 0;
	float cvInput = 0;
	float voltInput = 0;
	float voltOutput = 0;
};
