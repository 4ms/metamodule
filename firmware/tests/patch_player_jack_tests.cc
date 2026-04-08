#include "doctest.h"
#include "patch-serial/yaml_to_patch.hh"
#include "patch_play/patch_player.hh"
#include "stubs/test_module.hh"

// Register TestModule so patches can use slug "TestModule"
namespace
{
constexpr MetaModule::ModuleInfoView TestModuleInfo{
	.description = "Test module",
	.width_hp = 8,
};
[[maybe_unused]] bool s_test_mono_registered =
	MetaModule::ModuleFactory::registerModuleType("TestModule", TestModule::create, TestModuleInfo, "");

auto *get_test_module(MetaModule::PatchPlayer &player, unsigned module_id) {
	return dynamic_cast<TestModule *>(player.modules[module_id].get());
}

constexpr MetaModule::ModuleInfoView TestPanelInfo{
	.description = "Test panel",
	.width_hp = 8,
};
[[maybe_unused]] bool s_test_panel_registered =
	MetaModule::ModuleFactory::registerModuleType("HubMedium", TestPanel::create, TestPanelInfo, "");

} // namespace

// ============================================================================
// Simple routing: 1 output -> 1 input (6 combinations)
// Output types: Module Out (M), Panel In (P), MIDI (D)
// Input types: Module In (m), Panel Out (p)
// ============================================================================

TEST_CASE("Simple: Module Out -> Module In") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: M_to_m
  module_slugs:
    0: HubMedium
    1: TestModule
    2: TestModule
  int_cables:
    - out:
        module_id: 1
        jack_id: 0
      ins:
        - module_id: 2
          jack_id: 0
  mapped_ins:
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 0
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);
	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	auto m1 = get_test_module(player, 1);
	auto m2 = get_test_module(player, 2);
	REQUIRE(m1);
	REQUIRE(m2);

	m1->set_input(0, 3.5f);
	player.update_patch();
	CHECK(m2->get_output(0) == doctest::Approx(3.5f));
}

TEST_CASE("Simple: Module Out -> Panel Out") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: M_to_p
  module_slugs:
    0: HubMedium
    1: TestModule
  int_cables:
  mapped_ins:
  mapped_outs:
    - panel_jack_id: 0
      out:
        module_id: 1
        jack_id: 0
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 0
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);
	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	auto m1 = get_test_module(player, 1);
	REQUIRE(m1);

	m1->set_input(0, 2.4f);
	player.update_patch();
	CHECK(player.get_panel_output(0) == doctest::Approx(2.4f));
}

TEST_CASE("Simple: Panel In -> Module In") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: P_to_m
  module_slugs:
    0: HubMedium
    1: TestModule
  int_cables:
  mapped_ins:
    - panel_jack_id: 0
      ins:
        - module_id: 1
          jack_id: 0
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 0
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);
	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	auto m1 = get_test_module(player, 1);
	REQUIRE(m1);

	player.set_panel_input(0, 4.0f);
	player.update_patch();
	CHECK(m1->get_output(0) == doctest::Approx(4.0f));
}

TEST_CASE("Simple: Panel In -> Panel Out (Hub passthrough)") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: P_to_p
  module_slugs:
    0: HubMedium
  int_cables:
  mapped_ins:
    - panel_jack_id: 0
      ins:
        - module_id: 0
          jack_id: 1
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 0
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);
	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	player.set_panel_input(0, 5.5f);
	CHECK(player.get_panel_output(1) == doctest::Approx(5.5f));
}

TEST_CASE("Simple: MIDI -> Module In") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: D_to_m
  module_slugs:
    0: HubMedium
    1: TestModule
  int_cables:
  mapped_ins:
    - panel_jack_id: 256
      ins:
        - module_id: 1
          jack_id: 0
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 1
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);
	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	auto m1 = get_test_module(player, 1);
	REQUIRE(m1);

	player.set_midi_note_pitch(0, 4.5f, 0);
	CHECK(m1->get_output(0) == doctest::Approx(4.5f));
}

TEST_CASE("Simple: MIDI -> Panel Out (via Hub)") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: D_to_p
  module_slugs:
    0: HubMedium
  int_cables:
  mapped_ins:
    - panel_jack_id: 256
      ins:
        - module_id: 0
          jack_id: 2
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 1
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);
	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	player.set_midi_note_pitch(0, 6.0f, 0);
	CHECK(player.get_panel_output(2) == doctest::Approx(6.0f));
}

// ============================================================================
// Splitting: 1 output -> 2 inputs (9 combinations)
// ============================================================================

TEST_CASE("Split: Module Out -> Module In + Module In") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: M_split_mm
  module_slugs:
    0: HubMedium
    1: TestModule
    2: TestModule
    3: TestModule
  int_cables:
    - out:
        module_id: 1
        jack_id: 0
      ins:
        - module_id: 2
          jack_id: 0
        - module_id: 3
          jack_id: 0
  mapped_ins:
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 0
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);
	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	auto m1 = get_test_module(player, 1);
	auto m2 = get_test_module(player, 2);
	auto m3 = get_test_module(player, 3);
	REQUIRE(m1);
	REQUIRE(m2);
	REQUIRE(m3);

	m1->set_input(0, 7.0f);
	player.update_patch();
	CHECK(m2->get_output(0) == doctest::Approx(7.0f));
	CHECK(m3->get_output(0) == doctest::Approx(7.0f));
}

TEST_CASE("Split: Module Out -> Module In + Panel Out") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: M_split_mp
  module_slugs:
    0: HubMedium
    1: TestModule
    2: TestModule
  int_cables:
    - out:
        module_id: 1
        jack_id: 0
      ins:
        - module_id: 2
          jack_id: 0
  mapped_ins:
  mapped_outs:
    - panel_jack_id: 0
      out:
        module_id: 1
        jack_id: 0
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 0
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);
	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	auto m1 = get_test_module(player, 1);
	auto m2 = get_test_module(player, 2);
	REQUIRE(m1);
	REQUIRE(m2);

	m1->set_input(0, 3.0f);
	player.update_patch();
	CHECK(m2->get_output(0) == doctest::Approx(3.0f));
	CHECK(player.get_panel_output(0) == doctest::Approx(3.0f));
}

