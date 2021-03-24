#pragma once

#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "processors/twoOpFMOscillator.h"
#include "util/math.hh"

using namespace MathTools;

class FmoscCore : public CoreProcessor {
	static inline const int NumInJacks = 5;
	static inline const int NumOutJacks = 1;
	static inline const int NumKnobs = 8;

	static inline const std::array<StaticString<NameChars>, NumKnobs> KnobNames{"Pitch", "Index", "Ratio Coarse", "Ratio Fine", "Shape", "Shape Amount", "Index Amount", "Mix"};
	static inline const std::array<StaticString<NameChars>, NumOutJacks> OutJackNames{"Output"};
	static inline const std::array<StaticString<NameChars>, NumInJacks> InJackNames{"Index CV", "Pitch 1", "Shape", "Mix", "Pitch 2"};
	static inline const StaticString<LongNameChars> description{"FM Oscillator"};

	// clang-format off
	virtual StaticString<NameChars> knob_name(unsigned idx) override { return (idx < NumKnobs) ? KnobNames[idx] : ""; }
	virtual StaticString<NameChars> injack_name(unsigned idx) override { return (idx < NumInJacks) ? InJackNames[idx] : ""; }
	virtual StaticString<NameChars> outjack_name(unsigned idx) override { return (idx < NumOutJacks) ? OutJackNames[idx] : ""; }
	virtual StaticString<LongNameChars> get_description() override { return description; }
	// clang-format on
public:
	virtual void update(void) override
	{
		fm.set_frequency(0, basePitch * setPitchMultiple(pitchInput));
		if (secondPitchConnected == false) {
			fm.set_frequency(1, basePitch * ratioFine * ratioCoarse);
		} else {
			fm.set_frequency(1, basePitch * setPitchMultiple(secondPitchInput));
		}
		totalIndex = constrain(indexCV * indexAmount + indexKnob, 0.0f, 1.0f);
		float totalShape = constrain(shapeCV * shapeAmount + shapeKnob, 0.0f, 1.0f);
		fm.shape = totalShape;
		fm.modAmount = totalIndex;
		float finalMix = constrain(mixCV + mix, 0.0f, 1.0f);
		fm.mix = finalMix;
		mainOutput = fm.update();
	}

	FmoscCore() {}

	virtual void set_param(int const param_id, const float val) override
	{
		switch (param_id) {
			case 0:
				basePitch = 20.0f * expTable.interp(val);
				break;
			case 1:
				indexKnob = val;
				break;
			case 2:
				ratioCoarse = ratioTable[map_value(val, 0.0f, 1.0f, 0, 7)];
				break;
			case 3: {
				if (val < 0.5f)
					ratioFine = map_value(val, 0.0f, 0.5f, 0.5f, 1.0f);
				else
					ratioFine = map_value(val, 0.5f, 1.0f, 1.0f, 2.0f);
				break;
			}
			case 4:
				shapeKnob = val;
				break;
			case 5:
				shapeAmount = val;
				break;
			case 6:
				indexAmount = val;
				break;
			case 7:
				mix = val;
				break;
		}
	}
	virtual void set_samplerate(const float sr) override
	{
		fm.set_samplerate(sr);
	}

	virtual void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			case 0:
				indexCV = val;
				break;
			case 1:
				pitchInput = val;
				break;
			case 2:
				shapeCV = val;
				break;
			case 3:
				mixCV = val;
				break;
			case 4:
				secondPitchInput = val;
				break;
		}
	}

	virtual float get_output(const int output_id) const override
	{
		float output = 0;
		switch (output_id) {
			case 0:
				output = mainOutput;
				break;
		}
		return output;
	}

	virtual void mark_input_unpatched(const int input_id) override
	{
		if (input_id == 4) {
			secondPitchConnected = false;
		}
	}
	virtual void mark_input_patched(const int input_id) override
	{
		if (input_id == 4) {
			secondPitchConnected = true;
		}
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<FmoscCore>();
	}
	static constexpr char typeID[20] = "FMOSC";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	TwoOpFM fm;
	float ratioCoarse = 1;
	float ratioFine = 1;
	float mix = 0;
	float mixCV = 0;
	float basePitch = 0;
	float mainOutput;
	float indexKnob = 0;
	float secondPitchInput = 0;
	bool secondPitchConnected = false;
	float indexCV = 0;
	float shapeKnob = 0;
	float shapeCV = 0;
	float totalIndex = 0;
	float pitchInput = 0;
	float shapeAmount = 0;
	float indexAmount = 0;

	const float ratioTable[8] = {0.125f, 0.25f, 0.5f, 1, 2, 4, 8, 16};
};
