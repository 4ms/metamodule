#pragma once

#include "coreProcessor.h"
#include "moduleTypes.h"
#include "util/math.hh"
#include "util/math_tables.hh"
#include "util/parameter.h"

using namespace MathTools;

struct LFOCoreDefs {
	using NameString = StaticString<CoreProcessor::NameChars>;
	using DescString = StaticString<CoreProcessor::LongNameChars>;

	static inline const int NumInJacks = 2;
	static inline const int NumOutJacks = 1;
	static inline const int NumKnobs = 3;

	static inline const std::array<NameString, NumKnobs> KnobNames{"Freq", "Phase", "Level"};
	static inline const std::array<NameString, NumOutJacks> OutJackNames{"Sine"};
	static inline const std::array<NameString, NumInJacks> InJackNames{"Freq", "Reset"};
	static inline const DescString description{"SineLFO"};
};

class NodeLFOCore : public CoreProcessor {
public:
	static inline const int NumInJacks = 2;
	static inline const int NumOutJacks = 1;
	static inline const int NumKnobs = 3;

	static inline const std::array<StaticString<NameChars>, NumKnobs> KnobNames{"Freq", "Phase", "Level"};
	static inline const std::array<StaticString<NameChars>, NumOutJacks> OutJackNames{"Sine"};
	static inline const std::array<StaticString<NameChars>, NumInJacks> InJackNames{"Freq", "Reset"};
	static inline const StaticString<LongNameChars> description{"SineLFO"};

	NodeLFOCore() {
		freqJack = 0.f;
		resetJack = 0.f;
		sinOut = 0.f;
	}

	void update() override {

		if (doReset) {
			phaccu = 0.f;
			doReset = false;
		} else {
			phaccu += frequency / sampleRate;
			if (phaccu >= 1.0f)
				phaccu -= 1.0f;
		}
		sinOut = sinTable.interp_wrap(phaccu + phaseOffset) * level;
	}

	// void check_changes() {
	// if (resetJack.isChanged()) {
	// Todo: check hystersis here
	// }
	// }

	//
	void set_param(const int param_id, const float val) override {
		if (param_id == 0) {
			knob_frequency = exp10Table.closest(constrain(val, 0.f, 1.f)); // knob range is 10 octaves
			combineKnobCVFreq();
		}
		if (param_id == 1) {
			phaseOffset = val;
		}
		if (param_id == 2) {
			level = val;
		}
	}

	void set_samplerate(const float sr) override {
		sampleRate = sr;
	}

	void set_input(const int input_id, const float val) override {
		if (input_id == 0) {
			// Freq jack range is -10 .. 10 octaves,
			// Freq jack expects -1..+1 to represent -10V to +10V
			if (val == 0.f)
				cv_frequency = 1.0f;
			else if (val >= 1.f)
				cv_frequency = 1024.f;
			else if (val <= -1.f)
				cv_frequency = 1.f / 1024.f;
			else if (val > 0.f)
				cv_frequency = exp10Table.closest(val);
			else
				cv_frequency = 1.0f / exp10Table.closest(-val);
			combineKnobCVFreq();
		}
		if (input_id == 1) {
			resetJack = val;
			if (resetJack > GateThreshold) {
				if (!lastReset) {
					doReset = true;
				}
				lastReset = true;
			} else
				lastReset = false;
		}
	}

	float get_output(const int output_id) const override {
		if (output_id == 0)
			return sinOut;
		return 0.f;
	}

	// clang-format off
	virtual StaticString<NameChars> knob_name(unsigned idx) override { return (idx < NumKnobs) ? KnobNames[idx] : ""; }
	virtual StaticString<NameChars> injack_name(unsigned idx) override { return (idx < NumInJacks) ? InJackNames[idx] : ""; }
	virtual StaticString<NameChars> outjack_name(unsigned idx) override { return (idx < NumOutJacks) ? OutJackNames[idx] : ""; }
	virtual StaticString<LongNameChars> get_description() override { return description; }
	// clang-format on

	static std::unique_ptr<CoreProcessor> create() {
		return std::make_unique<NodeLFOCore>();
	}
	static constexpr char typeID[20] = "LFOSINE";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	const float GateThreshold = 0.1f;

	Parameter<float> freqJack = nodes[0];
	Parameter<float> resetJack = nodes[1];
	Parameter<float> sinOut = nodes[2];

	// knobs
	float phaseOffset = 0;
	float level = 1;
	float knob_frequency = 1.f;

	// internals
	float cv_frequency = 0.f;
	float phaccu = 0;
	float frequency = 1;
	float sampleRate = 48000;
	bool lastReset = false;
	bool doReset = false;

	void combineKnobCVFreq() {
		frequency = knob_frequency * cv_frequency;
	}
};
