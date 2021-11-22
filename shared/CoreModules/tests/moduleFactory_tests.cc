#include "doctest.h"
#include "info/EnOsc_info.hh"
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

constexpr ModuleInfoView testinfo{
	.width_hp = 4,
	.svg_filename = "",
	.Knobs = TestInfo::Knobs,
};

TEST_CASE("Register ModuleTypes with an object constructed from static constexpr members of ModuleInfoBase") {
	bool already_exists = ModuleFactory::registerModuleType("ABC", "abc module", create);
	auto slug = ModuleFactory::getModuleSlug("ABC");
	CHECK(slug == "ABC");
	CHECK_FALSE(already_exists);

	SUBCASE("Test if Knob info get stored and retreived OK") {
		already_exists = ModuleFactory::registerModuleType("DEF", "def module", create, testinfo);
		CHECK_FALSE(already_exists);

		CHECK(ModuleFactory::getModuleInfo("DEF").width_hp == 4);
		auto knobs = ModuleFactory::getModuleInfo("DEF").Knobs;
		CHECK(knobs[0].short_name == "Spread");
		CHECK(knobs[1].short_name == "Scale");
		CHECK(knobs.size() == 2);

		SUBCASE("Test actual EnOscInfo data") {
			already_exists = ModuleFactory::registerModuleType(
				"EnOsc2", "EnOsc module", create, ModuleInfoView::makeView<EnOscInfo>());
			// already_exists = ModuleFactory::registerModuleType("EnOsc2",
			// 												   "EnOsc module",
			// 												   create,
			// 												   {
			// 													   .width_hp = EnOscInfo::width_hp,
			// 													   .svg_filename = EnOscInfo::svg_filename,
			// 													   .Knobs = EnOscInfo::Knobs,
			// 													   .InJacks = EnOscInfo::InJacks,
			// 													   .OutJacks = EnOscInfo::OutJacks,
			// 													   .Switches = EnOscInfo::Switches,
			// 													   .Leds = EnOscInfo::Leds,
			// 												   });
			CHECK_FALSE(already_exists);

			auto info = ModuleFactory::getModuleInfo("EnOsc2");
			CHECK(info.width_hp == 16);
			CHECK(info.svg_filename == "res/EnOsc-artwork.svg");
			CHECK(info.Knobs[0].short_name == "Spread");
			CHECK(info.Knobs[1].short_name == "Scale");
			CHECK(info.Knobs[2].short_name == "Pitch");
			CHECK(info.Knobs[2].knob_style == KnobDef::Medium);
			CHECK(info.Knobs[2].default_val == 0.5f);
			CHECK(info.Knobs[7].id == 7);
			CHECK(info.Knobs.size() == 9);

			CHECK(info.InJacks.size() == 10);
			CHECK(info.InJacks[2].short_name == "Cross FM");
			CHECK(info.InJacks[2].x_mm == EnOscInfo::px_to_mm<72>(133.86f));

			CHECK(info.OutJacks.size() == 2);
			CHECK(info.OutJacks[0].short_name == "Out A");
			CHECK(info.OutJacks[0].signal_type == OutJackDef::Analog);
			CHECK(info.OutJacks[0].id == EnOscInfo::OutputOut_A);
			CHECK(info.OutJacks[0].y_mm == EnOscInfo::px_to_mm<72>(262.78f));

			// Switches
			// Leds
			//
			SUBCASE("Test unregistered slug") {
				auto slug = ModuleFactory::getModuleSlug("NotFound");
				CHECK(slug == "????");

				auto info = ModuleFactory::getModuleInfo("NotFound");
				CHECK(info.width_hp == 0);
				CHECK(info.svg_filename.empty() == true);
				CHECK(info.Knobs.size() == 0);
				CHECK(info.InJacks.size() == 0);
				CHECK(info.OutJacks.size() == 0);
				CHECK(info.Switches.size() == 0);
				CHECK(info.Leds.size() == 0);
			}
		}
	}
}
