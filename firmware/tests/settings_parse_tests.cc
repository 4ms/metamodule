#include "doctest.h"
#include "fs/settings_parse.hh"
#include "gui/pages/view_settings.hh"

TEST_CASE("Parse settings file") {

	// clang format-off
	std::string yaml = R"(Settings:
  patch_view:
    map_ring_flash_active: true
    scroll_to_active_param: false
    param_style: 
      mode: CurModuleIfPlaying
      opa: 129
    paneljack_style:
      mode: HideAlways
      opa: 192
    cable_style: 
      mode: ShowAll
      opa: 100
    view_height_px: 180

  module_view:
    map_ring_flash_active: false
    scroll_to_active_param: true
    param_style: 
      mode: CurModule
      opa: 128
    paneljack_style:
      mode: ShowAllIfPlaying
      opa: 92
    cable_style: 
      mode: HideAlways
      opa: 0
    view_height_px: 240

)";
	// clang format-on

	MetaModule::ViewSettings settings;
	auto ok = MetaModule::Settings::parse_settings(yaml, &settings);
	CHECK(ok);

	using enum MetaModule::MapRingStyle::Mode;

	CHECK(settings.patch_view.map_ring_flash_active == true);
	CHECK(settings.patch_view.scroll_to_active_param == false);
	CHECK(settings.patch_view.param_style.mode == CurModuleIfPlaying);
	CHECK(settings.patch_view.param_style.opa == 129);
	CHECK(settings.patch_view.paneljack_style.mode == HideAlways);
	CHECK(settings.patch_view.paneljack_style.opa == 192);
	CHECK(settings.patch_view.cable_style.mode == ShowAll);
	CHECK(settings.patch_view.cable_style.opa == 100);
	CHECK(settings.patch_view.view_height_px == 180);

	CHECK(settings.module_view.map_ring_flash_active == false);
	CHECK(settings.module_view.scroll_to_active_param == true);
	CHECK(settings.module_view.param_style.mode == CurModule);
	CHECK(settings.module_view.param_style.opa == 128);
	CHECK(settings.module_view.paneljack_style.mode == ShowAllIfPlaying);
	CHECK(settings.module_view.paneljack_style.opa == 92);
	CHECK(settings.module_view.cable_style.mode == HideAlways);
	CHECK(settings.module_view.cable_style.opa == 0);
	CHECK(settings.module_view.view_height_px == 240);
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
  patch_view:
  module_view:
)";
	}

	SUBCASE("Some values:") {
		yaml = R"(Settings:
  patch_view:
    view_height_px: 180
  module_view:
)";
	}

	SUBCASE("Malformed values:") {
		yaml = R"(Settings:
  patch_view:
    param_style: 
      opa: abc
)";
	}

	MetaModule::ViewSettings settings;
	auto ok = MetaModule::Settings::parse_settings(yaml, &settings);
	CHECK(ok == should_parse);

	using enum MetaModule::MapRingStyle::Mode;

	MetaModule::ModuleDisplaySettings df{};

	CHECK(settings.patch_view.map_ring_flash_active == df.map_ring_flash_active);
	CHECK(settings.patch_view.scroll_to_active_param == df.scroll_to_active_param);
	CHECK(settings.patch_view.param_style.mode == df.param_style.mode);
	CHECK(settings.patch_view.param_style.opa == df.param_style.opa);
	CHECK(settings.patch_view.paneljack_style.mode == df.paneljack_style.mode);
	CHECK(settings.patch_view.paneljack_style.opa == df.paneljack_style.opa);
	CHECK(settings.patch_view.cable_style.mode == df.cable_style.mode);
	CHECK(settings.patch_view.cable_style.opa == df.cable_style.opa);
	CHECK(settings.patch_view.view_height_px == df.view_height_px);

	CHECK(settings.module_view.map_ring_flash_active == df.map_ring_flash_active);
	CHECK(settings.module_view.scroll_to_active_param == df.scroll_to_active_param);
	CHECK(settings.module_view.param_style.mode == df.param_style.mode);
	CHECK(settings.module_view.param_style.opa == df.param_style.opa);
	CHECK(settings.module_view.paneljack_style.mode == df.paneljack_style.mode);
	CHECK(settings.module_view.paneljack_style.opa == df.paneljack_style.opa);
	CHECK(settings.module_view.cable_style.mode == df.cable_style.mode);
	CHECK(settings.module_view.cable_style.opa == df.cable_style.opa);
	CHECK(settings.module_view.view_height_px == df.view_height_px);
}