TEST_CASE("Split: Module Out -> Panel Out + Panel Out") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: M_split_pp
  module_slugs:
    0: HubMedium
    1: TestModule
  int_cables:
  mapped_ins:
  mapped_outs:
    - panel_jack_id: 0
      out:
        module_id: 1
        jack_id: 0
    - panel_jack_id: 1
      out:
        module_id: 1
        jack_id: 0
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 0
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);
	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	auto m1 = get_test_module(player, 1);
	REQUIRE(m1);

	m1->set_input(0, 4.0f);
	player.update_patch();
	CHECK(player.get_panel_output(0) == doctest::Approx(4.0f));
	CHECK(player.get_panel_output(1) == doctest::Approx(4.0f));
}

TEST_CASE("Split: Panel In -> Module In + Module In") {
	// Panel In 0 -> module 1 jack 0 and module 2 jack 0
	// Because both destinations share a source (panel_in), this creates a summed input
	// through the Hub virtual cable mechanism. Each destination gets the panel input value.
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: P_split_mm
  module_slugs:
    0: HubMedium
    1: TestModule
    2: TestModule
  int_cables:
  mapped_ins:
    - panel_jack_id: 0
      ins:
        - module_id: 1
          jack_id: 0
        - module_id: 2
          jack_id: 0
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 0
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);
	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	auto m1 = get_test_module(player, 1);
	auto m2 = get_test_module(player, 2);
	REQUIRE(m1);
	REQUIRE(m2);

	player.set_panel_input(0, 2.0f);
	player.update_patch();
	CHECK(m1->get_output(0) == doctest::Approx(2.0f));
	CHECK(m2->get_output(0) == doctest::Approx(2.0f));
}

TEST_CASE("Split: Panel In -> Module In + Panel Out") {
	// Panel In 0 -> module 1 jack 0 AND Panel In 0 -> Panel Out 1 (via Hub)
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: P_split_mp
  module_slugs:
    0: HubMedium
    1: TestModule
  int_cables:
  mapped_ins:
    - panel_jack_id: 0
      ins:
        - module_id: 1
          jack_id: 0
        - module_id: 0
          jack_id: 1
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 0
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);
	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	auto m1 = get_test_module(player, 1);
	REQUIRE(m1);

	player.set_panel_input(0, 3.5f);
	player.update_patch();
	CHECK(m1->get_output(0) == doctest::Approx(3.5f));
	CHECK(player.get_panel_output(1) == doctest::Approx(3.5f));
}

TEST_CASE("Split: Panel In -> Panel Out + Panel Out") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: P_split_pp
  module_slugs:
    0: HubMedium
  int_cables:
  mapped_ins:
    - panel_jack_id: 0
      ins:
        - module_id: 0
          jack_id: 1
        - module_id: 0
          jack_id: 2
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 0
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);
	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	player.set_panel_input(0, 6.0f);
	CHECK(player.get_panel_output(1) == doctest::Approx(6.0f));
	CHECK(player.get_panel_output(2) == doctest::Approx(6.0f));
}

TEST_CASE("Split: MIDI -> Module In + Module In") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: D_split_mm
  module_slugs:
    0: HubMedium
    1: TestModule
    2: TestModule
  int_cables:
  mapped_ins:
    - panel_jack_id: 256
      ins:
        - module_id: 1
          jack_id: 0
        - module_id: 2
          jack_id: 0
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 1
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);
	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	auto m1 = get_test_module(player, 1);
	auto m2 = get_test_module(player, 2);
	REQUIRE(m1);
	REQUIRE(m2);

	player.set_midi_note_pitch(0, 5.0f, 0);
	CHECK(m1->get_output(0) == doctest::Approx(5.0f));
	CHECK(m2->get_output(0) == doctest::Approx(5.0f));
}

TEST_CASE("Split: MIDI -> Module In + Panel Out") {
	// MIDI Note -> module 1 jack 0 AND MIDI Note -> Panel Out 1 (via Hub)
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: D_split_mp
  module_slugs:
    0: HubMedium
    1: TestModule
  int_cables:
  mapped_ins:
    - panel_jack_id: 256
      ins:
        - module_id: 1
          jack_id: 0
        - module_id: 0
          jack_id: 1
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 1
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);
	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	auto m1 = get_test_module(player, 1);
	REQUIRE(m1);

	player.set_midi_note_pitch(0, 4.2f, 0);
	CHECK(m1->get_output(0) == doctest::Approx(4.2f));
	CHECK(player.get_panel_output(1) == doctest::Approx(4.2f));
}

TEST_CASE("Split: MIDI -> Panel Out + Panel Out") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: D_split_pp
  module_slugs:
    0: HubMedium
  int_cables:
  mapped_ins:
    - panel_jack_id: 256
      ins:
        - module_id: 0
          jack_id: 1
        - module_id: 0
          jack_id: 2
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 1
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);
	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	player.set_midi_note_pitch(0, 3.3f, 0);
	CHECK(player.get_panel_output(1) == doctest::Approx(3.3f));
	CHECK(player.get_panel_output(2) == doctest::Approx(3.3f));
}

// ============================================================================
// Summing: 2 outputs -> 1 input (6 pair combinations x 2 input types = 12)
// ============================================================================

TEST_CASE("Sum: Module Out + Module Out -> Module In") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: MM_to_m
  module_slugs:
    0: HubMedium
    1: TestModule
    2: TestModule
    3: TestModule
  int_cables:
    - out:
        module_id: 1
        jack_id: 0
      ins:
        - module_id: 3
          jack_id: 0
    - out:
        module_id: 2
        jack_id: 0
      ins:
        - module_id: 3
          jack_id: 0
  mapped_ins:
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 0
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);
	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	auto m1 = get_test_module(player, 1);
	auto m2 = get_test_module(player, 2);
	auto m3 = get_test_module(player, 3);
	REQUIRE(m1);
	REQUIRE(m2);
	REQUIRE(m3);

	m1->set_input(0, 1.5f);
	m2->set_input(0, 2.5f);
	player.update_patch();
	CHECK(m3->get_output(0) == doctest::Approx(4.0f));
}

