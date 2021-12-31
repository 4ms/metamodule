#pragma once

#include "../processors/lpg.h"
#include "../processors/tools/expDecay.h"
#include "CoreModules/moduleFactory.hh"
#include "CoreModules/coreProcessor.h"
#include "util/math.hh"
#include "processors/tools/windowComparator.h"

using namespace MathTools;

class LowpassgateCore : public CoreProcessor {
	static inline const int NumInJacks = 3;
	static inline const int NumOutJacks = 1;
	static inline const int NumKnobs = 3;

	static inline const std::array<StaticString<NameChars>, NumKnobs> KnobNames{"Level", "CV", "Decay"};
	static inline const std::array<StaticString<NameChars>, NumOutJacks> OutJackNames{"Output"};
	static inline const std::array<StaticString<NameChars>, NumInJacks> InJackNames{"CV", "Input", "Ping"};
	static inline const StaticString<LongNameChars> description{"Lowpass Gate"};

	// clang-format off
	virtual StaticString<NameChars> knob_name(unsigned idx) override { return (idx < NumKnobs) ? KnobNames[idx] : ""; }
	virtual StaticString<NameChars> injack_name(unsigned idx) override { return (idx < NumInJacks) ? InJackNames[idx] : ""; }
	virtual StaticString<NameChars> outjack_name(unsigned idx) override { return (idx < NumOutJacks) ? OutJackNames[idx] : ""; }
	virtual StaticString<LongNameChars> get_description() override { return description; }
	// clang-format on
public:
	virtual void update(void) override
	{
		wc.update(pingIn);
		pingLast = pingCurrent;
		pingCurrent = wc.get_output();
		if (pingCurrent > pingLast) {
			sincePing = 0;
		}
		pulseOut = sincePing < pulseTime;
		float levelCV = levelControl + cvAmount * cvInput + pulseOut;
		levelCV = constrain(levelCV, 0.0f, 1.0f);
		lpg.level.setValue(levelCV);
		signalOutput = (lpg.update(signalInput));
		sincePing++;
	}

	LowpassgateCore() {}

	virtual void set_param(int const param_id, const float val) override
	{
		if (param_id == 0) {
			levelControl = val;
		}
		if (param_id == 1) {
			cvAmount = val;
		}
		if (param_id == 2) {
			lpg.decayTime.setValue(map_value(val, 0.F, 1.F, 10.F, 1000.0F));
		}
	}
	virtual void set_samplerate(const float sr) override
	{
		lpg.sampleRate.setValue(sr);
		pulseTime = 12 / 1000.0f * sr;
	}

	virtual void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			case 0:
				cvInput = val;
				break;
			case 1:
				signalInput = val;
				break;
			case 2:
				pingIn = val;
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
		return std::make_unique<LowpassgateCore>();
	}
	static constexpr char typeID[20] = "LOWPASSGATE";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	float signalInput = 0;
	float signalOutput = 0;
	float cvInput = 0;
	float cvAmount = 0;
	LowPassGate lpg;
	float levelControl = 1;
	float pingCurrent = 0;
	float pingLast = 0;
	float pingIn = 0;
	float pulseOut = 0;
	WindowComparator wc;
	long sincePing = 0;
	long pulseTime = 300;
};
