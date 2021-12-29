#include "doctest.h"
#include "info/EnOsc_info.hh"
#include "moduleFactory.hh"
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

	static std::unique_ptr<CoreProcessor> create() {
		return std::make_unique<TestCoreMod>();
	}
};

static constexpr std::string_view abcabc_slug{"abcabc"};
constexpr ModuleInfoView abcabcInfo{
	.width_hp = 40,
	.svg_filename = "abcabc.svg",
	.module_name = "abcabc module",
};

class AutoInit {
public:
	static inline bool g_abcabc_already_exists =
		ModuleFactory::registerModuleType(abcabc_slug, TestCoreMod::create, abcabcInfo);
};

TEST_CASE("Static objects register automatically") {
	constexpr char typeID[20] = "abcabc";
	CHECK(ModuleFactory::isValidSlug(abcabc_slug));
	auto cf1 = ModuleFactory::create(abcabc_slug);
	CHECK(cf1 != nullptr);

	CHECK(ModuleFactory::isValidSlug(typeID));
	auto cf = ModuleFactory::create(typeID);
	CHECK(cf != nullptr);

	auto nm = ModuleFactory::getModuleTypeName(typeID);
	CHECK(nm == "abcabc module");

	auto info = ModuleFactory::getModuleInfo(typeID);
	CHECK(info.width_hp == 40);
	CHECK(info.module_name == "abcabc module");

	CHECK_FALSE(AutoInit::g_abcabc_already_exists);
}

constexpr ModuleInfoView ABCInfo{
	.width_hp = 40,
	.svg_filename = "abc.svg",
	.module_name = "ABC module",
};

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

TEST_CASE("Register ModuleTypes with an object constructed from ModuleInfoView") {

	bool already_exists = ModuleFactory::registerModuleType("ABC", TestCoreMod::create, ABCInfo);
	CHECK_FALSE(already_exists);

	CHECK(ModuleFactory::isValidSlug("ABC"));
	CHECK_FALSE(ModuleFactory::isValidSlug("DEF"));

	constexpr char typeID[20] = "ABC";
	CHECK(ModuleFactory::isValidSlug(typeID));

	auto nm = ModuleFactory::getModuleTypeName(typeID);
	CHECK(nm == "ABC module");

	auto info = ModuleFactory::getModuleInfo(typeID);
	CHECK(info.width_hp == 40);
	CHECK(info.module_name == "ABC module");

	auto cf = ModuleFactory::create(typeID);
	CHECK(cf != nullptr);

	SUBCASE("Test if Knob info get stored and retreived OK") {
		constexpr ModuleInfoView testinfo{
			.width_hp = 4,
			.svg_filename = "",
			.module_name = "def info",
			.Knobs = TestInfo::Knobs,
		};

		already_exists = ModuleFactory::registerModuleType("DEF", TestCoreMod::create, testinfo);
		CHECK_FALSE(already_exists);

		CHECK(ModuleFactory::getModuleInfo("DEF").width_hp == 4);
		auto knobs = ModuleFactory::getModuleInfo("DEF").Knobs;
		CHECK(knobs[0].short_name == "Spread");
		CHECK(knobs[1].short_name == "Scale");
		CHECK(knobs.size() == 2);

		SUBCASE("Test actual EnOscInfo data") {
			already_exists =
				ModuleFactory::registerModuleType("EnOsc2", TestCoreMod::create, ModuleInfoView::makeView<EnOscInfo>());
			CHECK_FALSE(already_exists);

			auto info = ModuleFactory::getModuleInfo("EnOsc2");
			CHECK(info.width_hp == 16);
			CHECK(info.svg_filename == "res/modules/EnOsc-artwork.svg");
			CHECK(info.Knobs[0].short_name == "Scale");
			CHECK(info.Knobs[1].short_name == "Spread");
			CHECK(info.Knobs[2].short_name == "Pitch");
			CHECK(info.Knobs[2].knob_style == KnobDef::Medium);
			CHECK(info.Knobs[2].default_val == 0.5f);
			CHECK(info.Knobs[7].id == 7);
			CHECK(info.Knobs.size() == 9);

			CHECK(info.InJacks.size() == 10);
			CHECK(info.InJacks[2].short_name == "Scale");
			CHECK(info.InJacks[2].x_mm == EnOscInfo::px_to_mm<72>(59.0f));

			CHECK(info.OutJacks.size() == 2);
			CHECK(info.OutJacks[0].short_name == "Out A");
			CHECK(info.OutJacks[0].signal_type == OutJackDef::Analog);
			CHECK(info.OutJacks[0].id == EnOscInfo::OutputOut_A);
			CHECK(info.OutJacks[0].y_mm == EnOscInfo::px_to_mm<72>(262.78f));

			// Switches
			// Leds

			SUBCASE("Test unregistered slug") {
				CHECK_FALSE(ModuleFactory::isValidSlug("NotFound"));

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

TEST_CASE("ModuleInfoView::makeView<T>() matches T:: fields") {

	auto v = ModuleInfoView::makeView<EnOscInfo>();
	CHECK(v.width_hp == EnOscInfo::width_hp);
	CHECK(v.svg_filename == EnOscInfo::svg_filename);
	CHECK(v.Knobs.size() == EnOscInfo::Knobs.size());
	// 													   .Knobs = EnOscInfo::Knobs,
	// 													   .InJacks = EnOscInfo::InJacks,
	// 													   .OutJacks = EnOscInfo::OutJacks,
	// 													   .Switches = EnOscInfo::Switches,
	// 													   .Leds = EnOscInfo::Leds,
}

etl::string_view get_str() {
	return "module4";
}
TEST_CASE("ETL::map tests") {
	SUBCASE("string -> string") {
		etl::unordered_map<etl::string<3>, std::string, 4> m;
		m["ABC"] = "DEF";
		CHECK(m["ABC"] == "DEF");
	}

	SUBCASE("string -> struct") {
		etl::unordered_map<etl::string<10>, ModuleInfoView, 4> m;
		ModuleInfoView info{.width_hp = 4};
		m["module4"] = info;
		CHECK(m["module4"].width_hp == 4);
	}

	SUBCASE("string_view -> struct") {
		using KeyT = etl::string_view;
		etl::unordered_map<KeyT, ModuleInfoView, 4> m;
		ModuleInfoView info{.width_hp = 4};
		KeyT slug{"module4"};
		m[slug] = info;
		CHECK(m[slug].width_hp == 4);
		CHECK(m["module4"].width_hp == 4);
		CHECK(m[get_str()].width_hp == 4);
		KeyT otherslug = slug;
		CHECK(m[otherslug].width_hp == 4);

		//Static string converts
		StaticString<31> ss{"module4"};
		CHECK(m[ss.c_str()].width_hp == 4);
	}
}