TEST_CASE("Sum: Module Out + Module Out -> Panel Out") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: MM_to_p
  module_slugs:
    0: HubMedium
    1: TestModule
    2: TestModule
  int_cables:
  mapped_ins:
  mapped_outs:
    - panel_jack_id: 0
      out:
        module_id: 1
        jack_id: 0
    - panel_jack_id: 0
      out:
        module_id: 2
        jack_id: 0
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 0
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);
	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	auto m1 = get_test_module(player, 1);
	auto m2 = get_test_module(player, 2);
	REQUIRE(m1);
	REQUIRE(m2);

	m1->set_input(0, 1.0f);
	m2->set_input(0, 2.0f);
	player.update_patch();
	CHECK(player.get_panel_output(0) == doctest::Approx(3.0f));
}

TEST_CASE("Sum: Module Out + Panel In -> Module In") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: MP_to_m
  module_slugs:
    0: HubMedium
    1: TestModule
    2: TestModule
  int_cables:
    - out:
        module_id: 1
        jack_id: 0
      ins:
        - module_id: 2
          jack_id: 0
  mapped_ins:
    - panel_jack_id: 0
      ins:
        - module_id: 2
          jack_id: 0
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 0
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);
	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	auto m1 = get_test_module(player, 1);
	auto m2 = get_test_module(player, 2);
	REQUIRE(m1);
	REQUIRE(m2);

	m1->set_input(0, 2.0f);
	player.set_panel_input(0, 3.0f);
	player.update_patch();
	CHECK(m2->get_output(0) == doctest::Approx(5.0f));
}

TEST_CASE("Sum: Module Out + Panel In -> Panel Out") {
	// Module 1 out 0 mapped to panel out 0; Panel In 0 also mapped to panel out 0 (via Hub)
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: MP_to_p
  module_slugs:
    0: HubMedium
    1: TestModule
  int_cables:
  mapped_ins:
    - panel_jack_id: 0
      ins:
        - module_id: 0
          jack_id: 1
  mapped_outs:
    - panel_jack_id: 1
      out:
        module_id: 1
        jack_id: 0
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 0
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);
	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	auto m1 = get_test_module(player, 1);
	REQUIRE(m1);

	m1->set_input(0, 1.5f);
	player.set_panel_input(0, 2.5f);
	player.update_patch();
	CHECK(player.get_panel_output(1) == doctest::Approx(4.0f));
}

TEST_CASE("Sum: Module Out + MIDI -> Module In") {
	// Module 1 out 0 -> module 2 jack 0 (cable) + MIDI Note -> module 2 jack 0
	// The MIDI destination becomes a summed input with the cable.
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: MD_to_m
  module_slugs:
    0: HubMedium
    1: TestModule
    2: TestModule
  int_cables:
    - out:
        module_id: 1
        jack_id: 0
      ins:
        - module_id: 2
          jack_id: 0
  mapped_ins:
    - panel_jack_id: 256
      ins:
        - module_id: 2
          jack_id: 0
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 1
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);
	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	auto m1 = get_test_module(player, 1);
	auto m2 = get_test_module(player, 2);
	REQUIRE(m1);
	REQUIRE(m2);

	m1->set_input(0, 1.0f);
	player.set_midi_note_pitch(0, 2.0f, 0);
	player.update_patch();
	CHECK(m2->get_output(0) == doctest::Approx(3.0f));
}

TEST_CASE("Sum: Module Out + MIDI -> Panel Out") {
	// Module 1 out 0 -> Panel Out 0; MIDI Note -> Panel Out 0 (via Hub)
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: MD_to_p
  module_slugs:
    0: HubMedium
    1: TestModule
  int_cables:
  mapped_ins:
    - panel_jack_id: 256
      ins:
        - module_id: 0
          jack_id: 0
  mapped_outs:
    - panel_jack_id: 0
      out:
        module_id: 1
        jack_id: 0
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 1
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);
	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	auto m1 = get_test_module(player, 1);
	REQUIRE(m1);

	m1->set_input(0, 1.5f);
	player.set_midi_note_pitch(0, 2.5f, 0);
	player.update_patch();
	CHECK(player.get_panel_output(0) == doctest::Approx(4.0f));
}

TEST_CASE("Sum: Panel In + Panel In -> Module In") {
	// Two panel inputs both mapped to module 1 jack 0
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: PP_to_m
  module_slugs:
    0: HubMedium
    1: TestModule
  int_cables:
  mapped_ins:
    - panel_jack_id: 0
      ins:
        - module_id: 1
          jack_id: 0
    - panel_jack_id: 1
      ins:
        - module_id: 1
          jack_id: 0
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 0
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);
	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	auto m1 = get_test_module(player, 1);
	REQUIRE(m1);

	player.set_panel_input(0, 1.0f);
	player.set_panel_input(1, 2.0f);
	player.update_patch();
	CHECK(m1->get_output(0) == doctest::Approx(3.0f));
}

TEST_CASE("Sum: Panel In + Panel In -> Panel Out (Hub-to-Hub summing)") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: PP_to_p
  module_slugs:
    0: HubMedium
  int_cables:
  mapped_ins:
    - panel_jack_id: 0
      ins:
        - module_id: 0
          jack_id: 2
    - panel_jack_id: 1
      ins:
        - module_id: 0
          jack_id: 2
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 0
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);
	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	player.set_panel_input(0, 1.5f);
	player.set_panel_input(1, 3.5f);
	CHECK(player.get_panel_output(2) == doctest::Approx(5.0f));
}

TEST_CASE("Sum: Panel In + MIDI -> Module In") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: PD_to_m
  module_slugs:
    0: HubMedium
    1: TestModule
  int_cables:
  mapped_ins:
    - panel_jack_id: 0
      ins:
        - module_id: 1
          jack_id: 0
    - panel_jack_id: 256
      ins:
        - module_id: 1
          jack_id: 0
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 1
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);
	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	auto m1 = get_test_module(player, 1);
	REQUIRE(m1);

	player.set_panel_input(0, 2.0f);
	player.set_midi_note_pitch(0, 3.0f, 0);
	player.update_patch();
	CHECK(m1->get_output(0) == doctest::Approx(5.0f));
}

