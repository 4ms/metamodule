#include "doctest.h"
#include "dynload/json_parse.hh"

TEST_CASE("basic parsing") {
	// clang-format off
	std::string yaml = R"({
  "MetaModuleBrandName": "4ms",
  "MetaModuleBrandAliases": ["4mscompany", "4ms-company", "4MS"],
  "MetaModulePluginMaintainer": "4ms Company",
  "MetaModulePluginMaintainerEmail": "",
  "MetaModulePluginMaintainerUrl": "https://4mscompany.com",
  "MetaModuleDescription": "",
  "MetaModuleIncludedModules": [
  {
    "slug": "Atvert2",
    "displayName": "Atvert2"
  },
  {
    "slug": "BPF",
    "displayName": "BPF"
  }
  ]
}
)";
	// clang-format on

	MetaModule::Plugin::Metadata metadata;

	CHECK(MetaModule::Plugin::parse_mm_json(yaml, &metadata));
	CHECK(metadata.display_name == "4ms");
	CHECK(metadata.brand_aliases.size() == 3);
	CHECK(metadata.brand_aliases[0] == "4mscompany");
	CHECK(metadata.brand_aliases[1] == "4ms-company");
	CHECK(metadata.brand_aliases[2] == "4MS");
}
