#pragma once

#include "CoreModules/moduleFactory.hh"
#include "CoreModules/coreProcessor.h"
#include "processors/stepsequencer.h"
#include "util/math.hh"

using namespace MathTools;

class FourstepCore : public CoreProcessor {
	static inline const int NumInJacks = 1;
	static inline const int NumOutJacks = 1;
	static inline const int NumKnobs = 4;

	static inline const std::array<StaticString<NameChars>, NumKnobs> KnobNames{"Step 1", "Step 2", "Step 3", "Step 4"};
	static inline const std::array<StaticString<NameChars>, NumOutJacks> OutJackNames{"Output"};
	static inline const std::array<StaticString<NameChars>, NumInJacks> InJackNames{"Clock In"};
	static inline const StaticString<LongNameChars> description{"4 Step Sequencer"};

	// clang-format off
	virtual StaticString<NameChars> knob_name(unsigned idx) override { return (idx < NumKnobs) ? KnobNames[idx] : ""; }
	virtual StaticString<NameChars> injack_name(unsigned idx) override { return (idx < NumInJacks) ? InJackNames[idx] : ""; }
	virtual StaticString<NameChars> outjack_name(unsigned idx) override { return (idx < NumOutJacks) ? OutJackNames[idx] : ""; }
	virtual StaticString<LongNameChars> get_description() override { return description; }
	// clang-format on
public:
	virtual void update(void) override
	{
		seq->update();
	}

	FourstepCore() {}

	virtual void set_param(int const param_id, const float val) override
	{
		seq->setStep(param_id, val);
	}
	virtual void set_samplerate(const float sr) override {}

	virtual void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			case 0:
				seq->updateClock(val);
				break;
		}
	}

	virtual float get_output(const int output_id) const override
	{
		float output = 0;
		switch (output_id) {
			case 0:
				output = seq->output;
				break;
		}
		return output;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<FourstepCore>();
	}
	static constexpr char typeID[20] = "FOURSTEP";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	std::unique_ptr<StepSequencer> seq = std::make_unique<StepSequencer>(4);
};
