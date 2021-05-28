#pragma once

#include "CoreModules/coreProcessor.h"
#include "CoreModules/moduleTypes.h"
#include "processors/pitchShift.h"
#include "util/math.hh"

using namespace MathTools;

class PitchshiftCore : public CoreProcessor {
	static inline const int NumInJacks = 4;
	static inline const int NumOutJacks = 1;
	static inline const int NumKnobs = 4;

	static inline const std::array<StaticString<NameChars>, NumKnobs> KnobNames{"Coarse", "Fine", "Window", "Mix"};
	static inline const std::array<StaticString<NameChars>, NumOutJacks> OutJackNames{"Output"};
	static inline const std::array<StaticString<NameChars>, NumInJacks> InJackNames{"Input", "Shift", "Window", "Mix"};
	static inline const StaticString<LongNameChars> description{"Pitch Shifter"};

	// clang-format off
	virtual StaticString<NameChars> knob_name(unsigned idx) override { return (idx < NumKnobs) ? KnobNames[idx] : ""; }
	virtual StaticString<NameChars> injack_name(unsigned idx) override { return (idx < NumInJacks) ? InJackNames[idx] : ""; }
	virtual StaticString<NameChars> outjack_name(unsigned idx) override { return (idx < NumOutJacks) ? OutJackNames[idx] : ""; }
	virtual StaticString<LongNameChars> get_description() override { return description; }
	// clang-format on
public:
	PitchshiftCore() {}

	PitchshiftCore(float &in, float &shift, float &window, float &mix, float &out)
		: signalInput{in}
		, shiftCV{shift}
		, windowCV{window}
		, mixCV{mix}
		, signalOutput{out}
	{}

	virtual void update(void) override
	{
		auto finalWindow = constrain(windowOffset + windowCV, 0.0f, 1.0f);
		p.windowSize = map_value(finalWindow, 0.0f, 1.0f, 20.0f, static_cast<float>(maxWindowSize));
		p.shiftAmount = coarseShift + fineShift + (shiftCV * 12.0f);
		p.mix = constrain(mixOffset + mixCV, 0.0f, 1.0f);
		signalOutput = p.update(signalInput);
	}

	virtual void set_param(int const param_id, const float val) override
	{
		switch (param_id) {
			case 0:
				coarseShift = map_value(val, 0.0f, 1.0f, -12.0f, 12.0f);
				break;
			case 1:
				fineShift = map_value(val, 0.0f, 1.0f, -1.0f, 1.0f);
				break;
			case 2:
				windowOffset = val;
				break;
			case 3:
				mixOffset = val;
				break;
		}
	}
	virtual void set_samplerate(const float sr) override
	{
		p.setSampleRate(sr);
	}

	virtual void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			case 0:
				signalInput = val;
				break;
			case 1:
				shiftCV = val;
				break;
			case 2:
				windowCV = val;
				break;
			case 3:
				mixCV = val;
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
		return std::make_unique<PitchshiftCore>();
	}
	static std::unique_ptr<CoreProcessor> create(float *nodelist, const uint8_t *idx)
	{
		return std::make_unique<PitchshiftCore>(
			nodelist[idx[0]], nodelist[idx[1]], nodelist[idx[2]], nodelist[idx[3]], nodelist[idx[4]]);
	}
	static constexpr char typeID[20] = "PITCHSHIFT";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);
	static inline bool s_registered_wp =
		ModuleFactory::registerModuleType(typeID, description, create, NumInJacks, NumOutJacks, NumKnobs);

private:
	const static inline long maxWindowSize = 9600;
	PitchShift<maxWindowSize> p;

	float &signalInput = nodes[0];
	float &shiftCV = nodes[1];
	float &windowCV = nodes[2];
	float &mixCV = nodes[3];
	float &signalOutput = nodes[4];

	float coarseShift = 0;
	float fineShift = 0;
	float mixOffset = 0;
	float windowOffset = 100;
};
