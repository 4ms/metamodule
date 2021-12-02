#pragma once
#include "CoreModules/coreProcessor.h"
#include "util/math.hh"
#include "CoreModules/moduleFactory.hh"
#include "processors/tools/windowComparator.h"

using namespace MathTools;

class SampleHoldCore : public CoreProcessor {
	static inline const int NumInJacks = 4;
	static inline const int NumOutJacks = 2;
	static inline const int NumKnobs = 0;

	static inline const std::array<StaticString<NameChars>, NumKnobs> KnobNames{};
	static inline const std::array<StaticString<NameChars>, NumOutJacks> OutJackNames{"Output 1", "Output 2"};
	static inline const std::array<StaticString<NameChars>, NumInJacks> InJackNames{
		"In 1", "Sample 1", "In 2", "Sample 2"};
	static inline const StaticString<LongNameChars> description{"Sample and Hold"};

	// clang-format off
	virtual StaticString<NameChars> knob_name(unsigned idx) override { return (idx < NumKnobs) ? KnobNames[idx] : ""; }
	virtual StaticString<NameChars> injack_name(unsigned idx) override { return (idx < NumInJacks) ? InJackNames[idx] : ""; }
	virtual StaticString<NameChars> outjack_name(unsigned idx) override { return (idx < NumOutJacks) ? OutJackNames[idx] : ""; }
	virtual StaticString<LongNameChars> get_description() override { return description; }
	// clang-format on
public:
	virtual void update(void) override
	{
		lastSample1 = currentSample1;
		currentSample1 = sample1.get_output();

		lastSample2 = currentSample2;
		currentSample2 = sample2.get_output();

		if (currentSample1 > lastSample1) {
			out1 = in1;
		}

		if (currentSample2 > lastSample2) {
			out2 = in2;
		}
	}

	SampleHoldCore() {}

	virtual void set_param(const int param_id, const float val) override {}
	virtual void set_samplerate(const float sr) override {}

	virtual void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			case 0: {
				if (in1Connected == 1) {
					in1 = val;
				} else {
					in1 = randomNumber(-1.0f, 1.0f);
				}
			} break;
			case 1:
				sample1.update(val);
				break;
			case 2: {
				if (in2Connected == 1) {
					in2 = val;
				} else {
					in2 = randomNumber(-1.0f, 1.0f);
				}
			} break;
			case 3:
				sample2.update(val);
				break;
		}
	}

	virtual float get_output(const int output_id) const override
	{
		float output = 0;
		switch (output_id) {
			case 0:
				output = out1;
				break;
			case 1:
				output = out2;
				break;
		}
		return output;
	}

	virtual void mark_input_unpatched(const int input_id) override
	{
		if (input_id == 0)
			in1Connected = 0;
		else if (input_id == 2)
			in2Connected = 0;
	}
	virtual void mark_input_patched(const int input_id) override
	{
		if (input_id == 0)
			in1Connected = 1;
		else if (input_id == 2)
			in2Connected = 1;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<SampleHoldCore>();
	}
	static constexpr char typeID[20] = "SAMPHOLD";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	float in1 = 0;
	float in2 = 0;
	WindowComparator sample1;
	WindowComparator sample2;
	float out1 = 0;
	float out2 = 0;

	int currentSample1 = 0;
	int lastSample1 = 0;
	int currentSample2 = 0;
	int lastSample2 = 0;

	int in1Connected = 0;
	int in2Connected = 0;
};
