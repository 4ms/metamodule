#pragma once

#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "util/math.hh"
#include "util/math_tables.hh"

using namespace MathTools;

class MultilfoCore : public CoreProcessor {
	static inline const int NumInJacks = 4;
	static inline const int NumOutJacks = 4;
	static inline const int NumKnobs = 3;

	static inline const std::array<StaticString<NameChars>, NumKnobs> KnobNames{"Rate", "Phase", "PW"};
	static inline const std::array<StaticString<NameChars>, NumOutJacks> OutJackNames{"Sine", "Saw", "Ramp", "Pulse"};
	static inline const std::array<StaticString<NameChars>, NumInJacks> InJackNames{
		"RateCV", "PhaseCV", "PWCV", "Reset"};
	static inline const StaticString<LongNameChars> description{"Multi Output LFO"};

public:
	MultilfoCore() = default;

	virtual void update(void) override
	{
		if (rateChanged) {
			combineKnobCVFreq();
			rateChanged = false;
		}

		phaccu += finalRate / sampRate;
		if (phaccu >= 1.0f)
			phaccu -= 1.0f;
		modPhase = phaccu + phaseOffset;
		if (modPhase >= 1.0f)
			modPhase -= 1.0f;
	}

	void combineKnobCVFreq()
	{
		auto knobFreq = expTable.closest(constrain(rawKnobVal, 0.f, 1.f));
		finalRate = knobFreq * setPitchMultiple(rawCvVal);
	}

	virtual void set_param(int const param_id, const float val) override
	{
		switch (param_id) {
			case 0:
				rawKnobVal = val;
				rateChanged = true;
				break;
			case 1:
				phaseOffset = val;
				break;
			case 2:
				pwOffset = val;
				break;
		}
	}
	virtual void set_samplerate(const float sr) override
	{
		sampRate = sr;
	}

	virtual void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			case 0:
				rawCvVal = val;
				rateChanged = true;
				break;
			case 1: // phase cv
				phaseCV = val;
				break;
			case 2: // pw cv
				pwCV = val;
				break;
			case 3: // reset
				lastReset = currentReset;
				currentReset = val > 0.2f;
				if (currentReset > lastReset) {
					phaccu = 0;
				}
				break;
		}
	}

	virtual float get_output(const int output_id) const override
	{
		float output = 0;
		switch (output_id) {
			case 0: // sin
				output = sinTable.interp(modPhase);
				break;
			case 1: // saw
				output = modPhase * 2.f - 1.f;
				break;
			case 2: // inverted saw
				output = 1.f - modPhase * 2.f;
				break;
			case 3: // pulse
				float finalPw = constrain(pwOffset + pwCV, 0.0f, 1.0f);
				if (modPhase < finalPw) {
					output = 1.0f;
				} else {
					output = -1.0f;
				}
				break;
		}
		return output;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<MultilfoCore>();
	}
	static constexpr char typeID[20] = "MULTILFO";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);
	// clang-format off
	virtual StaticString<NameChars> knob_name(unsigned idx) override { return (idx < NumKnobs) ? KnobNames[idx] : ""; }
	virtual StaticString<NameChars> injack_name(unsigned idx) override { return (idx < NumInJacks) ? InJackNames[idx] : ""; }
	virtual StaticString<NameChars> outjack_name(unsigned idx) override { return (idx < NumOutJacks) ? OutJackNames[idx] : ""; }
	virtual StaticString<LongNameChars> get_description() override { return description; }
	// clang-format on

private:
	bool rateChanged = true;
	float phaccu = 0.f;
	float finalRate = 0.1f;
	float sampRate = 48000.f;
	float lfoRate = 1.0f;
	float rawKnobVal = 1.0f;
	float rawCvVal = 1.0f;
	float rateCV = 0.f;
	float phaseCV = 0.f;
	float pwOffset = 0.5f;
	float pwCV = 0.f;
	float modPhase = 0.f;
	float phaseOffset = 0.f;
	bool currentReset = 0.f;
	bool lastReset = 0.f;
};
