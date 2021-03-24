#pragma once

#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "math.hh"
#include "processors/stepsequencer.h"

using namespace MathTools;

class EightstepCore : public CoreProcessor {
	static inline const int NumInJacks = 2;
	static inline const int NumOutJacks = 2;
	static inline const int NumKnobs = 9;

	static inline const std::array<StaticString<NameChars>, NumKnobs> KnobNames{"Step 1","Step 2","Step 3", "Step 4", "Step 5", "Step 6", "Step 7", "Step 8", "Length"};
	static inline const std::array<StaticString<NameChars>, NumOutJacks> OutJackNames{"End","Output"};
	static inline const std::array<StaticString<NameChars>, NumInJacks> InJackNames{"Clock In", "Reset In"};
	static inline const StaticString<LongNameChars> description{"Eight Step CV Sequencer"};

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

	EightstepCore() {}

	virtual void set_param(int const param_id, const float val) override
	{
		if(param_id<8)
		seq->setStep(param_id, val);
		else
		{
			seq->setLength(map_value(val,0.0f,1.0f,0,8));
		}
		
	}
	virtual void set_samplerate(const float sr) override {}

	virtual void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			case 0:
				seq->updateClock(val);
				break;
			case 1:
				seq->updateReset(val);
				break;
		}
	}

	virtual float get_output(const int output_id) const override
	{
		float output = 0;
		switch (output_id) {
			case 0:
				output = seq->endOutput;
				break;
			case 1:
				output = seq->output;
				break;
		}
		return output;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<EightstepCore>();
	}
	static constexpr char typeID[20] = "EIGHTSTEP";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	std::unique_ptr<StepSequencer> seq = std::make_unique<StepSequencer>(8);
};
