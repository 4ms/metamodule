#include "doctest.h"
#include "moduleTypes.h"
#include <iostream>
#include <span>
#include <stdint.h>

struct TestCoreMod : public CoreProcessor {
	void update() override {
	}
	void set_samplerate(const float sr) override {
	}
	void set_param(const int param_id, const float val) override {
	}
	void set_input(const int input_id, const float val) override {
	}
	float get_output(const int output_id) const override {
		return 0.f;
	}
};

std::unique_ptr<CoreProcessor> create() {
	return std::unique_ptr<TestCoreMod>();
}

struct TestInfo : ModuleInfoBase {
	static constexpr std::string_view slug{"HIJ"};
	static constexpr uint32_t width_hp = 2;
	static constexpr std::array<KnobDef, 2> Knobs = {{
		{
			.id = 1,
			.x_mm = ModuleInfoBase::px_to_mm<72>(114.85f),
			.y_mm = ModuleInfoBase::px_to_mm<72>(61.59f),
			.short_name = "Spread",
			.long_name = "Spread",
			.default_val = 0.5f,
			.knob_style = KnobDef::Medium,
		},
		{
			.id = 2,
			.x_mm = ModuleInfoBase::px_to_mm<72>(53.68f),
			.y_mm = ModuleInfoBase::px_to_mm<72>(78.08f),
			.short_name = "Scale",
			.long_name = "Scale",
			.default_val = 0.0f,
			.knob_style = KnobDef::Medium,
		},
	}};
};

KnobDef ar[2] = {
	{
		.id = 1,
		.x_mm = ModuleInfoBase::px_to_mm<72>(114.85f),
		.y_mm = ModuleInfoBase::px_to_mm<72>(61.59f),
		.short_name = "Spread",
		.long_name = "Spread",
		.default_val = 0.5f,
		.knob_style = KnobDef::Medium,
	},
	{
		.id = 2,
		.x_mm = ModuleInfoBase::px_to_mm<72>(53.68f),
		.y_mm = ModuleInfoBase::px_to_mm<72>(78.08f),
		.short_name = "Scale",
		.long_name = "Scale",
		.default_val = 0.0f,
		.knob_style = KnobDef::Medium,
	},
};

ModuleInfo testinfo{
	.slug = "mno",
	.width_hp = 4,
	.NumKnobs = TestInfo::Knobs.size(),
	.Knobs = TestInfo::Knobs.data(),
	.KnobSpan = TestInfo::Knobs,

};

TEST_CASE("Register derived object uses its values, not ModuleInfoBase") {
	bool already_exists = ModuleFactory::registerModuleType("ABC", "abc module", create);
	CHECK_FALSE(already_exists);

	already_exists = ModuleFactory::registerModuleType("DEF", "def module", create, testinfo);
	CHECK_FALSE(already_exists);

	// CHECK(ModuleFactory::getModuleInfo("DEF").slug == "mno"); //confusing, slug should be slug
	CHECK(ModuleFactory::getModuleInfo("DEF").width_hp == 4);
	// CHECK(ModuleFactory::getModuleInfo("DEF").NumKnobs == 3);
	auto knobs = ModuleFactory::getModuleInfo("DEF").Knobs;
	CHECK(knobs[0].short_name == "Spread");
	CHECK(knobs[1].short_name == "Scale");
	// CHECK(knobs.size() == 2);
	CHECK(ModuleFactory::getModuleInfo("DEF").NumKnobs == 2);

	CHECK(ModuleFactory::getModuleInfo("DEF").KnobSpan.size() == 2);
	CHECK(ModuleFactory::getModuleInfo("DEF").KnobSpan[0].short_name == "Spread");
	CHECK(ModuleFactory::getModuleInfo("DEF").KnobSpan[1].short_name == "Scale");
}
