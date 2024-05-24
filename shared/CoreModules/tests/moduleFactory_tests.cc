#include "CoreModules/4ms/info/EnOsc_info.hh"
#include "CoreModules/moduleFactory.hh"
#include "doctest.h"
#include <cstdint>
#include <span>
#include <string_view>

/////////// Sample module class:

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

////////////// Sample module construction
static constexpr std::string_view abcabc_slug{"abcabc"};
constexpr MetaModule::ModuleInfoView abcabcInfo{
	.description = "abcabc module",
	.width_hp = 40,
};

using namespace MetaModule;

class AutoInit {

public:
	static inline bool g_abcabc_registered_ok =
		ModuleFactory::registerModuleType(abcabc_slug, TestCoreMod::create, abcabcInfo, "faceplate.png");

	static inline bool g_brandedmod_registered_ok =
		ModuleFactory::registerModuleType("BrandX", "moduleY", TestCoreMod::create, abcabcInfo, "faceplate.png");
};

////////////// Tests

TEST_CASE("Static objects register automatically") {
	// defaults to 4ms for brand:
	CHECK(ModuleFactory::isValidSlug("4msCompany:abcabc"));
	auto cf1 = ModuleFactory::create("4msCompany:abcabc");
	CHECK(cf1 != nullptr);

	// check explicit brand
	CHECK(ModuleFactory::isValidSlug("BrandX:moduleY"));

	constexpr char typeID[20] = "abcabc";
	CHECK(ModuleFactory::isValidSlug(typeID));
	auto cf = ModuleFactory::create(typeID);
	CHECK(cf != nullptr);

	auto info = ModuleFactory::getModuleInfo(typeID);
	CHECK(info.width_hp == 40);
	CHECK(info.description == "abcabc module");

	CHECK(AutoInit::g_abcabc_registered_ok);
}

constexpr MetaModule::ModuleInfoView ABCInfo{
	.description = "ABC module",
	.width_hp = 40,
};

struct TestInfo : MetaModule::ModuleInfoBase {
	static constexpr std::string_view slug{"HIJ"};
	static constexpr uint32_t width_hp = 2;
	static constexpr std::array<MetaModule::Element, 2> Elements{{
		MetaModule::Knob9mm{{to_mm<72>(114.85f), to_mm<72>(61.59f), MetaModule::Coords::Center, "Spread", "Spread"}},
		MetaModule::Davies1900hBlackKnob{
			{to_mm<72>(53.68f), to_mm<72>(78.08f), MetaModule::Coords::Center, "Scale", "Scale"}},
	}};
};

TEST_CASE("Register ModuleTypes with an object constructed from ModuleInfoView") {

	bool registered_ok = ModuleFactory::registerModuleType("ABC", TestCoreMod::create, ABCInfo, "abc.png");
	CHECK(registered_ok);

	CHECK(ModuleFactory::isValidSlug("ABC"));
	CHECK_FALSE(ModuleFactory::isValidSlug("DEF"));

	constexpr char typeID[20] = "ABC";
	CHECK(ModuleFactory::isValidSlug(typeID));

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

		registered_ok = ModuleFactory::registerModuleType("DEF", TestCoreMod::create, testinfo, "def.png");
		CHECK(registered_ok);

		CHECK(ModuleFactory::getModuleInfo("DEF").width_hp == 4);
		auto elements = ModuleFactory::getModuleInfo("DEF").elements;

		auto name0 = std::visit([](auto el) { return el.short_name; }, elements[0]);
		CHECK(name0 == "Spread");

		auto name1 = std::visit([](auto el) { return el.short_name; }, elements[1]);
		CHECK(name1 == "Scale");

		CHECK(elements.size() == 2);
	}
}

TEST_CASE("ModuleInfoView::makeView<T>() matches T:: fields") {

	auto v = MetaModule::ModuleInfoView::makeView<MetaModule::EnOscInfo>();
	CHECK(v.width_hp == MetaModule::EnOscInfo::width_hp);
	CHECK(v.elements.size() == MetaModule::EnOscInfo::Elements.size());
}
