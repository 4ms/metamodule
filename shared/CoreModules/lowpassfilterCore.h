#pragma once

#include "../processors/lpf.h"
#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "math.hh"
#include "processors/moogLadder.h"
#include "util/math_tables.hh"

using namespace MathTools;

class LowpassfilterCore : public CoreProcessor {
	static inline const int NumInJacks = 2;
	static inline const int NumOutJacks = 1;
	static inline const int NumKnobs = 2;

	static inline const std::array<StaticString<NameChars>, NumKnobs> KnobNames{"Cutoff", "Q"};
	static inline const std::array<StaticString<NameChars>, NumOutJacks> OutJackNames{"Output"};
	static inline const std::array<StaticString<NameChars>, NumInJacks> InJackNames{"Input", "Cutoff CV"};
	static inline const StaticString<LongNameChars> description{"Lowpass Filter"};

	// clang-format off
	virtual StaticString<NameChars> knob_name(unsigned idx) override { return (idx < NumKnobs) ? KnobNames[idx] : ""; }
	virtual StaticString<NameChars> injack_name(unsigned idx) override { return (idx < NumInJacks) ? InJackNames[idx] : ""; }
	virtual StaticString<NameChars> outjack_name(unsigned idx) override { return (idx < NumOutJacks) ? OutJackNames[idx] : ""; }
	virtual StaticString<LongNameChars> get_description() override { return description; }
	// clang-format on

public:
	virtual void update(void) override
	{
		auto filterFreq = setPitchMultiple(constrain(baseFrequency + cvInput * cvAmount, -1.0f, 1.0f)) * 262.0f ;
		if (mode == 0) // basic resonant LPF
		{
			lpf.cutoff.setValue(filterFreq);
			lpf.q.setValue(filterQ);
			signalOut = lpf.update(signalIn);
		} else if (mode == 1) // Moog LPF
		{
			moog.cutoff.setValue(audioFreqToNorm(filterFreq));
			moog.q.setValue(filterQ);
			signalOut = moog.update(signalIn);
		}
	}

	LowpassfilterCore() {}

	virtual void set_param(int const param_id, const float val) override
	{
		if (param_id == 0) {
			baseFrequency = map_value(val, 0.0f, 1.0f, -1.0f, 1.0f);
		} else if (param_id == 1) {
			filterQ = map_value(val, 0.0f, 1.0f, 1.0f, 20.0f);
		} else if (param_id == 2) {
			cvAmount = val;
		} else if (param_id == 3) {
			mode = val;
		}
	}
	virtual void set_samplerate(const float sr) override
	{
		lpf.sampleRate.setValue(sr);
	}

	virtual void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			case 0:
				signalIn = val;
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
				output = signalOut;
				break;
		}
		return output;
	}

	virtual float get_led_brightness(const int led_id) const override
	{
		return mode;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<LowpassfilterCore>();
	}
	static constexpr char typeID[20] = "LOWPASSFILTER";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	int mode = 1;
	MoogLadder moog;
	LowPassFilter lpf;
	float signalIn = 0;
	float signalOut = 0;
	float baseFrequency = 1.0;
	float cvInput = 0;
	float filterQ = 0;
	float cvAmount = 0;
};