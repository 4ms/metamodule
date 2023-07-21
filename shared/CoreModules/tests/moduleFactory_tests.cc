#include "4ms/info/SMR_info.hh"
#include "CoreModules/moduleFactory.hh"
#include "doctest.h"
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
constexpr MetaModule::ModuleInfoView abcabcInfo{
	.description = "abcabc module",
	.width_hp = 40,
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
	CHECK(info.description == "abcabc module");

	CHECK_FALSE(AutoInit::g_abcabc_already_exists);
}

constexpr MetaModule::ModuleInfoView ABCInfo{
	.description = "ABC module",
	.width_hp = 40,
};

struct TestInfo : MetaModule::ModuleInfoBase {
	static constexpr std::string_view slug{"HIJ"};
	static constexpr uint32_t width_hp = 2;
	static constexpr std::array<MetaModule::Element, 2> Elements{{
		MetaModule::Knob9mm{to_mm<72>(114.85f), to_mm<72>(61.59f), "Spread", "Spread", 0, 0, 1, 0.5f},
		MetaModule::Davies1900hBlackKnob{to_mm<72>(53.68f), to_mm<72>(78.08f), "Scale", "Scale", 0, 0, 1, 0.0f},
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
	CHECK(info.description == "ABC module");

	auto cf = ModuleFactory::create(typeID);
	CHECK(cf != nullptr);

	SUBCASE("Test if Elements info gets stored and retreived OK") {
		constexpr MetaModule::ModuleInfoView testinfo{
			.description = "def info",
			.width_hp = 4,
			.elements = TestInfo::Elements,
		};

		already_exists = ModuleFactory::registerModuleType("DEF", TestCoreMod::create, testinfo);
		CHECK_FALSE(already_exists);

		CHECK(ModuleFactory::getModuleInfo("DEF").width_hp == 4);
		auto elements = ModuleFactory::getModuleInfo("DEF").elements;

		auto name0 = std::visit([](auto el) { return el.short_name; }, elements[0]);
		CHECK(name0 == "Spread");

		auto name1 = std::visit([](auto el) { return el.short_name; }, elements[1]);
		CHECK(name1 == "Scale");

		CHECK(elements.size() == 2);

		// FIXME: update once we convert EnOsc to new format
		// SUBCASE("Test actual EnOscInfo data") {
		// 	already_exists =
		// 		ModuleFactory::registerModuleType("EnOsc2", TestCoreMod::create, ModuleInfoView::makeView<EnOscInfo>());
		// 	CHECK_FALSE(already_exists);

		// 	auto info = ModuleFactory::getModuleInfo("EnOsc2");
		// 	CHECK(info.width_hp == 16);
		// 	CHECK(info.Knobs[0].short_name == "Scale");
		// 	CHECK(info.Knobs[1].short_name == "Spread");
		// 	CHECK(info.Knobs[2].short_name == "Pitch");
		// 	CHECK(info.Knobs[2].knob_style == KnobDef::Medium);
		// 	CHECK(info.Knobs[4].default_val == 0.5f);
		// 	CHECK(info.Knobs[7].id == 7);
		// 	CHECK(info.Knobs.size() == 9);

		// 	CHECK(info.InJacks.size() == 10);
		// 	CHECK(info.InJacks[2].short_name == "Spread Jack");
		// 	CHECK(info.InJacks[2].x_mm == EnOscInfo::px_to_mm<72>(96.88f));

		// 	CHECK(info.OutJacks.size() == 2);
		// 	CHECK(info.OutJacks[0].short_name == "Out A");
		// 	CHECK(info.OutJacks[0].signal_type == OutJackDef::Analog);
		// 	CHECK(info.OutJacks[0].id == EnOscInfo::OutputOut_A);
		// 	CHECK(info.OutJacks[0].y_mm == EnOscInfo::px_to_mm<72>(262.78f));

		// 	// Switches
		// 	// Leds

		// 	SUBCASE("Test unregistered slug") {
		// 		CHECK_FALSE(ModuleFactory::isValidSlug("NotFound"));

		// 		auto info = ModuleFactory::getModuleInfo("NotFound");
		// 		CHECK(info.width_hp == 0);
		// 		CHECK(info.Knobs.size() == 0);
		// 		CHECK(info.InJacks.size() == 0);
		// 		CHECK(info.OutJacks.size() == 0);
		// 		CHECK(info.Switches.size() == 0);
		// 		CHECK(info.Leds.size() == 0);
		// 	}
		// }
	}
}

TEST_CASE("ModuleInfoView::makeView<T>() matches T:: fields") {

	auto v = MetaModule::ModuleInfoView::makeView<MetaModule::SMRInfo>();
	CHECK(v.width_hp == MetaModule::SMRInfo::width_hp);
	CHECK(v.elements.size() == MetaModule::SMRInfo::Elements.size());
}
