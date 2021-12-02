#pragma once

#include "CoreModules/moduleFactory.hh"
#include "CoreModules/coreProcessor.h"
#include "processors/tools/clockPhase.h"
#include "util/math.hh"

using namespace MathTools;

class Switch4to1Core : public CoreProcessor {
	static inline const int NumInJacks = 7;
	static inline const int NumOutJacks = 1;
	static inline const int NumKnobs = 0;

	static inline const std::array<StaticString<NameChars>, NumKnobs> KnobNames{};
	static inline const std::array<StaticString<NameChars>, NumOutJacks> OutJackNames{"Output"};
	static inline const std::array<StaticString<NameChars>, NumInJacks> InJackNames{
		"Clock In", "Reset In", "CV", "Input 1", "Input 2", "Input 3", "Inptu 4"};
	static inline const StaticString<LongNameChars> description{"4:1 Switch"};

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

		float position = cvInput * 3.0f;
		float fade = position - (int)position;

		switch ((int)position) {
			case 0:
				scanLevels[0] = 1.0f - fade;
				scanLevels[1] = fade;
				scanLevels[2] = 0;
				scanLevels[3] = 0;
				break;
			case 1:
				scanLevels[1] = 1.0f - fade;
				scanLevels[2] = fade;
				scanLevels[0] = 0;
				scanLevels[3] = 0;
				break;
			case 2:
				scanLevels[2] = 1.0f - fade;
				scanLevels[3] = fade;
				scanLevels[0] = 0;
				scanLevels[1] = 0;
				break;
			case 3:
				scanLevels[0] = 0;
				scanLevels[1] = 0;
				scanLevels[2] = 0;
				scanLevels[3] = 1.0f;
				break;
		}
	}

	Switch4to1Core() {}

	virtual void set_param(int const param_id, const float val) override
	{
		switch (param_id) {
		}
	}
	virtual void set_samplerate(const float sr) override {}

	virtual void set_input(const int input_id, const float val) override
	{
		if (input_id == 0) {
			cp.updateClock(val);
		} else if (input_id == 1) {
			cp.updateReset(val);
		} else if (input_id == 6) {
			cvInput = constrain(val, 0.0f, 1.0f);
		} else {
			auto inputNum = input_id - 2;
			signalInputs[inputNum] = val;
		}
	}

	virtual float get_output(const int output_id) const override
	{
		float output = 0;
		switch (output_id) {
			case 0: {
				if (cvMode) {
					for (int i = 0; i < 4; i++) {
						output += signalInputs[i] * scanLevels[i];
					}

				} else {
					output = signalInputs[stepNum];
				}
			} break;
		}
		return output;
	}

	virtual void mark_input_unpatched(const int input_id) override
	{
		if (input_id == 6) {
			cvMode = false;
		}
	}
	virtual void mark_input_patched(const int input_id) override
	{
		if (input_id == 6) {
			cvMode = true;
		}
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<Switch4to1Core>();
	}
	static constexpr char typeID[20] = "SWITCH4TO1";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	int stepNum = 0;
	float signalInputs[4] = {0, 0, 0, 0};
	float cvInput;
	float scanLevels[4];
	bool cvMode = false;
	ClockPhase cp;
};
