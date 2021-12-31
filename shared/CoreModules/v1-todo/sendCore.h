#pragma once
#include "CoreModules/coreProcessor.h"
#include "util/math.hh"
#include "CoreModules/moduleFactory.hh"

using namespace MathTools;

class SendCore : public CoreProcessor {
	static inline const int NumInJacks = 1;
	static inline const int NumOutJacks = 1;
	static inline const int NumKnobs = 4;

	static inline const std::array<StaticString<NameChars>, NumKnobs> KnobNames{"Level 1", "Level 2", "Level 3", "Level 4"};
	static inline const std::array<StaticString<NameChars>, NumOutJacks> OutJackNames{"Output"};
	static inline const std::array<StaticString<NameChars>, NumInJacks> InJackNames{"Input"};
	static inline const StaticString<LongNameChars> description{"Send"};

	// clang-format off
	virtual StaticString<NameChars> knob_name(unsigned idx) override { return (idx < NumKnobs) ? KnobNames[idx] : ""; }
	virtual StaticString<NameChars> injack_name(unsigned idx) override { return (idx < NumInJacks) ? InJackNames[idx] : ""; }
	virtual StaticString<NameChars> outjack_name(unsigned idx) override { return (idx < NumOutJacks) ? OutJackNames[idx] : ""; }
	virtual StaticString<LongNameChars> get_description() override { return description; }
	// clang-format on
public:
	virtual void update(void) override
	{
		for (int i = 0; i < 4; i++) {
			signalOuts[i] = signalInput * levels[i];
		}
	}

	SendCore()
	{
		for (int i = 0; i < 4; i++) {
			levels[i] = 0;
			signalOuts[i] = 0;
		}
	}

	virtual void set_param(int const param_id, const float val) override
	{
		levels[param_id] = val;
	}
	virtual void set_samplerate(const float sr) override {}

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
		output = signalOuts[output_id];
		return output;
	}
	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<SendCore>();
	}
	static constexpr char typeID[20] = "SEND_1TO4";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	float levels[4];
	float signalInput = 0;
	float signalOuts[4];
};
