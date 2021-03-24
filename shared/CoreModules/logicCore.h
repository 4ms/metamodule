#pragma once
#include "coreProcessor.h"
#include "moduleTypes.h"
#include "processors/tools/windowComparator.h"
#include "util/math.hh"

using namespace MathTools;

class LogicCore : public CoreProcessor {
	static inline const int NumInJacks = 2;
	static inline const int NumOutJacks = 3;
	static inline const int NumKnobs = 0;

	static inline const std::array<StaticString<NameChars>, NumKnobs> KnobNames{};
	static inline const std::array<StaticString<NameChars>, NumOutJacks> OutJackNames{"AND", "OR", "XOR"};
	static inline const std::array<StaticString<NameChars>, NumInJacks> InJackNames{"Input 1", "Input 2"};
	static inline const StaticString<LongNameChars> description{"Logic"};

	// clang-format off
	virtual StaticString<NameChars> knob_name(unsigned idx) override { return (idx < NumKnobs) ? KnobNames[idx] : ""; }
	virtual StaticString<NameChars> injack_name(unsigned idx) override { return (idx < NumInJacks) ? InJackNames[idx] : ""; }
	virtual StaticString<NameChars> outjack_name(unsigned idx) override { return (idx < NumOutJacks) ? OutJackNames[idx] : ""; }
	virtual StaticString<LongNameChars> get_description() override { return description; }
	// clang-format on
public:
	LogicCore() {}

	virtual void update(void) override
	{
		andOutput = in1.get_output() & in2.get_output();
		orOutput = in1.get_output() | in2.get_output();
		xorOutput = in1.get_output() ^ in2.get_output();
	}

	virtual void set_param(const int param_id, const float val) override {}
	virtual void set_samplerate(const float sr) override {}

	virtual void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			case 0:
				in1.update(val);
				break;
			case 1:
				in2.update(val);
				break;
		}
	}

	virtual float get_output(const int output_id) const override
	{
		float output = 0;
		switch (output_id) {
			case 0:
				output = andOutput;
				break;
			case 1:
				output = orOutput;
				break;
			case 2:
				output = xorOutput;
				break;
		}
		return output;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<LogicCore>();
	}
	static constexpr char typeID[20] = "LOGIC";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	WindowComparator in1;
	WindowComparator in2;
	bool andOutput = 0;
	bool orOutput = 0;
	bool xorOutput = 0;
};
