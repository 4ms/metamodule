#pragma once

#include "CoreModules/coreProcessor.h"
#include "CoreModules/moduleFactory.hh"
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
	PitchshiftCore() {
	}

	void update(void) override {
		auto finalWindow = constrain(windowOffset + windowCV, 0.0f, 1.0f);
		p.windowSize = map_value(finalWindow, 0.0f, 1.0f, 20.0f, static_cast<float>(maxWindowSize));
		p.shiftAmount = coarseShift + fineShift + (shiftCV * 12.0f);
		p.mix = constrain(mixOffset + mixCV, 0.0f, 1.0f);
		signalOutput = p.update(signalInput);
	}

	void set_param(int const param_id, const float val) override {
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
	void set_samplerate(const float sr) override {
		p.setSampleRate(sr);
	}

	void set_input(const int input_id, const float val) override {
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

	float get_output(const int output_id) const override {
		float output = 0;
		switch (output_id) {
			case 0:
				output = signalOutput;
				break;
		}
		return output;
	}

	static std::unique_ptr<CoreProcessor> create() {
		return std::make_unique<PitchshiftCore>();
	}

	static constexpr char typeID[20] = "PITCHSHIFT";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	const static inline long maxWindowSize = 9600;
	PitchShift<maxWindowSize> p;

	float signalInput = 0;
	float shiftCV = 0;
	float windowCV = 0;
	float mixCV = 0;
	float signalOutput = 0;
	float coarseShift = 0;
	float fineShift = 0;
	float mixOffset = 0;
	float windowOffset = 100;
};