TEST_CASE("Sum: Panel In + MIDI -> Panel Out (via Hub)") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: PD_to_p
  module_slugs:
    0: HubMedium
  int_cables:
  mapped_ins:
    - panel_jack_id: 0
      ins:
        - module_id: 0
          jack_id: 2
    - panel_jack_id: 256
      ins:
        - module_id: 0
          jack_id: 2
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 1
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);
	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	player.set_panel_input(0, 1.0f);
	player.set_midi_note_pitch(0, 4.0f, 0);
	CHECK(player.get_panel_output(2) == doctest::Approx(5.0f));
}

TEST_CASE("MIDI Note and MIDI Gate to separate module jacks") {
	// MIDI Note pitch -> module 1 jack 0; MIDI Gate -> module 1 jack 1
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: DD_separate_m
  module_slugs:
    0: HubMedium
    1: TestModule
  int_cables:
  mapped_ins:
    - panel_jack_id: 256
      ins:
        - module_id: 1
          jack_id: 0
    - panel_jack_id: 272
      ins:
        - module_id: 1
          jack_id: 1
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 1
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);
	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	auto m1 = get_test_module(player, 1);
	REQUIRE(m1);

	player.set_midi_note_pitch(0, 3.0f, 0);
	player.set_midi_note_gate(0, 8.0f, 0);
	CHECK(m1->get_output(0) == doctest::Approx(3.0f));
	CHECK(m1->get_output(1) == doctest::Approx(8.0f));
}

TEST_CASE("MIDI Note and MIDI Gate to separate Panel Outs (via Hub)") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: DD_separate_p
  module_slugs:
    0: HubMedium
  int_cables:
  mapped_ins:
    - panel_jack_id: 256
      ins:
        - module_id: 0
          jack_id: 1
    - panel_jack_id: 272
      ins:
        - module_id: 0
          jack_id: 2
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 1
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);
	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	player.set_midi_note_pitch(0, 1.5f, 0);
	player.set_midi_note_gate(0, 3.5f, 0);
	CHECK(player.get_panel_output(1) == doctest::Approx(1.5f));
	CHECK(player.get_panel_output(2) == doctest::Approx(3.5f));
}

// ============================================================================
// 3-way summing
// ============================================================================

TEST_CASE("Sum: Module Out + Panel In + MIDI -> Module In") {
	// Module 1 out 0 -> module 2 jack 0 (cable)
	// Panel In 0 -> module 2 jack 0 (mapped_in, creates virtual cable via Hub)
	// MIDI Note -> module 2 jack 0 (mapped_in, also creates virtual cable via Hub)
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: MPD_to_m
  module_slugs:
    0: HubMedium
    1: TestModule
    2: TestModule
  int_cables:
    - out:
        module_id: 1
        jack_id: 0
      ins:
        - module_id: 2
          jack_id: 0
  mapped_ins:
    - panel_jack_id: 0
      ins:
        - module_id: 2
          jack_id: 0
    - panel_jack_id: 256
      ins:
        - module_id: 2
          jack_id: 0
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 1
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);
	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	auto m1 = get_test_module(player, 1);
	auto m2 = get_test_module(player, 2);
	REQUIRE(m1);
	REQUIRE(m2);

	m1->set_input(0, 1.0f);
	player.set_panel_input(0, 2.0f);
	player.set_midi_note_pitch(0, 3.0f, 0);
	player.update_patch();
	CHECK(m2->get_output(0) == doctest::Approx(6.0f));
}

TEST_CASE("Sum: Module Out + Panel In + MIDI -> Panel Out") {
	// Module 1 out 0 -> Panel Out 0 (mapped_out)
	// Panel In 0 -> Panel Out 0 (via Hub)
	// MIDI Note -> Panel Out 0 (via Hub)
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: MPD_to_p
  module_slugs:
    0: HubMedium
    1: TestModule
  int_cables:
  mapped_ins:
    - panel_jack_id: 0
      ins:
        - module_id: 0
          jack_id: 1
    - panel_jack_id: 256
      ins:
        - module_id: 0
          jack_id: 1
  mapped_outs:
    - panel_jack_id: 1
      out:
        module_id: 1
        jack_id: 0
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 1
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);
	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	auto m1 = get_test_module(player, 1);
	REQUIRE(m1);

	m1->set_input(0, 1.0f);
	player.set_panel_input(0, 2.0f);
	player.set_midi_note_pitch(0, 3.0f, 0);
	player.update_patch();
	CHECK(player.get_panel_output(1) == doctest::Approx(6.0f));
}

TEST_CASE("Sum: Panel In + Panel In + Panel In -> Module In") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: PPP_to_m
  module_slugs:
    0: HubMedium
    1: TestModule
  int_cables:
  mapped_ins:
    - panel_jack_id: 0
      ins:
        - module_id: 1
          jack_id: 0
    - panel_jack_id: 1
      ins:
        - module_id: 1
          jack_id: 0
    - panel_jack_id: 2
      ins:
        - module_id: 1
          jack_id: 0
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 0
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);
	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	auto m1 = get_test_module(player, 1);
	REQUIRE(m1);

	player.set_panel_input(0, 1.0f);
	player.set_panel_input(1, 2.0f);
	player.set_panel_input(2, 3.0f);
	player.update_patch();
	CHECK(m1->get_output(0) == doctest::Approx(6.0f));
}

TEST_CASE("Sum: Panel In + Panel In + Panel In -> Panel Out") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: PPP_to_p
  module_slugs:
    0: HubMedium
  int_cables:
  mapped_ins:
    - panel_jack_id: 0
      ins:
        - module_id: 0
          jack_id: 3
    - panel_jack_id: 1
      ins:
        - module_id: 0
          jack_id: 3
    - panel_jack_id: 2
      ins:
        - module_id: 0
          jack_id: 3
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 0
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);
	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	player.set_panel_input(0, 1.0f);
	player.set_panel_input(1, 2.0f);
	player.set_panel_input(2, 3.0f);
	CHECK(player.get_panel_output(3) == doctest::Approx(6.0f));
}

