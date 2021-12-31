#pragma once

#include "CoreModules/moduleFactory.hh"
#include "CoreModules/coreProcessor.h"
#include "util/math.hh"
#include "processors/tools/clockPhase.h"

using namespace MathTools;

class Gateseq8Core : public CoreProcessor {
	static inline const int NumInJacks = 1;
	static inline const int NumOutJacks = 9;
	static inline const int NumKnobs = 0;

	static inline const std::array<StaticString<NameChars>, NumKnobs> KnobNames{};
	static inline const std::array<StaticString<NameChars>, NumOutJacks> OutJackNames{"Output", "Step 1", "Step 2", "Step 3", "Step 4", "Step 5", "Step 6", "Step 7", "Step 8"};
	static inline const std::array<StaticString<NameChars>, NumInJacks> InJackNames{"Clock In"};
	static inline const StaticString<LongNameChars> description{"8 Step Gate Sequencer"};

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
		stepPhase = cp.getWrappedPhase();
		currentStep = (int)(cp.getPhase())%8;
		if (stepActive[currentStep] && (stepPhase < 0.5f)) {
			gateOutput = 1;
		} else {
			gateOutput = 0;
		}
	}

	Gateseq8Core()
	{
		for (int i = 0; i < 8; i++) {
			stepActive[i] = false;
		}
	}

	virtual void set_param(int const param_id, const float val) override
	{
		if (param_id > 7 || param_id < 0) {
			return;
		}

		stepActive[param_id] = val > 0.0f;
	}

	virtual void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			case 0:
				cp.updateClock(val);
				break;
		}
	}

	virtual void set_samplerate(const float sr) override
	{
	}

	virtual float get_output(const int output_id) const override
	{
		float output = 0;
		if(output_id==0)
		{
			output=gateOutput;
		}
		else
		{
			currentStep == (output_id-1) ? output =1 : output =0;
		}
		
		return output;
	}

	virtual float get_led_brightness(const int led_id) const override
	{
		bool stepStatus = stepActive[led_id];
		bool countStatus = (currentStep==led_id) && (stepPhase<0.5f);
		return stepStatus^countStatus;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<Gateseq8Core>();
	}
	static constexpr char typeID[20] = "GATESEQ8";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	ClockPhase cp;
	int currentStep = 0;
	float gateOutput = 0;
	bool stepActive[8];
	float stepPhase=0;
};
