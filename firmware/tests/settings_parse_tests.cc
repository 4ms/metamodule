#include "doctest.h"
#include "user_settings/settings_parse.hh"
#include "user_settings/settings_serialize.hh"
#include <string>

TEST_CASE("Parse settings file") {

	// clang-format off
	std::string yaml = R"(Settings:
  low_sel: 1
  mid_sel: 2
  high_sel: 3
)";
	// clang-format on

	MetaModule::UserSettings settings;
	auto ok = MetaModule::Settings::parse(yaml, &settings);
	CHECK(ok);

	CHECK(settings.low_sel == 1);
	CHECK(settings.mid_sel == 2);
	CHECK(settings.high_sel == 3);
}

TEST_CASE("Get default settings if file is missing fields") {
	std::string yaml;
	bool should_parse = true;

	SUBCASE("empty file") {
		yaml = "";
		should_parse = false;
	}

	SUBCASE("Just Settings:") {
		yaml = R"(Settings:
)";
	}

	SUBCASE("Just headers:") {
		yaml = R"(Settings:
  low_sel: 0
)";
	}

	SUBCASE("Some values:") {
		yaml = R"(Settings:
  mid_sel: 0
)";
	}

	SUBCASE("Malformed values:") {
		yaml = R"(Settings:
  high_sel: 0
)";
	}

	MetaModule::UserSettings settings;
	auto ok = MetaModule::Settings::parse(yaml, &settings);
	CHECK(ok == should_parse);

	CHECK(settings.low_sel == 0);
	CHECK(settings.mid_sel == 0);
	CHECK(settings.high_sel == 0);
}

TEST_CASE("Serialize settings") {

	MetaModule::UserSettings settings;

	settings.low_sel = 3;
	settings.mid_sel = 2;
	settings.high_sel = 1;

	// clang format-off
	std::string expected = R"(Settings:
  low_sel: 3
  mid_sel: 2
  high_sel: 1
)";
	// clang format-on

	std::string parsed;
	parsed.resize(2048);
	auto bytes_size = MetaModule::Settings::serialize(settings, {parsed.data(), parsed.size()});
	parsed.resize(bytes_size);

	CHECK(parsed == expected);
}
