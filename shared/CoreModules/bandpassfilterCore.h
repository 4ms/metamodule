#pragma once

#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "math.hh"
#include "processors/bpf.h"
#include "processors/oberheimBPF.h"

using namespace MathTools;

class BandpassfilterCore : public CoreProcessor {
	static inline const int NumInJacks = 2;
	static inline const int NumOutJacks = 1;
	static inline const int NumKnobs = 2;

	static inline const std::array<StaticString<NameChars>, NumKnobs> KnobNames{"Cutoff", "Q"};
	static inline const std::array<StaticString<NameChars>, NumOutJacks> OutJackNames{"Output"};
	static inline const std::array<StaticString<NameChars>, NumInJacks> InJackNames{"Cutoff CV", "Q CV"};
	static inline const StaticString<LongNameChars> description{"Bandpass Filter"};

	// clang-format off
	virtual StaticString<NameChars> knob_name(unsigned idx) override { return (idx < NumKnobs) ? KnobNames[idx] : ""; }
	virtual StaticString<NameChars> injack_name(unsigned idx) override { return (idx < NumInJacks) ? InJackNames[idx] : ""; }
	virtual StaticString<NameChars> outjack_name(unsigned idx) override { return (idx < NumOutJacks) ? OutJackNames[idx] : ""; }
	virtual StaticString<LongNameChars> get_description() override { return description; }
	// clang-format on
public:
	virtual void update(void) override
	{
		float filterFreq = 523.25f * setPitchMultiple(constrain(cutoffCV + cutoffOffset, -1.0f, 1.0f));
		if (mode == 0) {
			bpf.q = map_value(filterQ, 0.0f, 1.0f, 1.0f, 20.0f);
			bpf.cutoff.setValue(filterFreq);
			signalOutput = bpf.update(signalInput);
		} else if (mode == 1) {
			ober.q = map_value(filterQ, 0.0f, 1.0f, 1.0f, 20.0f);
			ober.cutoff.setValue(audioFreqToNorm(filterFreq));
			signalOutput = ober.update(signalInput);
		}
	}

	BandpassfilterCore() {}

	virtual void set_param(int const param_id, const float val) override
	{
		switch (param_id) {
			case 0:
				cutoffOffset = map_value(val, 0.0f, 1.0f, -1.0f, 1.0f);
				break;
			case 1:
				filterQ = val;
				break;
			case 2:
				mode = val;
				break;
		}
	}
	virtual void set_samplerate(const float sr) override
	{
		bpf.sampleRate.setValue(sr);
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

	virtual float get_led_brightness(const int led_id) const override
	{
		return mode;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<BandpassfilterCore>();
	}
	static constexpr char typeID[20] = "BANDPASSFILTER";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	int mode = 0;
	float filterQ = 1;
	BandPassFilter bpf;
	OberBPF ober;
	float cutoffCV = 0;
	float cutoffOffset = 0;
	float signalInput = 0;
	float signalOutput = 0;
};