TEST_CASE("Sum: Panel In + Panel In + Module Out -> Module In") {
	// Two panel inputs + one cable all to module 2 jack 0
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: PPM_to_m
  module_slugs:
    0: HubMedium
    1: TestModule
    2: TestModule
  int_cables:
    - out:
        module_id: 1
        jack_id: 0
      ins:
        - module_id: 2
          jack_id: 0
  mapped_ins:
    - panel_jack_id: 0
      ins:
        - module_id: 2
          jack_id: 0
    - panel_jack_id: 1
      ins:
        - module_id: 2
          jack_id: 0
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 0
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);
	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	auto m1 = get_test_module(player, 1);
	auto m2 = get_test_module(player, 2);
	REQUIRE(m1);
	REQUIRE(m2);

	m1->set_input(0, 1.0f);
	player.set_panel_input(0, 2.0f);
	player.set_panel_input(1, 3.0f);
	player.update_patch();
	CHECK(m2->get_output(0) == doctest::Approx(6.0f));
}

TEST_CASE("Sum: Panel In + Panel In + Module Out -> Panel Out") {
	// Two panel inputs via Hub + one module output, all summed at panel out 3
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: PPM_to_p
  module_slugs:
    0: HubMedium
    1: TestModule
  int_cables:
  mapped_ins:
    - panel_jack_id: 0
      ins:
        - module_id: 0
          jack_id: 3
    - panel_jack_id: 1
      ins:
        - module_id: 0
          jack_id: 3
  mapped_outs:
    - panel_jack_id: 3
      out:
        module_id: 1
        jack_id: 0
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 0
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);
	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	auto m1 = get_test_module(player, 1);
	REQUIRE(m1);

	m1->set_input(0, 1.0f);
	player.set_panel_input(0, 2.0f);
	player.set_panel_input(1, 3.0f);
	player.update_patch();
	CHECK(player.get_panel_output(3) == doctest::Approx(6.0f));
}

TEST_CASE("Sum: Module Out + Module Out + Panel In -> Module In") {
	// Two cables + one panel input all to module 3 jack 0
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: MMP_to_m
  module_slugs:
    0: HubMedium
    1: TestModule
    2: TestModule
    3: TestModule
  int_cables:
    - out:
        module_id: 1
        jack_id: 0
      ins:
        - module_id: 3
          jack_id: 0
    - out:
        module_id: 2
        jack_id: 0
      ins:
        - module_id: 3
          jack_id: 0
  mapped_ins:
    - panel_jack_id: 0
      ins:
        - module_id: 3
          jack_id: 0
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 0
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);
	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	auto m1 = get_test_module(player, 1);
	auto m2 = get_test_module(player, 2);
	auto m3 = get_test_module(player, 3);
	REQUIRE(m1);
	REQUIRE(m2);
	REQUIRE(m3);

	m1->set_input(0, 1.0f);
	m2->set_input(0, 2.0f);
	player.set_panel_input(0, 3.0f);
	player.update_patch();
	CHECK(m3->get_output(0) == doctest::Approx(6.0f));
}

TEST_CASE("Sum: Module Out + Module Out + Panel In -> Panel Out") {
	// Two module outputs + one panel input via Hub, all summed at panel out 3
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: MMP_to_p
  module_slugs:
    0: HubMedium
    1: TestModule
    2: TestModule
  int_cables:
  mapped_ins:
    - panel_jack_id: 0
      ins:
        - module_id: 0
          jack_id: 3
  mapped_outs:
    - panel_jack_id: 3
      out:
        module_id: 1
        jack_id: 0
    - panel_jack_id: 3
      out:
        module_id: 2
        jack_id: 0
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 0
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);
	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	auto m1 = get_test_module(player, 1);
	auto m2 = get_test_module(player, 2);
	REQUIRE(m1);
	REQUIRE(m2);

	m1->set_input(0, 1.0f);
	m2->set_input(0, 2.0f);
	player.set_panel_input(0, 3.0f);
	player.update_patch();
	CHECK(player.get_panel_output(3) == doctest::Approx(6.0f));
}

// ============================================================================
// Split + Sum combinations
// ============================================================================

TEST_CASE("Split+Sum: Module Out splits to Module In and Panel Out; Module In also sums with Panel In") {
	// Module 1 out 0 -> module 2 jack 0 (cable, will be summed with Panel In)
	// Module 1 out 0 -> Panel Out 0 (mapped_out, split destination)
	// Panel In 0 -> module 2 jack 0 (mapped_in, summed with cable)
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: split_sum_MP_m_p
  module_slugs:
    0: HubMedium
    1: TestModule
    2: TestModule
  int_cables:
    - out:
        module_id: 1
        jack_id: 0
      ins:
        - module_id: 2
          jack_id: 0
  mapped_ins:
    - panel_jack_id: 0
      ins:
        - module_id: 2
          jack_id: 0
  mapped_outs:
    - panel_jack_id: 0
      out:
        module_id: 1
        jack_id: 0
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 0
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);
	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	auto m1 = get_test_module(player, 1);
	auto m2 = get_test_module(player, 2);
	REQUIRE(m1);
	REQUIRE(m2);

	m1->set_input(0, 4.0f);
	player.set_panel_input(0, 1.0f);
	player.update_patch();

	// Panel Out 0 gets module 1 output (no sum, just split)
	CHECK(player.get_panel_output(0) == doctest::Approx(4.0f));
	// Module 2 jack 0 gets module 1 output (4.0) + panel in (1.0) = 5.0
	CHECK(m2->get_output(0) == doctest::Approx(5.0f));
}

