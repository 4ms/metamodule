#pragma once
#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "util/math.hh"

using namespace MathTools;

class AttCore : public CoreProcessor {
	static inline const int NumInJacks = 2;
	static inline const int NumOutJacks = 2;
	static inline const int NumKnobs = 2;

	static inline const std::array<StaticString<NameChars>, NumKnobs> KnobNames{"Level 1", "Level 2"};
	static inline const std::array<StaticString<NameChars>, NumOutJacks> OutJackNames{"Out 1", "Out 2"};
	static inline const std::array<StaticString<NameChars>, NumInJacks> InJackNames{"In 1", "In 2"};
	static inline const StaticString<LongNameChars> description{"Attenuverter"};

	// clang-format off
	virtual StaticString<NameChars> knob_name(unsigned idx) override { return (idx < NumKnobs) ? KnobNames[idx] : ""; }
	virtual StaticString<NameChars> injack_name(unsigned idx) override { return (idx < NumInJacks) ? InJackNames[idx] : ""; }
	virtual StaticString<NameChars> outjack_name(unsigned idx) override { return (idx < NumOutJacks) ? OutJackNames[idx] : ""; }
	virtual StaticString<LongNameChars> get_description() override { return description; }
	// clang-format on

public:
	virtual void update(void) override {
		out1 = (in1Connected ? in1 : 1.f) * level1;
		out2 = (in2Connected ? in2 : 1.f) * level2;
	}

	AttCore() = default;

	void set_param(int param_id, float val) override {
		float mappedVal = map_value(val, 0.0f, 1.0f, -1.0f, 1.0f);
		switch (param_id) {
			case 0:
				level1 = mappedVal;
				break;
			case 1:
				level2 = mappedVal;
				break;
		}
	}

	void set_samplerate(const float sr) override {
	}

	void set_input(int input_id, float val) override {
		switch (input_id) {
			case 0:
				in1 = val;
				break;
			case 1:
				in2 = 1.0f;
				break;
			default:
				break;
		}
	}

	float get_output(int output_id) const override {
		switch (output_id) {
			case 0:
				return out1;
				break;
			case 1:
				return out2;
				break;
			default:
				return 0;
				break;
		}
	}

	void mark_input_unpatched(int input_id) override {
		if (input_id == 0)
			in1Connected = false;
		else if (input_id == 1)
			in2Connected = false;
	}

	void mark_input_patched(int input_id) override {
		if (input_id == 0)
			in1Connected = true;
		else if (input_id == 1)
			in2Connected = true;
	}

	static std::unique_ptr<CoreProcessor> create() {
		return std::make_unique<AttCore>();
	}
	static constexpr char typeID[20] = "ATTENVERT2";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	float in1 = 0;
	float in2 = 0;
	float out1 = 0;
	float out2 = 0;
	float level1 = 0;
	float level2 = 0;

	bool in1Connected = false;
	bool in2Connected = false;
};
