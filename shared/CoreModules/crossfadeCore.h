#pragma once
#include "coreProcessor.h"
#include "math.hh"
#include "moduleTypes.h"

using namespace MathTools;

class CrossfadeCore : public CoreProcessor {
	static inline const int NumInJacks = 3;
	static inline const int NumOutJacks = 1;
	static inline const int NumKnobs = 1;

	static inline const std::array<StaticString<NameChars>, NumKnobs> KnobNames{"Fade"};
	static inline const std::array<StaticString<NameChars>, NumOutJacks> OutJackNames{"Output"};
	static inline const std::array<StaticString<NameChars>, NumInJacks> InJackNames{"Input 1", "Input 2", "Fade CV"};
	static inline const StaticString<LongNameChars> description{"Crossfader"};

	// clang-format off
	virtual StaticString<NameChars> knob_name(unsigned idx) override { return (idx < NumKnobs) ? KnobNames[idx] : ""; }
	virtual StaticString<NameChars> injack_name(unsigned idx) override { return (idx < NumInJacks) ? InJackNames[idx] : ""; }
	virtual StaticString<NameChars> outjack_name(unsigned idx) override { return (idx < NumOutJacks) ? OutJackNames[idx] : ""; }
	virtual StaticString<LongNameChars> get_description() override { return description; }
	// clang-format on
public:
	CrossfadeCore() {}

	virtual void update(void) override
	{
		xfadeOut = interpolate(in1, in2, constrain(xFade + xFadeCV, 0.0f, 1.0f));
	}

	virtual void set_param(const int param_id, const float val) override
	{
		if (param_id == 0) {
			xFade = val;
		}
	}

	virtual void set_samplerate(const float sr) override {}

	virtual void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			case 0:
				in1 = val;
				break;
			case 1:
				in2 = val;
				break;
			case 2:
				xFadeCV = val;
				break;
		}
	}

	virtual float get_output(const int output_id) const override
	{
		float value = 0;
		if (output_id == 0) {
			value = xfadeOut;
		}
		return value;
	}
	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<CrossfadeCore>();
	}
	static constexpr char typeID[20] = "XFADE";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	float xFade = 0;
	float xFadeCV = 0;
	float xfadeOut = 0;
	float in1;
	float in2;
};
