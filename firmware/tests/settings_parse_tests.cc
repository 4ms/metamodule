#include "doctest.h"
#include "user_settings/settings_parse.hh"
#include "user_settings/settings_serialize.hh"
#include "user_settings/view_settings.hh"
#include <string>

TEST_CASE("Parse settings file") {

	// clang-format off
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

  audio:
    sample_rate: 96000
    block_size: 128
    max_overrun_retries: 4

  plugin_autoload:
    - Plugin One
    - Plugin Two

  last_patch_opened: '/somedir/SomePatch.yml'
  last_patch_vol: 1

  screensaver:
    index: 3
    knobs_can_wake: 1

  catchup:
    mode: ResumeOnEqual
    allow_jump_outofrange: 0

  filesystem:
    auto_reload_patch_file: false
    max_open_patches: 7

  midi:
    midi_feedback: 1
    midi_quick_mapping: false
)";
	// clang-format on

	MetaModule::UserSettings settings;
	auto ok = MetaModule::Settings::parse(yaml, &settings);
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

	CHECK(settings.audio.sample_rate == 96000);
	CHECK(settings.audio.block_size == 128);
	CHECK(settings.audio.max_overrun_retries == 4);

	CHECK(settings.plugin_preload.slug.at(0) == "Plugin One");
	CHECK(settings.plugin_preload.slug.at(1) == "Plugin Two");

	CHECK(settings.last_patch_opened == "/somedir/SomePatch.yml");
	CHECK(settings.last_patch_vol == MetaModule::Volume::SDCard);

	CHECK(settings.screensaver.timeout_ms == 3);
	CHECK(settings.screensaver.knobs_can_wake == true);

	CHECK(settings.catchup.mode == MetaModule::CatchupParam::Mode::ResumeOnEqual);
	CHECK(settings.catchup.allow_jump_outofrange == false);

	CHECK(settings.filesystem.auto_reload_patch_file == false);
	CHECK(settings.filesystem.max_open_patches == 7);

	CHECK(settings.midi.midi_feedback == MetaModule::MidiSettings::MidiFeedback::Enabled);
	CHECK(settings.midi.midi_quick_mapping == false); // explicitly set to false in YAML
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
	SUBCASE("Bad audio sample rate:") {
		yaml = R"(Settings:
  audio:
    sample_rate: 44100
)";
	}
	SUBCASE("Bad audio block size:") {
		yaml = R"(Settings:
  audio:
    block_size: 6
)";
	}
	SUBCASE("Empty Autoload:") {
		yaml = R"(Settings:
  plugin_autoload: []
)";
	}
	SUBCASE("Bad screensaver settings:") {
		yaml = R"(Settings:
  screensaver:
)";
	}
	SUBCASE("Bad audio overrun settings:") {
		yaml = R"(Settings:
  max_overrun_retries: 94
)";
	}
	SUBCASE("Bad catchup settings:") {
		yaml = R"(Settings:
  catchup:
    mode: INvaliDmodE
)";
	}
	SUBCASE("Bad catchup settings:") {
		yaml = R"(Settings:
  catchup:
    allow_jump_outofrange: 2
)";
	}
	SUBCASE("Bad filesystem settings:") {
		yaml = R"(Settings:
  filesystem:
    max_open_patches: INvalID
)";
	}

	MetaModule::UserSettings settings;
	auto ok = MetaModule::Settings::parse(yaml, &settings);
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

	CHECK(settings.audio.sample_rate == 48000);
	CHECK(settings.audio.block_size == 64);
	CHECK(settings.audio.max_overrun_retries == 2);

	CHECK(settings.plugin_preload.slug.size() == 0);

	CHECK(settings.last_patch_opened == "");
	CHECK(settings.last_patch_vol == MetaModule::Volume::NorFlash);

	CHECK(settings.screensaver.timeout_ms == MetaModule::ScreensaverSettings::defaultTimeout);
	CHECK(settings.screensaver.knobs_can_wake == true);

	CHECK(settings.catchup.mode == MetaModule::CatchupParam::Mode::ResumeOnMotion);
	CHECK(settings.catchup.allow_jump_outofrange == true);

	CHECK(settings.filesystem.auto_reload_patch_file == true);
	CHECK(settings.filesystem.max_open_patches == 15);

	CHECK(settings.midi.midi_feedback == MetaModule::MidiSettings::MidiFeedback::Enabled);
	CHECK(settings.midi.midi_quick_mapping == true); // defaults to true when not specified
}

