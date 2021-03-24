#pragma once

#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "math.hh"
#include "processors/hpf.h"

using namespace MathTools;

class HighpassfilterCore : public CoreProcessor {
	static inline const int NumInJacks = 2;
	static inline const int NumOutJacks = 1;
	static inline const int NumKnobs = 2;

	static inline const std::array<StaticString<NameChars>, NumKnobs> KnobNames{"Cutoff", "Q"};
	static inline const std::array<StaticString<NameChars>, NumOutJacks> OutJackNames{"Output"};
	static inline const std::array<StaticString<NameChars>, NumInJacks> InJackNames{"Input", "Cutoff CV"};
	static inline const StaticString<LongNameChars> description{"Highpass Filter"};

	// clang-format off
	virtual StaticString<NameChars> knob_name(unsigned idx) override { return (idx < NumKnobs) ? KnobNames[idx] : ""; }
	virtual StaticString<NameChars> injack_name(unsigned idx) override { return (idx < NumInJacks) ? InJackNames[idx] : ""; }
	virtual StaticString<NameChars> outjack_name(unsigned idx) override { return (idx < NumOutJacks) ? OutJackNames[idx] : ""; }
	virtual StaticString<LongNameChars> get_description() override { return description; }
	// clang-format on
public:
	virtual void update(void) override
	{
		hpf.cutoff.setValue(setPitchMultiple(constrain(cutoffOffset + cutoffCV, -1.0f, 1.0f)) * 262.0f);
		signalOutput = hpf.update(signalInput);
	}

	HighpassfilterCore() {}

	virtual void set_param(int const param_id, const float val) override
	{
		switch (param_id) {
			case 0:
				cutoffOffset = map_value(val, 0.0f, 1.0f, -1.0f, 1.0f);
				break;
			case 1:
				hpf.q = map_value(val, 0.0f, 1.0f, 1.0f, 20.0f);
				break;
		}
	}
	virtual void set_samplerate(const float sr) override
	{
		hpf.sampleRate.setValue(sr);
	}

	virtual void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			case 0:
				signalInput = val;
				break;
			case 1:
				cutoffCV = val;
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
		return std::make_unique<HighpassfilterCore>();
	}
	static constexpr char typeID[20] = "HIGHPASSFILTER";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	HighPassFilter hpf;
	float signalInput = 0;
	float signalOutput = 0;
	float cutoffOffset = 0;
	float cutoffCV = 0;
};
