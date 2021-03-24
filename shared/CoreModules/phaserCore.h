#pragma once

#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "math.hh"
#include "processors/phaser.h"

using namespace MathTools;

class PhaserCore : public CoreProcessor {
	static inline const int NumInJacks = 1;
	static inline const int NumOutJacks = 1;
	static inline const int NumKnobs = 6;

	static inline const std::array<StaticString<NameChars>, NumKnobs> KnobNames{"LFO Speed", "LFO Depth", "Freq Min", "Freq Max", "Width", "Feedback"};
	static inline const std::array<StaticString<NameChars>, NumOutJacks> OutJackNames{"Output"};
	static inline const std::array<StaticString<NameChars>, NumInJacks> InJackNames{"Input"};
	static inline const StaticString<LongNameChars> description{"Phaser"};

	// clang-format off
	virtual StaticString<NameChars> knob_name(unsigned idx) override { return (idx < NumKnobs) ? KnobNames[idx] : ""; }
	virtual StaticString<NameChars> injack_name(unsigned idx) override { return (idx < NumInJacks) ? InJackNames[idx] : ""; }
	virtual StaticString<NameChars> outjack_name(unsigned idx) override { return (idx < NumOutJacks) ? OutJackNames[idx] : ""; }
	virtual StaticString<LongNameChars> get_description() override { return description; }
	// clang-format on
public:
	virtual void update(void) override
	{
		signalOutput = phaser.update(signalInput);
	}

	PhaserCore() {}

	virtual void set_param(int const param_id, const float val) override
	{
		switch (param_id) {
			case 0:
				phaser.lfoSpeed.setValue(val);
				break;
			case 1:
				phaser.lfoDepth.setValue(val);
				break;
			case 2:
				phaser.freqMin.setValue(val);
				break;
			case 3:
				phaser.freqMax.setValue(val);
				break;
			case 4:
				phaser.width.setValue(val);
				break;
			case 5:
				phaser.feedback.setValue(val);
				break;
		}
	}
	virtual void set_samplerate(const float sr) override
	{
		phaser.sampleRate.setValue(sr);
	}

	virtual void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			case 0:
				signalInput = val;
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
		return std::make_unique<PhaserCore>();
	}
	static constexpr char typeID[20] = "PHASER";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	Phaser phaser;

	float signalInput;
	float signalOutput;
};
