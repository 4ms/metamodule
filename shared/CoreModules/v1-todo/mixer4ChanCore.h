#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/moduleFactory.hh"
#include "util/math.hh"
#include "util/parameter.h"

using namespace MathTools;

class NodeMixer4Core : public CoreProcessor {
public:
	static inline const int NumInJacks = 4;
	static inline const int NumOutJacks = 2;
	static inline const int NumKnobs = 4;

	static inline const std::array<StaticString<NameChars>, NumKnobs> KnobNames{
		"Level 1", "Level 2", "Level 3", "Level 4"};
	static inline const std::array<StaticString<NameChars>, NumOutJacks> OutJackNames{"Mix", "Inv. Mix"};
	static inline const std::array<StaticString<NameChars>, NumInJacks> InJackNames{"In 1", "In 2", "In 3", "In 4"};
	static inline const StaticString<LongNameChars> description{"MIXER"};

	// clang-format off
	virtual StaticString<NameChars> knob_name(unsigned idx) override { return (idx < NumKnobs) ? KnobNames[idx] : ""; }
	virtual StaticString<NameChars> injack_name(unsigned idx) override { return (idx < NumInJacks) ? InJackNames[idx] : ""; }
	virtual StaticString<NameChars> outjack_name(unsigned idx) override { return (idx < NumOutJacks) ? OutJackNames[idx] : ""; }
	virtual StaticString<LongNameChars> get_description() override { return description; }
	// clang-format on

	NodeMixer4Core() {
	}

	void update() override {
		float sum = 0;
		for (int i = 0; i < 4; i++) {
			sum += inputs[i] * levels[i];
		}
		mixOut[0] = sum;
		mixOut[1] = -sum;
	}

	void set_param(const int param_id, const float val) override {
		if (param_id >= 4)
			return;
		levels[param_id] = val;
	}
	void set_samplerate(const float sr) override {
	}

	void set_input(const int input_id, const float val) override {
		if (input_id >= 4)
			return;
		inputs[input_id] = val;
	}

	float get_output(const int output_id) const override {
		switch (output_id) {
			case 0:
				return mixOut[0];
			case 1:
				return mixOut[1];
			default:
				return 0.f;
		}
	}

	static std::unique_ptr<CoreProcessor> create() {
		return std::make_unique<NodeMixer4Core>();
	}
	static constexpr char typeID[20] = "MIXER4";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	float inputs[4] = {0, 0, 0, 0};
	float mixOut[2] = {0, 0};
	float levels[4] = {0, 0, 0, 0};
};