TEST_CASE("Split+Sum: Module Out splits to Module In and Panel Out; Module In also sums with MIDI") {
	// Module 1 out 0 -> module 2 jack 0 (cable)
	// Module 1 out 0 -> Panel Out 0 (mapped_out)
	// MIDI Note -> module 2 jack 0 (mapped_in, summed with cable)
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: split_sum_MD_m_p
  module_slugs:
    0: HubMedium
    1: TestModule
    2: TestModule
  int_cables:
    - out:
        module_id: 1
        jack_id: 0
      ins:
        - module_id: 2
          jack_id: 0
  mapped_ins:
    - panel_jack_id: 256
      ins:
        - module_id: 2
          jack_id: 0
  mapped_outs:
    - panel_jack_id: 0
      out:
        module_id: 1
        jack_id: 0
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 1
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);
	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	auto m1 = get_test_module(player, 1);
	auto m2 = get_test_module(player, 2);
	REQUIRE(m1);
	REQUIRE(m2);

	m1->set_input(0, 3.0f);
	player.set_midi_note_pitch(0, 2.0f, 0);
	player.update_patch();

	CHECK(player.get_panel_output(0) == doctest::Approx(3.0f));
	CHECK(m2->get_output(0) == doctest::Approx(5.0f));
}

TEST_CASE("Split+Sum: Panel In splits to Module In and Panel Out; Module In also sums with Module Out") {
	// Panel In 0 -> module 2 jack 0 (mapped_in, summed with cable from module 1)
	// Panel In 0 -> Panel Out 1 (via Hub, split)
	// Module 1 out 0 -> module 2 jack 0 (cable, summed with panel in)
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: split_P_sum_PM_m_p
  module_slugs:
    0: HubMedium
    1: TestModule
    2: TestModule
  int_cables:
    - out:
        module_id: 1
        jack_id: 0
      ins:
        - module_id: 2
          jack_id: 0
  mapped_ins:
    - panel_jack_id: 0
      ins:
        - module_id: 2
          jack_id: 0
        - module_id: 0
          jack_id: 1
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 0
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);
	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	auto m1 = get_test_module(player, 1);
	auto m2 = get_test_module(player, 2);
	REQUIRE(m1);
	REQUIRE(m2);

	m1->set_input(0, 2.0f);
	player.set_panel_input(0, 3.0f);
	player.update_patch();

	// Panel Out 1 gets panel in 0 value via Hub passthrough
	CHECK(player.get_panel_output(1) == doctest::Approx(3.0f));
	// Module 2 jack 0 gets module 1 (2.0) + panel in 0 (3.0) = 5.0
	CHECK(m2->get_output(0) == doctest::Approx(5.0f));
}

TEST_CASE("Split+Sum: MIDI splits to Module In and Panel Out; Module In also sums with Module Out") {
	// MIDI Note -> module 2 jack 0 (mapped_in)
	// MIDI Note -> Panel Out 1 (via Hub)
	// Module 1 out 0 -> module 2 jack 0 (cable, summed with MIDI)
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: split_D_sum_DM_m_p
  module_slugs:
    0: HubMedium
    1: TestModule
    2: TestModule
  int_cables:
    - out:
        module_id: 1
        jack_id: 0
      ins:
        - module_id: 2
          jack_id: 0
  mapped_ins:
    - panel_jack_id: 256
      ins:
        - module_id: 2
          jack_id: 0
        - module_id: 0
          jack_id: 1
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 1
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);
	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	auto m1 = get_test_module(player, 1);
	auto m2 = get_test_module(player, 2);
	REQUIRE(m1);
	REQUIRE(m2);

	m1->set_input(0, 2.0f);
	player.set_midi_note_pitch(0, 4.0f, 0);
	player.update_patch();

	// Panel Out 1 gets MIDI value via Hub
	CHECK(player.get_panel_output(1) == doctest::Approx(4.0f));
	// Module 2 jack 0 gets module 1 (2.0) + MIDI (4.0) = 6.0
	CHECK(m2->get_output(0) == doctest::Approx(6.0f));
}

TEST_CASE("Split+Sum: Module Out splits to two Module Ins; one of those also sums with Panel In + MIDI") {
	// Module 1 out 0 -> module 2 jack 0 (split dest 1, simple)
	// Module 1 out 0 -> module 3 jack 0 (split dest 2, summed with Panel In and MIDI)
	// Panel In 0 -> module 3 jack 0
	// MIDI Note -> module 3 jack 0
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: split_M_sum_MPD_mm
  module_slugs:
    0: HubMedium
    1: TestModule
    2: TestModule
    3: TestModule
  int_cables:
    - out:
        module_id: 1
        jack_id: 0
      ins:
        - module_id: 2
          jack_id: 0
        - module_id: 3
          jack_id: 0
  mapped_ins:
    - panel_jack_id: 0
      ins:
        - module_id: 3
          jack_id: 0
    - panel_jack_id: 256
      ins:
        - module_id: 3
          jack_id: 0
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 1
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);
	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	auto m1 = get_test_module(player, 1);
	auto m2 = get_test_module(player, 2);
	auto m3 = get_test_module(player, 3);
	REQUIRE(m1);
	REQUIRE(m2);
	REQUIRE(m3);

	m1->set_input(0, 1.0f);
	player.set_panel_input(0, 2.0f);
	player.set_midi_note_pitch(0, 3.0f, 0);
	player.update_patch();

	// Module 2 gets only module 1 output (no sum, just split)
	CHECK(m2->get_output(0) == doctest::Approx(1.0f));
	// Module 3 gets module 1 (1.0) + panel in (2.0) + MIDI (3.0) = 6.0
	CHECK(m3->get_output(0) == doctest::Approx(6.0f));
}

// ============================================================================
// MIDI type variations (Gate, CC, different pitch polyphony)
// ============================================================================

TEST_CASE("Simple: MIDI Gate -> Module In") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: Dgate_to_m
  module_slugs:
    0: HubMedium
    1: TestModule
  int_cables:
  mapped_ins:
    - panel_jack_id: 272
      ins:
        - module_id: 1
          jack_id: 0
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 1
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);
	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	auto m1 = get_test_module(player, 1);
	REQUIRE(m1);

	player.set_midi_note_gate(0, 8.0f, 0);
	CHECK(m1->get_output(0) == doctest::Approx(8.0f));
}

