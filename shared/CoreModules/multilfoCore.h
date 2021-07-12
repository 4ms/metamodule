#pragma once

#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "math.hh"
#include "util/math_tables.hh"

using namespace MathTools;

class MultilfoCore : public CoreProcessor {
	static inline const int NumInJacks = 1;
	static inline const int NumOutJacks = 1;
	static inline const int NumKnobs = 1;

	static inline const std::array<StaticString<NameChars>, NumKnobs> KnobNames{};
	static inline const std::array<StaticString<NameChars>, NumOutJacks> OutJackNames{};
	static inline const std::array<StaticString<NameChars>, NumInJacks> InJackNames{};
	static inline const StaticString<LongNameChars> description{"Multi Output LFO"};

	// clang-format off
	virtual StaticString<NameChars> knob_name(unsigned idx) override { return (idx < NumKnobs) ? KnobNames[idx] : ""; }
	virtual StaticString<NameChars> injack_name(unsigned idx) override { return (idx < NumInJacks) ? InJackNames[idx] : ""; }
	virtual StaticString<NameChars> outjack_name(unsigned idx) override { return (idx < NumOutJacks) ? OutJackNames[idx] : ""; }
	virtual StaticString<LongNameChars> get_description() override { return description; }
	// clang-format on
public:
	virtual void update(void) override
	{
		float finalRate = rateOffset * setPitchMultiple(rateCV);
		phaccu += finalRate / sampRate;
		if (phaccu >= 1.0f)
			phaccu -= 1.0f;
		modPhase = phaccu + phaseOffset;
		if (modPhase > 1.0f)
			modPhase -= 1.0f;
	}

	MultilfoCore() {}

	virtual void set_param(int const param_id, const float val) override
	{
		switch (param_id) {
			case 0:
				rateOffset = map_value(val, 0.0f, 1.0f, 0.1f, 10.0f);
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
				rateCV = val;
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
				output = sawTable.interp(modPhase);
				break;
			case 2: // inverted saw
				output = isawTable.interp(modPhase);
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

private:
	float phaccu = 0;
	float sampRate = 44100;
	float rateOffset = 1.0f;
	float rateCV = 0;
	float phaseCV = 0;
	float pwOffset = 0.5f;
	float pwCV = 0;
	InterpArray<float, 2> sawTable = {-1.0f, 1.0f};
	InterpArray<float, 2> isawTable = {1.0f, -1.0f};
	float modPhase = 0;
	float phaseOffset = 0;
	bool currentReset = 0;
	bool lastReset = 0;
};
