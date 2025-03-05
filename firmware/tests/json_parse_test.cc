#include "doctest.h"
#include "src/dynload/json_parse.hh"

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
	CHECK(metadata.display_name == "PluginName");
}