TEST_CASE("Simple: MIDI CC -> Module In") {
	// CC0 = panel_jack_id 0x200
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: Dcc_to_m
  module_slugs:
    0: HubMedium
    1: TestModule
  int_cables:
  mapped_ins:
    - panel_jack_id: 0x200
      ins:
        - module_id: 1
          jack_id: 0
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 1
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);
	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	auto m1 = get_test_module(player, 1);
	REQUIRE(m1);

	player.set_midi_cc(0, 127, 0);
	CHECK(m1->get_output(0) == doctest::Approx(127.f / 12.7f));
}

TEST_CASE("Simple: MIDI Gate -> Panel Out (via Hub)") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: Dgate_to_p
  module_slugs:
    0: HubMedium
  int_cables:
  mapped_ins:
    - panel_jack_id: 272
      ins:
        - module_id: 0
          jack_id: 3
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 1
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);
	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	player.set_midi_note_gate(0, 8.0f, 0);
	CHECK(player.get_panel_output(3) == doctest::Approx(8.0f));
}

// ============================================================================
// Edge cases: cable splitting interacting with summed inputs
// ============================================================================

TEST_CASE("Cable split where one destination is summed with Panel In") {
	// Cable: Module 1 out 0 → [Module 2 jack 0, Module 3 jack 0]
	// Panel In 0 → Module 3 jack 0 (creates summed input at Module 3 only)
	// Module 2 should get cable value only; Module 3 should get cable + panel in
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: split_cable_partial_sum
  module_slugs:
    0: HubMedium
    1: TestModule
    2: TestModule
    3: TestModule
  int_cables:
    - out:
        module_id: 1
        jack_id: 0
      ins:
        - module_id: 2
          jack_id: 0
        - module_id: 3
          jack_id: 0
  mapped_ins:
    - panel_jack_id: 0
      ins:
        - module_id: 3
          jack_id: 0
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 0
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);
	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	auto m1 = get_test_module(player, 1);
	auto m2 = get_test_module(player, 2);
	auto m3 = get_test_module(player, 3);
	REQUIRE(m1);
	REQUIRE(m2);
	REQUIRE(m3);

	m1->set_input(0, 4.0f);
	player.set_panel_input(0, 1.5f);
	player.update_patch();

	CHECK(m2->get_output(0) == doctest::Approx(4.0f));
	CHECK(m3->get_output(0) == doctest::Approx(5.5f));
}

TEST_CASE("Cable split where one destination is summed with MIDI") {
	// Cable: Module 1 out 0 → [Module 2 jack 0, Module 3 jack 0]
	// MIDI Note → Module 3 jack 0 (summed with cable)
	// Module 2 gets cable only; Module 3 gets cable + MIDI
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: split_cable_midi_sum
  module_slugs:
    0: HubMedium
    1: TestModule
    2: TestModule
    3: TestModule
  int_cables:
    - out:
        module_id: 1
        jack_id: 0
      ins:
        - module_id: 2
          jack_id: 0
        - module_id: 3
          jack_id: 0
  mapped_ins:
    - panel_jack_id: 256
      ins:
        - module_id: 3
          jack_id: 0
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 1
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);
	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	auto m1 = get_test_module(player, 1);
	auto m2 = get_test_module(player, 2);
	auto m3 = get_test_module(player, 3);
	REQUIRE(m1);
	REQUIRE(m2);
	REQUIRE(m3);

	m1->set_input(0, 3.0f);
	player.set_midi_note_pitch(0, 2.0f, 0);
	player.update_patch();

	CHECK(m2->get_output(0) == doctest::Approx(3.0f));
	CHECK(m3->get_output(0) == doctest::Approx(5.0f));
}

// ============================================================================
// Edge cases: non-zero jack IDs
// ============================================================================

TEST_CASE("Summing with non-zero jack IDs") {
	// Module 1 out jack 2 → Module 3 jack 3 (cable)
	// Module 2 out jack 1 → Module 3 jack 3 (cable, summed)
	// Panel In 1 → Module 3 jack 3 (mapped_in, also summed)
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: nonzero_jacks
  module_slugs:
    0: HubMedium
    1: TestModule
    2: TestModule
    3: TestModule
  int_cables:
    - out:
        module_id: 1
        jack_id: 2
      ins:
        - module_id: 3
          jack_id: 3
    - out:
        module_id: 2
        jack_id: 1
      ins:
        - module_id: 3
          jack_id: 3
  mapped_ins:
    - panel_jack_id: 1
      ins:
        - module_id: 3
          jack_id: 3
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 0
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);
	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	auto m1 = get_test_module(player, 1);
	auto m2 = get_test_module(player, 2);
	auto m3 = get_test_module(player, 3);
	REQUIRE(m1);
	REQUIRE(m2);
	REQUIRE(m3);

	m1->set_input(2, 1.0f);
	m2->set_input(1, 2.0f);
	player.set_panel_input(1, 3.0f);
	player.update_patch();

	// Module 3 jack 3 should receive sum of all three
	CHECK(m3->get_output(3) == doctest::Approx(6.0f));
	// Other jacks on module 3 should be unaffected
	CHECK(m3->get_output(0) == doctest::Approx(0.0f));
}

// ============================================================================
// Edge cases: Panel In split via separate mapped_ins, mixed direct/summing
// ============================================================================

TEST_CASE("Panel In split via separate entries: one destination has cable, one does not") {
	// Panel In 0 → Module 1 jack 0 (has cable from Module 3, so summed)
	// Panel In 0 → Module 2 jack 0 (no cable, direct)
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: panel_split_mixed
  module_slugs:
    0: HubMedium
    1: TestModule
    2: TestModule
    3: TestModule
  int_cables:
    - out:
        module_id: 3
        jack_id: 0
      ins:
        - module_id: 1
          jack_id: 0
  mapped_ins:
    - panel_jack_id: 0
      ins:
        - module_id: 1
          jack_id: 0
    - panel_jack_id: 0
      ins:
        - module_id: 2
          jack_id: 0
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 0
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);
	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	auto m1 = get_test_module(player, 1);
	auto m2 = get_test_module(player, 2);
	auto m3 = get_test_module(player, 3);
	REQUIRE(m1);
	REQUIRE(m2);
	REQUIRE(m3);

	m3->set_input(0, 5.0f);
	player.set_panel_input(0, 2.0f);
	player.update_patch();

	// Module 1 jack 0 gets cable from Module 3 (5.0) + panel in (2.0) = 7.0
	CHECK(m1->get_output(0) == doctest::Approx(7.0f));
	// Module 2 jack 0 gets panel in directly = 2.0
	CHECK(m2->get_output(0) == doctest::Approx(2.0f));
}

