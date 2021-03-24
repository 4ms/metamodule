#pragma once

#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "math.hh"
#include "processors/pitchShift.h"

using namespace MathTools;

class InterpRandomGenerator {
public:
	float frequency = 1;

	float update()
	{
		phaccu += frequency / sampleRate;
		if (phaccu >= 1.0f) {
			phaccu -= 1.0f;
			lastValue = currentValue;
			currentValue = randomNumber(-1.0f, 1.0f);
		}

		outputValue = interpolate(lastValue, currentValue, phaccu);
		return (outputValue);
	}

	void set_samplerate(float sr)
	{
		sampleRate = sr;
	}

private:
	float sampleRate = 96000;
	float currentValue = 0;
	float lastValue = 0;
	float phaccu = 0;
	float outputValue = 0;
};

class DetuneCore : public CoreProcessor {
	static inline const int NumInJacks = 2;
	static inline const int NumOutJacks = 1;
	static inline const int NumKnobs = 4;

	static inline const std::array<StaticString<NameChars>, NumKnobs> KnobNames{"Wow Freq", "Wow Depth","Flutter Freq", "Flutter Depth"};
	static inline const std::array<StaticString<NameChars>, NumOutJacks> OutJackNames{"Output"};
	static inline const std::array<StaticString<NameChars>, NumInJacks> InJackNames{"Input", "CV"};
	static inline const StaticString<LongNameChars> description{"Detune"};

	// clang-format off
	virtual StaticString<NameChars> knob_name(unsigned idx) override { return (idx < NumKnobs) ? KnobNames[idx] : ""; }
	virtual StaticString<NameChars> injack_name(unsigned idx) override { return (idx < NumInJacks) ? InJackNames[idx] : ""; }
	virtual StaticString<NameChars> outjack_name(unsigned idx) override { return (idx < NumOutJacks) ? OutJackNames[idx] : ""; }
	virtual StaticString<LongNameChars> get_description() override { return description; }
	// clang-format on
public:
	virtual void update(void) override
	{
		float addWow = 0;
		float addFlutter = 0;
		float finalWow = 0;
		float finalFlutter = 0;
		if (detuneCvConnected == false) {
			finalWow = wowDepth;
			finalFlutter = flutterDepth;
		} else {
			finalWow = constrain(wowDepth + cvAmount, 0.0f, 1.0f);
			finalFlutter = constrain(flutterDepth + cvAmount, 0.0f, 1.0f);
		}
		addWow = wowGen.update() * (finalWow * finalWow);
		addFlutter = flutterGen.update() * (finalFlutter * finalFlutter);
		p.shiftAmount = addWow + addFlutter;
		signalOutput = p.update(signalInput);
	}

	DetuneCore()
	{
		p.mix = 1.0f;
		p.windowSize = 240;
	}

	virtual void set_param(int const param_id, const float val) override
	{
		switch (param_id) {
			case 0:
				wowGen.frequency = map_value(val, 0.0f, 1.0f, 0.1f, 5.0f);
				break;
			case 1:
				wowDepth = val;
				break;
			case 2:
				flutterGen.frequency = map_value(val, 0.0f, 1.0f, 5.0f, 30.0f);
				break;
			case 3:
				flutterDepth = val;
				break;
		}
	}
	virtual void set_samplerate(const float sr) override
	{
		p.setSampleRate(sr);
		flutterGen.set_samplerate(sr);
		wowGen.set_samplerate(sr);
	}

	virtual void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			case 0:
				signalInput = val;
				break;
			case 1:
				cvAmount = val;
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

	virtual void mark_input_unpatched(const int input_id) override
	{
		if (input_id == 1)
			detuneCvConnected = false;
	}
	virtual void mark_input_patched(const int input_id) override
	{
		if (input_id == 1)
			detuneCvConnected = true;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<DetuneCore>();
	}
	static constexpr char typeID[20] = "DETUNE";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	PitchShift<9600> p;
	float flutterDepth = 0;
	float wowDepth = 0;

	float signalInput = 0;
	float signalOutput = 0;

	bool detuneCvConnected = false;
	float cvAmount = 0;

	InterpRandomGenerator flutterGen;
	InterpRandomGenerator wowGen;
};