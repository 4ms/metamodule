#pragma once

#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "processors/tools/clockPhase.h"
#include "util/math.hh"

using namespace MathTools;

class EightstepprobCore : public CoreProcessor {
	static inline const int NumInJacks = 2;
	static inline const int NumOutJacks = 1;
	static inline const int NumKnobs = 8;

	static inline const std::array<StaticString<NameChars>, NumKnobs> KnobNames{"Step 1", "Step 2", "Step 3", "Step 4", "Step 5", "Step 6", "Step 7", "Step 8"};
	static inline const std::array<StaticString<NameChars>, NumOutJacks> OutJackNames{"Output"};
	static inline const std::array<StaticString<NameChars>, NumInJacks> InJackNames{"Clock In", "Reset In"};
	static inline const StaticString<LongNameChars> description{"8 Step Probabilistic Gate Sequencer"};

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
		lastStep = currentStep;
		currentStep = cp.getCount() % 8;
		if (currentStep != lastStep) {
			randNum = randomNumber(0.0f, 0.99f);
		}
		if ((prob[currentStep] > randNum) && (cp.getWrappedPhase() < 0.5f)) {
			gateOutput = 1;
		} else {
			gateOutput = 0;
		}
	}

	EightstepprobCore() {}

	virtual void set_param(int const param_id, const float val) override
	{
		prob[param_id] = val;
	}
	virtual void set_samplerate(const float sr) override {}

	virtual void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			case 0:
				cp.updateClock(val);
				break;
			case 1:
				cp.updateReset(val);
				break;
		}
	}

	virtual float get_output(const int output_id) const override
	{
		float output = 0;
		switch (output_id) {
			case 0:
				output = gateOutput;
				break;
		}
		return output;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<EightstepprobCore>();
	}
	static constexpr char typeID[20] = "EIGHTSTEPPROB";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	float prob[8] = {1, 0, 0, 0, 0, 0, 0, 0};

	int gateOutput;

	int currentStep;
	int lastStep;

	float randNum = 0;
	ClockPhase cp;
};