// ============================================================================
// Edge cases: MIDI split to Module In (summed with cable) + Panel Out
// ============================================================================

TEST_CASE("MIDI split to Module In (summed with cable) and Panel Out") {
	// MIDI Note → Module 2 jack 0 (summed with cable from Module 1)
	// MIDI Note → Panel Out 1 (via Hub)
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: midi_split_sum_panel
  module_slugs:
    0: HubMedium
    1: TestModule
    2: TestModule
  int_cables:
    - out:
        module_id: 1
        jack_id: 0
      ins:
        - module_id: 2
          jack_id: 0
  mapped_ins:
    - panel_jack_id: 256
      ins:
        - module_id: 2
          jack_id: 0
        - module_id: 0
          jack_id: 1
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 1
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);
	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	auto m1 = get_test_module(player, 1);
	auto m2 = get_test_module(player, 2);
	REQUIRE(m1);
	REQUIRE(m2);

	m1->set_input(0, 3.0f);
	player.set_midi_note_pitch(0, 2.0f, 0);
	player.update_patch();

	// Panel Out 1 gets MIDI value via Hub
	CHECK(player.get_panel_output(1) == doctest::Approx(2.0f));
	// Module 2 jack 0 gets cable (3.0) + MIDI (2.0) = 5.0
	CHECK(m2->get_output(0) == doctest::Approx(5.0f));
}

// ============================================================================
// Edge cases: Panel In split within single entry to module + Hub,
// where module also has a cable
// ============================================================================

TEST_CASE("Panel In split within single entry: one dest is Hub, other is module with cable") {
	// Panel In 0 → Module 2 jack 0 (has cable from Module 1, will sum)
	// Panel In 0 → Panel Out 1 (Hub passthrough)
	// Both destinations in the same mapped_ins entry
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: panel_split_hub_and_cable
  module_slugs:
    0: HubMedium
    1: TestModule
    2: TestModule
  int_cables:
    - out:
        module_id: 1
        jack_id: 0
      ins:
        - module_id: 2
          jack_id: 0
  mapped_ins:
    - panel_jack_id: 0
      ins:
        - module_id: 2
          jack_id: 0
        - module_id: 0
          jack_id: 1
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 0
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);
	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	auto m1 = get_test_module(player, 1);
	auto m2 = get_test_module(player, 2);
	REQUIRE(m1);
	REQUIRE(m2);

	m1->set_input(0, 4.0f);
	player.set_panel_input(0, 1.5f);
	player.update_patch();

	// Panel Out 1 gets panel in 0 value via Hub passthrough
	CHECK(player.get_panel_output(1) == doctest::Approx(1.5f));
	// Module 2 jack 0 gets cable (4.0) + panel in (1.5) = 5.5
	CHECK(m2->get_output(0) == doctest::Approx(5.5f));
}

// ============================================================================
// Edge cases: multiple overlapping panel mappings
// ============================================================================

TEST_CASE("Two Panel Ins to same module jack + one of them also goes to another module") {
	// Panel In 0 → Module 1 jack 0 (summed with Panel In 1)
	// Panel In 1 → Module 1 jack 0 (summed with Panel In 0)
	// Panel In 0 → Module 2 jack 0 (separate, direct)
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: overlapping_panel_maps
  module_slugs:
    0: HubMedium
    1: TestModule
    2: TestModule
  int_cables:
  mapped_ins:
    - panel_jack_id: 0
      ins:
        - module_id: 1
          jack_id: 0
    - panel_jack_id: 1
      ins:
        - module_id: 1
          jack_id: 0
    - panel_jack_id: 0
      ins:
        - module_id: 2
          jack_id: 0
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 0
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);
	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	auto m1 = get_test_module(player, 1);
	auto m2 = get_test_module(player, 2);
	REQUIRE(m1);
	REQUIRE(m2);

	player.set_panel_input(0, 3.0f);
	player.set_panel_input(1, 4.0f);
	player.update_patch();

	// Module 1 jack 0 gets sum of Panel In 0 (3.0) + Panel In 1 (4.0) = 7.0
	CHECK(m1->get_output(0) == doctest::Approx(7.0f));
	// Module 2 jack 0 gets Panel In 0 only = 3.0
	CHECK(m2->get_output(0) == doctest::Approx(3.0f));
}

TEST_CASE("Module output to panel out on non-zero jack IDs") {
	// Module 1 out jack 2 → Panel Out 3
	// Module 2 out jack 3 → Panel Out 3 (summed)
	// Panel In 5 → Panel Out 3 (via Hub, also summed)
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: nonzero_panel_sum
  module_slugs:
    0: HubMedium
    1: TestModule
    2: TestModule
  int_cables:
  mapped_ins:
    - panel_jack_id: 5
      ins:
        - module_id: 0
          jack_id: 3
  mapped_outs:
    - panel_jack_id: 3
      out:
        module_id: 1
        jack_id: 2
    - panel_jack_id: 3
      out:
        module_id: 2
        jack_id: 3
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 0
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);
	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	auto m1 = get_test_module(player, 1);
	auto m2 = get_test_module(player, 2);
	REQUIRE(m1);
	REQUIRE(m2);

	m1->set_input(2, 1.0f);
	m2->set_input(3, 2.0f);
	player.set_panel_input(5, 3.0f);
	player.update_patch();

	// Panel Out 3 sums: module 1 out 2 (1.0) + module 2 out 3 (2.0) + panel in 5 via Hub (3.0)
	CHECK(player.get_panel_output(3) == doctest::Approx(6.0f));
}
