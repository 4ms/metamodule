#pragma once

#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "util/math.hh"

using namespace MathTools;

class TemplateCore : public CoreProcessor {
	static inline const int NumInJacks = 1;
	static inline const int NumOutJacks = 1;
	static inline const int NumKnobs = 1;

	static inline const std::array<StaticString<NameChars>, NumKnobs> KnobNames{};
	static inline const std::array<StaticString<NameChars>, NumOutJacks> OutJackNames{};
	static inline const std::array<StaticString<NameChars>, NumInJacks> InJackNames{};
	static inline const StaticString<LongNameChars> description{"DESCRIPTION"};

public:
	void update(void) override {}

	TemplateCore() {}

	void set_param(int const param_id, const float val) override
	{
		switch (param_id) {
		}
	}
	void set_samplerate(const float sr) override {}

	void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
		}
	}

	float get_output(const int output_id) const override
	{
		float output = 0;
		switch (output_id) {
		}
		return output;
	}

private:
public:
	// Auto generated:
	// clang-format off
	static constexpr char typeID[20] = "SLUG";
	static std::unique_ptr<CoreProcessor> create() { return std::make_unique<TemplateCore>(); }
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);
	StaticString<NameChars> knob_name(unsigned idx) override { return (idx < NumKnobs) ? KnobNames[idx] : ""; }
	StaticString<NameChars> injack_name(unsigned idx) override { return (idx < NumInJacks) ? InJackNames[idx] : ""; }
	StaticString<NameChars> outjack_name(unsigned idx) override { return (idx < NumOutJacks) ? OutJackNames[idx] : ""; }
	StaticString<LongNameChars> get_description() override { return description; }
	// clang-format on
};
