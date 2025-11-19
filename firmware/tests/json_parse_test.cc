#include "doctest.h"
#include "src/dynload/json_parse.hh"
#include <string>
#include <vector>

TEST_CASE("Brand overrides name") {

	std::string filedata = R"({
  "slug": "ThisSlug",
  "name": "PluginName",
  "version": "1.0.0",
  "license": "GPL-3.0-or-later",
  "brand": "4msCompany",
  "author": "Dan Green",
  "modules": [
    {
      "slug": "SimpleGain",
      "name": "SimpleGain",
      "description": "Example plugin",
      "tags": [
      ]
    }
  ]
}
)";

	auto file_data = std::span<char>{filedata.data(), filedata.length()};
	MetaModule::Plugin::Metadata metadata;
	CHECK(MetaModule::Plugin::parse_json(file_data, &metadata));
	CHECK(metadata.brand_slug == "ThisSlug");
	// brand overrides name
	CHECK(metadata.display_name == "4msCompany");
}

TEST_CASE("No brand, use name") {
	std::string filedata = R"({
  "name":   "PluginName" ,
  "slug"  :   "ThisSlug",
  "version": "1.0.0",
  "license": "GPL-3.0-or-later",
  "author": "Dan Green",
  "modules": [
    {
      "slug": "SimpleGain",
      "name": "SimpleGain",
      "description": "Example plugin",
      "tags": [ ]
    }
  ]
}
)";

	auto file_data = std::span<char>{filedata.data(), filedata.length()};
	MetaModule::Plugin::Metadata metadata;
	CHECK(MetaModule::Plugin::parse_json(file_data, &metadata));
	CHECK(metadata.brand_slug == "ThisSlug");
	CHECK(metadata.display_name == "PluginName");
}

TEST_CASE("Parse module descriptions and tags from plugin.json") {
	std::string filedata = R"({
  "slug": "BrandX",
  "name": "Brand X",
  "version": "1.2.3",
  "author": "Author",
  "modules": [
    {
      "slug": "M1",
      "name": "Module One",
      "description": "A super module",
      "tags": [ "Oscillator", "Utility", "4ms" ]
    },
    {
      "slug": "M2",
      "name": "Module Two",
      "description": "",
      "tags": []
    }
  ]
}
)";

	auto file_data = std::span<char>{filedata.data(), filedata.length()};
	MetaModule::Plugin::Metadata metadata;
	CHECK(MetaModule::Plugin::parse_json(file_data, &metadata));

	CHECK(metadata.module_extras.size() == 2);

	// find M1 and validate
	bool found_m1 = false;
	for (auto const &m : metadata.module_extras) {
		if (m.slug == "M1") {
			found_m1 = true;
			CHECK(m.description == std::string("A super module"));
			CHECK(m.tags.size() == 3);
			CHECK(m.tags[0] == std::string("Oscillator"));
			CHECK(m.tags[1] == std::string("Utility"));
			CHECK(m.tags[2] == std::string("4ms"));
		}
	}
	CHECK(found_m1);

	// find M2 and validate empty description/tags accepted
	bool found_m2 = false;
	for (auto const &m : metadata.module_extras) {
		if (m.slug == "M2") {
			found_m2 = true;
			CHECK(m.description == std::string(""));
			CHECK(m.tags.size() == 0);
		}
	}
	CHECK(found_m2);
}