TEST_CASE("Serialize settings") {

	MetaModule::UserSettings settings;

	using enum MetaModule::MapRingStyle::Mode;

	settings.patch_view.map_ring_flash_active = true;
	settings.patch_view.scroll_to_active_param = false;
	settings.patch_view.param_style.mode = CurModuleIfPlaying;
	settings.patch_view.param_style.opa = 129;
	settings.patch_view.paneljack_style.mode = HideAlways;
	settings.patch_view.paneljack_style.opa = 192;
	settings.patch_view.cable_style.mode = ShowAll;
	settings.patch_view.cable_style.opa = 100;
	settings.patch_view.view_height_px = 180;

	settings.module_view.map_ring_flash_active = false;
	settings.module_view.scroll_to_active_param = true;
	settings.module_view.param_style.mode = CurModule;
	settings.module_view.param_style.opa = 128;
	settings.module_view.paneljack_style.mode = ShowAllIfPlaying;
	settings.module_view.paneljack_style.opa = 92;
	settings.module_view.cable_style.mode = HideAlways;
	settings.module_view.cable_style.opa = 0;
	settings.module_view.view_height_px = 240;

	settings.audio.sample_rate = 24000;
	settings.audio.block_size = 512;
	settings.audio.max_overrun_retries = 4;

	settings.plugin_preload.slug.emplace_back("Plugin One");
	settings.plugin_preload.slug.emplace_back("Plugin Two");

	settings.last_patch_vol = MetaModule::Volume::SDCard;
	settings.last_patch_opened = "SomePatch.yml";

	settings.screensaver.knobs_can_wake = false;
	settings.screensaver.timeout_ms = 2;

	settings.catchup.mode = MetaModule::CatchupParam::Mode::LinearFade;
	settings.catchup.allow_jump_outofrange = false;

	settings.filesystem.max_open_patches = 8;
	settings.filesystem.auto_reload_patch_file = false;

	settings.midi.midi_feedback = MetaModule::MidiSettings::MidiFeedback::Disabled;

	// clang format-off
	std::string expected = R"(Settings:
  patch_view:
    map_ring_flash_active: 1
    scroll_to_active_param: 0
    view_height_px: 180
    param_style:
      mode: CurModuleIfPlaying
      opa: 129
    paneljack_style:
      mode: HideAlways
      opa: 192
    cable_style:
      mode: ShowAll
      opa: 100
    show_graphic_screens: 1
    graphic_screen_throttle: 1
  module_view:
    map_ring_flash_active: 0
    scroll_to_active_param: 1
    view_height_px: 240
    param_style:
      mode: CurModule
      opa: 128
    paneljack_style:
      mode: ShowAllIfPlaying
      opa: 92
    cable_style:
      mode: HideAlways
      opa: 0
    show_graphic_screens: 1
    graphic_screen_throttle: 1
  audio:
    sample_rate: 24000
    block_size: 512
    max_overrun_retries: 4
  plugin_autoload:
    - Plugin One
    - Plugin Two
  last_patch_opened: SomePatch.yml
  last_patch_vol: 1
  screensaver:
    index: 2
    knobs_can_wake: 0
  catchup:
    mode: LinearFade
    allow_jump_outofrange: 0
  filesystem:
    auto_reload_patch_file: 0
    max_open_patches: 8
  midi:
    midi_feedback: 0
    midi_quick_mapping: 1
)";
	// clang format-on

	std::string parsed;
	parsed.resize(2048);
	auto bytes_size = MetaModule::Settings::serialize(settings, {parsed.data(), parsed.size()});
	parsed.resize(bytes_size);

	CHECK(parsed == expected);
}
