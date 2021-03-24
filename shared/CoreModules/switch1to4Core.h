#pragma once

#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "processors/tools/clockPhase.h"
#include "util/math.hh"

using namespace MathTools;

class Switch1to4Core : public CoreProcessor {
	static inline const int NumInJacks = 4;
	static inline const int NumOutJacks = 4;
	static inline const int NumKnobs = 0;

	static inline const std::array<StaticString<NameChars>, NumKnobs> KnobNames{};
	static inline const std::array<StaticString<NameChars>, NumOutJacks> OutJackNames{
		"Output 1", "Output 2", "Output 3", "Output 4"};
	static inline const std::array<StaticString<NameChars>, NumInJacks> InJackNames{
		"Clock In", "Reset In", "Input", "CV"};
	static inline const StaticString<LongNameChars> description{"1:4 Switch"};

	// clang-format off
	virtual StaticString<NameChars> knob_name(unsigned idx) override { return (idx < NumKnobs) ? KnobNames[idx] : ""; }
	virtual StaticString<NameChars> injack_name(unsigned idx) override { return (idx < NumInJacks) ? InJackNames[idx] : ""; }
	virtual StaticString<NameChars> outjack_name(unsigned idx) override { return (idx < NumOutJacks) ? OutJackNames[idx] : ""; }
	virtual StaticString<LongNameChars> get_description() override { return description; }
	// clang-format on
public:
	virtual void update(void) override
	{
		cp.update();
		stepNum = cp.getCount() % 4;

		float position = cvSignal * 3.0f;
		float fade = position - (int)position;

		switch ((int)position) {
			case 0:
				panSignals[0] = 1.0f - fade;
				panSignals[1] = fade;
				panSignals[2] = 0;
				panSignals[3] = 0;
				break;
			case 1:
				panSignals[0] = 0;
				panSignals[1] = 1.0f - fade;
				panSignals[2] = fade;
				panSignals[3] = 0;
				break;
			case 2:
				panSignals[0] = 0;
				panSignals[1] = 0;
				panSignals[2] = 1.0f - fade;
				panSignals[3] = fade;
				break;
			case 3:
				panSignals[0] = 0;
				panSignals[1] = 0;
				panSignals[2] = 0;
				panSignals[3] = 1.0f;
				break;
		}
	}

	Switch1to4Core()
	{
		for (int i = 0; i < 4; i++) {
			panSignals[i] = 0;
		}
	}

	virtual void set_param(int const param_id, const float val) override
	{
		switch (param_id) {
		}
	}
	virtual void set_samplerate(const float sr) override {}

	virtual void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			case 0: // clock
				cp.updateClock(val);
				break;
			case 1: // reset
				cp.updateReset(val);
				break;
			case 2: // signal
				inputSignal = val;
				break;
			case 3:
				cvSignal = constrain(val, 0.0f, 1.0f);
				break;
		}
	}

	virtual float get_output(const int output_id) const override
	{
		float output = 0;
		if (cvMode) {
			output = panSignals[output_id] * inputSignal;
		} else {
			if (output_id == stepNum) {
				output = inputSignal;
			} else {
				output = 0;
			}
		}

		return output;
	}

	virtual void mark_input_unpatched(const int input_id) override
	{
		if (input_id == 3)
			cvMode = false;
	}
	virtual void mark_input_patched(const int input_id) override
	{
		if (input_id == 3)
			cvMode = true;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<Switch1to4Core>();
	}
	static constexpr char typeID[20] = "SWITCH1TO4";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	ClockPhase cp;
	float panSignals[4];
	float cvSignal = 0;
	bool cvMode = false;
	int stepNum = 0;
	float inputSignal = 0;
};
