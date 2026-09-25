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

TEST_CASE("element names") {
	// clang-format off
	std::string yaml = R"({
  "MetaModuleBrandName": "4ms",
  "MetaModuleIncludedModules": [
  {
    "slug": "Mod",
    "groups": {
      "Red": ["Red Size", "Red Speed"]
    },
    "names": {
      "Red Speed": "Rate",
      "param:3": "Mix",
      "in:1": "",
      "Level CV In": "Lvl CV"
    }
  }
  ]
}
)";
	// clang-format on

	MetaModule::Plugin::Metadata metadata;
	CHECK(MetaModule::Plugin::parse_mm_json(yaml, &metadata));
	REQUIRE(metadata.module_display_names.size() == 1);

	auto const &module = metadata.module_display_names[0];
	REQUIRE(module.element_groups.size() == 1);
	CHECK(module.element_groups[0].members.size() == 2);

	// An empty name is dropped
	auto const &names = module.element_names;
	REQUIRE(names.size() == 3);

	CHECK(names[0].element.kind == MetaModule::ElementRef::Kind::Name);
	CHECK(names[0].element.name == "Red Speed");
	CHECK(names[0].name == "Rate");

	CHECK(names[1].element.kind == MetaModule::ElementRef::Kind::Param);
	CHECK(names[1].element.idx == 3);
	CHECK(names[1].name == "Mix");

	CHECK(names[2].element.name == "Level CV In");
	CHECK(names[2].name == "Lvl CV");
}
