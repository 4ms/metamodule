#pragma once

#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "math.hh"

using namespace MathTools;

class PannerCore : public CoreProcessor {
	static inline const int NumInJacks = 2;
	static inline const int NumOutJacks = 2;
	static inline const int NumKnobs = 1;

	static inline const std::array<StaticString<NameChars>, NumKnobs> KnobNames{"Pan"};
	static inline const std::array<StaticString<NameChars>, NumOutJacks> OutJackNames{"Left Out", "Right Out"};
	static inline const std::array<StaticString<NameChars>, NumInJacks> InJackNames{"Input", "Pan CV"};
	static inline const StaticString<LongNameChars> description{"Panner"};

	// clang-format off
	virtual StaticString<NameChars> knob_name(unsigned idx) override { return (idx < NumKnobs) ? KnobNames[idx] : ""; }
	virtual StaticString<NameChars> injack_name(unsigned idx) override { return (idx < NumInJacks) ? InJackNames[idx] : ""; }
	virtual StaticString<NameChars> outjack_name(unsigned idx) override { return (idx < NumOutJacks) ? OutJackNames[idx] : ""; }
	virtual StaticString<LongNameChars> get_description() override { return description; }
	// clang-format on
public:
	virtual void update(void) override
	{
		float finalPan = constrain(panPosition + panCV, 0.0f, 1.0f);
		leftOut = signalInput * (1.0f - finalPan);
		rightOut = signalInput * finalPan;
	}

	PannerCore() {}

	virtual void set_param(int const param_id, const float val) override
	{
		switch (param_id) {
			case 0:
				panPosition = val;
				break;
		}
	}
	virtual void set_samplerate(const float sr) override {}

	virtual void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			case 0:
				signalInput = val;
				break;
			case 1:
				panCV = val;
				break;
		}
	}

	virtual float get_output(const int output_id) const override
	{
		float output = 0;
		switch (output_id) {
			case 0:
				output = leftOut;
				break;
			case 1:
				output = rightOut;
				break;
		}
		return output;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<PannerCore>();
	}
	static constexpr char typeID[20] = "PANNER";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	float panPosition = 0;
	float signalInput = 0;
	float leftOut = 0;
	float rightOut = 0;

	float panCV = 0;
};
