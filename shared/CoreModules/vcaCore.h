#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/moduleFactory.hh"
#include "util/math.hh"
#include "util/parameter.h"

using namespace MathTools;

class VCACore : public CoreProcessor {
	static inline const int NumInJacks = 2;
	static inline const int NumOutJacks = 1;
	static inline const int NumKnobs = 4;

	static inline const std::array<StaticString<NameChars>, NumKnobs> KnobNames{
		"Pre Gain", "Post Gain", "Offset", "CV"};
	static inline const std::array<StaticString<NameChars>, NumOutJacks> OutJackNames{"Output"};
	static inline const std::array<StaticString<NameChars>, NumInJacks> InJackNames{"Input", "CV"};
	static inline const StaticString<LongNameChars> description{"VCA"};

	// clang-format off
	virtual StaticString<NameChars> knob_name(unsigned idx) override { return (idx < NumKnobs) ? KnobNames[idx] : ""; }
	virtual StaticString<NameChars> injack_name(unsigned idx) override { return (idx < NumInJacks) ? InJackNames[idx] : ""; }
	virtual StaticString<NameChars> outjack_name(unsigned idx) override { return (idx < NumOutJacks) ? OutJackNames[idx] : ""; }
	virtual StaticString<LongNameChars> get_description() override { return description; }
	// clang-format on
public:
	VCACore() = default;

	virtual void update(void) override {
		auto clippedOutput = constrain(input * preGain, -1.0f, 1.0f);
		auto vcaCtrl = constrain(offset + cv * cvAmount, -1.0f, 1.0f) * postGain;
		vcaOutput = clippedOutput * vcaCtrl;
	}

	virtual void set_param(int const param_id, const float val) override {
		switch (param_id) {
			case 0:
				preGain = map_value(val, 0.0f, 1.0f, 1.0f, 20.0f);
				break;
			case 1:
				postGain = val;
				break;
			case 2:
				offset = val;
				break;
			case 3:
				cvAmount = val;
				break;
		}
	}
	virtual void set_samplerate(const float sr) override {
	}

	virtual void set_input(const int input_id, const float val) override {
		switch (input_id) {
			case 0:
				input = val;
				break;
			case 1:
				cv = val;
				break;
		}
	}

	virtual float get_output(const int output_id) const override {
		float output = 0;
		switch (output_id) {
			case 0:
				output = vcaOutput;
				break;
		}
		return output;
	}

	static std::unique_ptr<CoreProcessor> create() {
		return std::make_unique<VCACore>();
	}
	static constexpr char typeID[20] = "VCA";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	float input = 0;
	float cv = 0;
	float vcaOutput = 0;

	float preGain = 1;
	float postGain = 1;
	float offset = 0;
	float cvAmount;
};
