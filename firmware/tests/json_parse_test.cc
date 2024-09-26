#include "doctest.h"
#include "src/dynload/json_parse.hh"

TEST_CASE("Check hack parser") {

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
	auto json = MetaModule::Plugin::parse_json(file_data);
	CHECK(json.slug == "ThisSlug");
	CHECK(json.name == "PluginName");
}

TEST_CASE("Check spaces, tabs") {

	std::string filedata = R"({
  	"name":   "PluginName" ,
  "slug"  : 		 "ThisSlug",
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
	auto json = MetaModule::Plugin::parse_json(file_data);
	CHECK(json.slug == "ThisSlug");
	CHECK(json.name == "PluginName");
}
