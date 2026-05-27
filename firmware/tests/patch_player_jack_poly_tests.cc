#include "doctest.h"
#include "patch-serial/yaml_to_patch.hh"
#include "patch_play/patch_player.hh"
#include "stubs/test_module.hh"
#include "stubs/test_poly_module.hh"

// Comprehensive tests for every combination of poly sources and sinks:
//  - Poly source types (writing to more than channel 0):
//      Mp : Module Out, poly buffer (TestPolyModule)
//      Dp : MIDI Out, poly (MidiNotePolyJack = 336 / 0x150)
//  - Mono source types (every test must include at least one poly node):
//      Mm : Module Out, mono (TestModule)
//      Dm : MIDI Out, mono (MidiMonoNoteJack = 256 / 0x100)
//      P  : Panel In (always mono)
//  - Sink types:
//      mp : Module In, poly (TestPolyModule)
//      mm : Module In, mono (TestModule)
//      p  : Panel Out (sums all poly channels)

namespace
{
constexpr MetaModule::ModuleInfoView TestModuleInfo{
	.description = "Test module",
	.width_hp = 8,
};
[[maybe_unused]] bool s_test_mono_registered =
	MetaModule::ModuleFactory::registerModuleType("TestModule", TestModule::create, TestModuleInfo, "");

constexpr MetaModule::ModuleInfoView TestPolyModuleInfo{
	.description = "Test poly module",
	.width_hp = 8,
};
[[maybe_unused]] bool s_test_poly_registered =
	MetaModule::ModuleFactory::registerModuleType("TestPoly", TestPolyModule::create, TestPolyModuleInfo, "");

constexpr MetaModule::ModuleInfoView TestPanelInfo{
	.description = "Test panel",
	.width_hp = 8,
};
[[maybe_unused]] bool s_test_panel_registered =
	MetaModule::ModuleFactory::registerModuleType("HubMedium", TestPanel::create, TestPanelInfo, "");

auto *get_test_module(MetaModule::PatchPlayer &player, unsigned module_id) {
	return dynamic_cast<TestModule *>(player.modules[module_id].get());
}

auto *get_test_poly(MetaModule::PatchPlayer &player, unsigned module_id) {
	return dynamic_cast<TestPolyModule *>(player.modules[module_id].get());
}
} // namespace

// ============================================================================
// Simple routing: 1 source -> 1 sink
// Every test involves at least one poly node.
// ============================================================================

TEST_CASE("Poly Simple: poly Module Out -> poly Module In") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: Mp_to_mp
  module_slugs:
    0: HubMedium
    1: TestPoly
    2: TestPoly
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

	auto *p1 = get_test_poly(player, 1);
	auto *p2 = get_test_poly(player, 2);
	REQUIRE(p1);
	REQUIRE(p2);

	p1->output_channels[0] = 3;
	p1->output_poly[0] = {1.0f, 2.0f, 3.0f, 0.f};
	player.update_patch();

	CHECK(p2->input_channels[0] == 3);
	CHECK(p2->input_poly[0][0] == doctest::Approx(1.0f));
	CHECK(p2->input_poly[0][1] == doctest::Approx(2.0f));
	CHECK(p2->input_poly[0][2] == doctest::Approx(3.0f));
}

TEST_CASE("Poly Simple: poly Module Out -> mono Module In (channel 0 only)") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: Mp_to_mm
  module_slugs:
    0: HubMedium
    1: TestPoly
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

	auto *p1 = get_test_poly(player, 1);
	auto *m2 = get_test_module(player, 2);
	REQUIRE(p1);
	REQUIRE(m2);

	p1->output_channels[0] = 3;
	p1->output_poly[0] = {2.5f, 9.9f, 7.0f, 0.f};
	player.update_patch();

	// Only channel 0 of poly source is delivered to mono destination
	CHECK(m2->get_output(0) == doctest::Approx(2.5f));
}

TEST_CASE("Poly Simple: mono Module Out -> poly Module In (written via set_input)") {
	// mono source always calls set_input(), which for TestPolyModule writes to inputs_mono,
	// NOT to the input_poly buffer. The poly buffer stays at zero.
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: Mm_to_mp
  module_slugs:
    0: HubMedium
    1: TestModule
    2: TestPoly
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

	auto *m1 = get_test_module(player, 1);
	auto *p2 = get_test_poly(player, 2);
	REQUIRE(m1);
	REQUIRE(p2);

	m1->set_input(0, 4.5f);
	player.update_patch();

	CHECK(p2->inputs_mono[0] == doctest::Approx(4.5f));
	// Poly buffer is untouched by mono sources
	CHECK(p2->input_poly[0][0] == doctest::Approx(0.0f));
	CHECK(p2->input_poly[0][1] == doctest::Approx(0.0f));
}

TEST_CASE("Poly Simple: poly Module Out -> Panel Out (channels summed)") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: Mp_to_p
  module_slugs:
    0: HubMedium
    1: TestPoly
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

	auto *p1 = get_test_poly(player, 1);
	REQUIRE(p1);

	p1->output_channels[0] = 4;
	p1->output_poly[0] = {1.0f, 2.0f, 3.0f, 4.0f};

	CHECK(player.get_panel_output(0) == doctest::Approx(10.0f));
}

TEST_CASE("Poly Simple: poly MIDI -> poly Module In") {
	// MidiNotePolyJack = 336 (0x150)
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: Dp_to_mp
  module_slugs:
    0: HubMedium
    1: TestPoly
  int_cables:
  mapped_ins:
    - panel_jack_id: 336
      ins:
        - module_id: 1
          jack_id: 0
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 4
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
	player.set_midi_connected();

	auto *p1 = get_test_poly(player, 1);
	REQUIRE(p1);

	player.set_midi_note_pitch(0, 1.5f, 0);
	player.set_midi_note_pitch(1, 2.5f, 0);
	player.set_midi_note_pitch(2, 3.5f, 0);
	player.set_midi_note_pitch(3, -1.0f, 0);

	CHECK(p1->input_poly[0][0] == doctest::Approx(1.5f));
	CHECK(p1->input_poly[0][1] == doctest::Approx(2.5f));
	CHECK(p1->input_poly[0][2] == doctest::Approx(3.5f));
	CHECK(p1->input_poly[0][3] == doctest::Approx(-1.0f));
}

TEST_CASE("Poly Simple: poly MIDI -> mono Module In (only channel 0 via set_input fallback)") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: Dp_to_mm
  module_slugs:
    0: HubMedium
    1: TestModule
  int_cables:
  mapped_ins:
    - panel_jack_id: 336
      ins:
        - module_id: 1
          jack_id: 0
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 4
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
	player.set_midi_connected();

	auto *m1 = get_test_module(player, 1);
	REQUIRE(m1);

	// poly channel 0 writes to mono input via set_input fallback
	player.set_midi_note_pitch(0, 3.7f, 0);
	CHECK(m1->get_output(0) == doctest::Approx(3.7f));

	// poly channels > 0 are no-ops for a mono destination
	player.set_midi_note_pitch(1, 9.9f, 0);
	player.set_midi_note_pitch(2, 9.9f, 0);
	player.set_midi_note_pitch(3, 9.9f, 0);
	CHECK(m1->get_output(0) == doctest::Approx(3.7f));
}

TEST_CASE("Poly Simple: poly MIDI -> Panel Out (Hub is mono, only channel 0 delivers)") {
	// MIDI poly -> Hub jack (which has no poly buffer) -> Panel Out.
	// Only poly channel 0 writes through the set_input fallback into the Hub slot.
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: Dp_to_p
  module_slugs:
    0: HubMedium
  int_cables:
  mapped_ins:
    - panel_jack_id: 336
      ins:
        - module_id: 0
          jack_id: 1
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 4
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
	player.set_midi_connected();

	player.set_midi_note_pitch(0, 2.0f, 0);
	CHECK(player.get_panel_output(1) == doctest::Approx(2.0f));

	// Higher poly channels do not propagate to mono Hub slot
	player.set_midi_note_pitch(1, 5.0f, 0);
	player.set_midi_note_pitch(2, 5.0f, 0);
	CHECK(player.get_panel_output(1) == doctest::Approx(2.0f));
}

TEST_CASE("Poly Simple: mono MIDI -> poly Module In (stored in inputs_mono)") {
	// Mono MIDI is delivered via set_input, which TestPolyModule stores in inputs_mono.
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: Dm_to_mp
  module_slugs:
    0: HubMedium
    1: TestPoly
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
	player.set_midi_connected();

	auto *p1 = get_test_poly(player, 1);
	REQUIRE(p1);

	player.set_midi_note_pitch(0, 4.2f, 0);
	CHECK(p1->inputs_mono[0] == doctest::Approx(4.2f));
	// Poly buffer is untouched
	CHECK(p1->input_poly[0][0] == doctest::Approx(0.0f));
}

// ============================================================================
// Splitting: 1 source -> 2+ sinks (at least one node is poly)
// ============================================================================

TEST_CASE("Poly Split: poly Module Out -> poly m + poly m") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: Mp_split_mpmp
  module_slugs:
    0: HubMedium
    1: TestPoly
    2: TestPoly
    3: TestPoly
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

	auto *p1 = get_test_poly(player, 1);
	auto *p2 = get_test_poly(player, 2);
	auto *p3 = get_test_poly(player, 3);
	REQUIRE(p1);
	REQUIRE(p2);
	REQUIRE(p3);

	p1->output_channels[0] = 4;
	p1->output_poly[0] = {1.1f, 2.2f, 3.3f, 4.4f};
	player.update_patch();

	CHECK(p2->input_channels[0] == 4);
	CHECK(p3->input_channels[0] == 4);
	for (unsigned ch = 0; ch < 4; ch++) {
		CHECK(p2->input_poly[0][ch] == doctest::Approx(p1->output_poly[0][ch]));
		CHECK(p3->input_poly[0][ch] == doctest::Approx(p1->output_poly[0][ch]));
	}
}

TEST_CASE("Poly Split: poly Module Out -> poly m + mono m") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: Mp_split_mpmm
  module_slugs:
    0: HubMedium
    1: TestPoly
    2: TestPoly
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

	auto *p1 = get_test_poly(player, 1);
	auto *p2 = get_test_poly(player, 2);
	auto *m3 = get_test_module(player, 3);
	REQUIRE(p1);
	REQUIRE(p2);
	REQUIRE(m3);

	p1->output_channels[0] = 3;
	p1->output_poly[0] = {2.0f, 4.0f, 6.0f, 0.f};
	player.update_patch();

	// Poly destination: full channels
	CHECK(p2->input_channels[0] == 3);
	CHECK(p2->input_poly[0][0] == doctest::Approx(2.0f));
	CHECK(p2->input_poly[0][1] == doctest::Approx(4.0f));
	CHECK(p2->input_poly[0][2] == doctest::Approx(6.0f));

	// Mono destination: only channel 0
	CHECK(m3->get_output(0) == doctest::Approx(2.0f));
}

TEST_CASE("Poly Split: poly Module Out -> mono m + mono m (both get channel 0)") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: Mp_split_mmmm
  module_slugs:
    0: HubMedium
    1: TestPoly
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

	auto *p1 = get_test_poly(player, 1);
	auto *m2 = get_test_module(player, 2);
	auto *m3 = get_test_module(player, 3);
	REQUIRE(p1);
	REQUIRE(m2);
	REQUIRE(m3);

	p1->output_channels[0] = 4;
	p1->output_poly[0] = {7.0f, 8.0f, 9.0f, 10.0f};
	player.update_patch();

	CHECK(m2->get_output(0) == doctest::Approx(7.0f));
	CHECK(m3->get_output(0) == doctest::Approx(7.0f));
}

TEST_CASE("Poly Split: poly Module Out -> poly m + Panel Out") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: Mp_split_mp_p
  module_slugs:
    0: HubMedium
    1: TestPoly
    2: TestPoly
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

	auto *p1 = get_test_poly(player, 1);
	auto *p2 = get_test_poly(player, 2);
	REQUIRE(p1);
	REQUIRE(p2);

	p1->output_channels[0] = 3;
	p1->output_poly[0] = {1.0f, 2.0f, 3.0f, 0.f};
	player.update_patch();

	// Poly destination: full channels via cable
	CHECK(p2->input_channels[0] == 3);
	CHECK(p2->input_poly[0][0] == doctest::Approx(1.0f));
	CHECK(p2->input_poly[0][1] == doctest::Approx(2.0f));
	CHECK(p2->input_poly[0][2] == doctest::Approx(3.0f));

	// Panel Out: sums all channels
	CHECK(player.get_panel_output(0) == doctest::Approx(6.0f));
}

TEST_CASE("Poly Split: poly Module Out -> mono m + Panel Out") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: Mp_split_mm_p
  module_slugs:
    0: HubMedium
    1: TestPoly
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

	auto *p1 = get_test_poly(player, 1);
	auto *m2 = get_test_module(player, 2);
	REQUIRE(p1);
	REQUIRE(m2);

	p1->output_channels[0] = 2;
	p1->output_poly[0] = {3.0f, 5.0f, 0.f, 0.f};
	player.update_patch();

	// Mono destination: channel 0 only
	CHECK(m2->get_output(0) == doctest::Approx(3.0f));
	// Panel Out: sums all channels
	CHECK(player.get_panel_output(0) == doctest::Approx(8.0f));
}

TEST_CASE("Poly Split: poly Module Out -> Panel Out + Panel Out") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: Mp_split_p_p
  module_slugs:
    0: HubMedium
    1: TestPoly
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

	auto *p1 = get_test_poly(player, 1);
	REQUIRE(p1);

	p1->output_channels[0] = 4;
	p1->output_poly[0] = {1.0f, 2.0f, 3.0f, 4.0f};

	// Both panel outs independently sum the full set of channels
	CHECK(player.get_panel_output(0) == doctest::Approx(10.0f));
	CHECK(player.get_panel_output(1) == doctest::Approx(10.0f));
}

TEST_CASE("Poly Split: mono Module Out -> poly m + poly m (inputs_mono on both)") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: Mm_split_mpmp
  module_slugs:
    0: HubMedium
    1: TestModule
    2: TestPoly
    3: TestPoly
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

	auto *m1 = get_test_module(player, 1);
	auto *p2 = get_test_poly(player, 2);
	auto *p3 = get_test_poly(player, 3);
	REQUIRE(m1);
	REQUIRE(p2);
	REQUIRE(p3);

	m1->set_input(0, 6.0f);
	player.update_patch();

	CHECK(p2->inputs_mono[0] == doctest::Approx(6.0f));
	CHECK(p3->inputs_mono[0] == doctest::Approx(6.0f));
	// Poly buffers untouched
	CHECK(p2->input_poly[0][0] == doctest::Approx(0.0f));
	CHECK(p3->input_poly[0][0] == doctest::Approx(0.0f));
}

TEST_CASE("Poly Split: poly MIDI -> poly m + poly m") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: Dp_split_mpmp
  module_slugs:
    0: HubMedium
    1: TestPoly
    2: TestPoly
  int_cables:
  mapped_ins:
    - panel_jack_id: 336
      ins:
        - module_id: 1
          jack_id: 0
        - module_id: 2
          jack_id: 0
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 4
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
	player.set_midi_connected();

	auto *p1 = get_test_poly(player, 1);
	auto *p2 = get_test_poly(player, 2);
	REQUIRE(p1);
	REQUIRE(p2);

	player.set_midi_note_pitch(0, 1.0f, 0);
	player.set_midi_note_pitch(1, 2.0f, 0);
	player.set_midi_note_pitch(2, 3.0f, 0);

	for (unsigned ch = 0; ch < 3; ch++) {
		CHECK(p1->input_poly[0][ch] == doctest::Approx(float(ch + 1)));
		CHECK(p2->input_poly[0][ch] == doctest::Approx(float(ch + 1)));
	}
}

TEST_CASE("Poly Split: poly MIDI -> poly m + mono m") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: Dp_split_mpmm
  module_slugs:
    0: HubMedium
    1: TestPoly
    2: TestModule
  int_cables:
  mapped_ins:
    - panel_jack_id: 336
      ins:
        - module_id: 1
          jack_id: 0
        - module_id: 2
          jack_id: 0
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 4
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
	player.set_midi_connected();

	auto *p1 = get_test_poly(player, 1);
	auto *m2 = get_test_module(player, 2);
	REQUIRE(p1);
	REQUIRE(m2);

	// Channel 0 goes to both poly buffer and mono set_input
	player.set_midi_note_pitch(0, 2.5f, 0);
	CHECK(p1->input_poly[0][0] == doctest::Approx(2.5f));
	CHECK(m2->get_output(0) == doctest::Approx(2.5f));

	// Higher channels go to poly buffer only
	player.set_midi_note_pitch(2, 4.0f, 0);
	CHECK(p1->input_poly[0][2] == doctest::Approx(4.0f));
	CHECK(m2->get_output(0) == doctest::Approx(2.5f));
}

TEST_CASE("Poly Split: poly MIDI -> poly m + Panel Out") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: Dp_split_mp_p
  module_slugs:
    0: HubMedium
    1: TestPoly
  int_cables:
  mapped_ins:
    - panel_jack_id: 336
      ins:
        - module_id: 1
          jack_id: 0
        - module_id: 0
          jack_id: 1
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 4
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
	player.set_midi_connected();

	auto *p1 = get_test_poly(player, 1);
	REQUIRE(p1);

	// Channel 0 writes to both poly buffer and Hub slot
	player.set_midi_note_pitch(0, 3.0f, 0);
	CHECK(p1->input_poly[0][0] == doctest::Approx(3.0f));
	CHECK(player.get_panel_output(1) == doctest::Approx(3.0f));

	// Higher channels update only the poly buffer
	player.set_midi_note_pitch(1, 7.0f, 0);
	CHECK(p1->input_poly[0][1] == doctest::Approx(7.0f));
	CHECK(player.get_panel_output(1) == doctest::Approx(3.0f));
}

// ============================================================================
// Summing: 2+ sources -> 1 sink
// ============================================================================

TEST_CASE("Poly Sum: poly M + poly M -> poly m (per-channel sum)") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: MpMp_to_mp
  module_slugs:
    0: HubMedium
    1: TestPoly
    2: TestPoly
    3: TestPoly
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

	auto *p1 = get_test_poly(player, 1);
	auto *p2 = get_test_poly(player, 2);
	auto *p3 = get_test_poly(player, 3);
	REQUIRE(p1);
	REQUIRE(p2);
	REQUIRE(p3);

	p1->output_channels[0] = 3;
	p1->output_poly[0] = {1.0f, 2.0f, 3.0f, 0.f};

	p2->output_channels[0] = 4;
	p2->output_poly[0] = {10.0f, 20.0f, 30.0f, 40.0f};

	player.update_patch();

	// Max channel count wins; per-channel sum; missing channels contribute 0.
	CHECK(p3->input_channels[0] == 4);
	CHECK(p3->input_poly[0][0] == doctest::Approx(11.0f));
	CHECK(p3->input_poly[0][1] == doctest::Approx(22.0f));
	CHECK(p3->input_poly[0][2] == doctest::Approx(33.0f));
	CHECK(p3->input_poly[0][3] == doctest::Approx(40.0f));
}

TEST_CASE("Poly Sum: poly M + mono M -> poly m (mono source adds to channel 0)") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: MpMm_to_mp
  module_slugs:
    0: HubMedium
    1: TestPoly
    2: TestModule
    3: TestPoly
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

	auto *p1 = get_test_poly(player, 1);
	auto *m2 = get_test_module(player, 2);
	auto *p3 = get_test_poly(player, 3);
	REQUIRE(p1);
	REQUIRE(m2);
	REQUIRE(p3);

	p1->output_channels[0] = 3;
	p1->output_poly[0] = {1.0f, 2.0f, 3.0f, 0.f};
	m2->set_input(0, 10.0f);

	player.update_patch();

	CHECK(p3->input_channels[0] == 3);
	// Mono source adds to channel 0
	CHECK(p3->input_poly[0][0] == doctest::Approx(11.0f));
	CHECK(p3->input_poly[0][1] == doctest::Approx(2.0f));
	CHECK(p3->input_poly[0][2] == doctest::Approx(3.0f));
}

TEST_CASE("Poly Sum: poly M + Panel In -> poly m (panel input adds to channel 0)") {
	// Panel In + cable to same module input creates a summed input via the Hub virtual cable.
	// The Hub source is mono, so the panel value is added to channel 0 only.
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: MpP_to_mp
  module_slugs:
    0: HubMedium
    1: TestPoly
    2: TestPoly
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

	auto *p1 = get_test_poly(player, 1);
	auto *p2 = get_test_poly(player, 2);
	REQUIRE(p1);
	REQUIRE(p2);

	p1->output_channels[0] = 3;
	p1->output_poly[0] = {1.5f, 2.5f, 3.5f, 0.f};
	player.set_panel_input(0, 10.0f);
	player.update_patch();

	CHECK(p2->input_channels[0] == 3);
	CHECK(p2->input_poly[0][0] == doctest::Approx(11.5f));
	CHECK(p2->input_poly[0][1] == doctest::Approx(2.5f));
	CHECK(p2->input_poly[0][2] == doctest::Approx(3.5f));
}

TEST_CASE("Poly Sum: poly M + mono MIDI -> poly m (MIDI via Hub adds to channel 0)") {
	// Mono MIDI + cable to same module input: MIDI is routed through a Hub virtual
	// cable, which adds to channel 0.
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: MpDm_to_mp
  module_slugs:
    0: HubMedium
    1: TestPoly
    2: TestPoly
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
	player.set_midi_connected();

	auto *p1 = get_test_poly(player, 1);
	auto *p2 = get_test_poly(player, 2);
	REQUIRE(p1);
	REQUIRE(p2);

	p1->output_channels[0] = 2;
	p1->output_poly[0] = {1.0f, 2.0f, 0.f, 0.f};
	player.set_midi_note_pitch(0, 5.0f, 0);
	player.update_patch();

	CHECK(p2->input_channels[0] == 2);
	CHECK(p2->input_poly[0][0] == doctest::Approx(6.0f));
	CHECK(p2->input_poly[0][1] == doctest::Approx(2.0f));
}

TEST_CASE("Poly Sum: poly M + poly MIDI -> poly m (MIDI via mono Hub slot: only ch0)") {
	// When poly MIDI is summed with a cable via the Hub virtual cable mechanism, the
	// Hub slot is a mono passthrough — only MIDI poly channel 0 propagates.
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: MpDp_to_mp
  module_slugs:
    0: HubMedium
    1: TestPoly
    2: TestPoly
  int_cables:
    - out:
        module_id: 1
        jack_id: 0
      ins:
        - module_id: 2
          jack_id: 0
  mapped_ins:
    - panel_jack_id: 336
      ins:
        - module_id: 2
          jack_id: 0
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 4
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
	player.set_midi_connected();

	auto *p1 = get_test_poly(player, 1);
	auto *p2 = get_test_poly(player, 2);
	REQUIRE(p1);
	REQUIRE(p2);

	p1->output_channels[0] = 2;
	p1->output_poly[0] = {1.0f, 2.0f, 0.f, 0.f};

	// Channel 0 MIDI passes through the Hub slot and adds to cable ch0.
	player.set_midi_note_pitch(0, 4.0f, 0);
	// Higher poly channels do NOT reach the mono Hub slot.
	player.set_midi_note_pitch(1, 99.0f, 0);
	player.set_midi_note_pitch(2, 99.0f, 0);
	player.update_patch();

	CHECK(p2->input_poly[0][0] == doctest::Approx(5.0f));
	CHECK(p2->input_poly[0][1] == doctest::Approx(2.0f));
}

TEST_CASE("Poly Sum: poly M + poly M -> mono m (uses outputs_mono from each poly source)") {
	// For summed inputs with a mono destination, the code path sums get_output() which
	// for TestPolyModule reads outputs_mono, NOT the poly buffer.
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: MpMp_to_mm
  module_slugs:
    0: HubMedium
    1: TestPoly
    2: TestPoly
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

	auto *p1 = get_test_poly(player, 1);
	auto *p2 = get_test_poly(player, 2);
	auto *m3 = get_test_module(player, 3);
	REQUIRE(p1);
	REQUIRE(p2);
	REQUIRE(m3);

	// Set outputs_mono, which is what the summed-to-mono path reads.
	p1->outputs_mono[0] = 1.5f;
	p2->outputs_mono[0] = 2.5f;

	player.update_patch();

	CHECK(m3->get_output(0) == doctest::Approx(4.0f));
}

TEST_CASE("Poly Sum: poly M + mono M -> mono m") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: MpMm_to_mm
  module_slugs:
    0: HubMedium
    1: TestPoly
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

	auto *p1 = get_test_poly(player, 1);
	auto *m2 = get_test_module(player, 2);
	auto *m3 = get_test_module(player, 3);
	REQUIRE(p1);
	REQUIRE(m2);
	REQUIRE(m3);

	p1->outputs_mono[0] = 3.0f;
	m2->set_input(0, 7.0f);

	player.update_patch();

	CHECK(m3->get_output(0) == doctest::Approx(10.0f));
}

TEST_CASE("Poly Sum: poly M + poly M -> Panel Out (both fully summed)") {
	// Two poly module outputs mapped to the same panel out: each contributes the
	// sum of its poly channels.
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: MpMp_to_p
  module_slugs:
    0: HubMedium
    1: TestPoly
    2: TestPoly
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

	auto *p1 = get_test_poly(player, 1);
	auto *p2 = get_test_poly(player, 2);
	REQUIRE(p1);
	REQUIRE(p2);

	p1->output_channels[0] = 3;
	p1->output_poly[0] = {1.0f, 2.0f, 3.0f, 0.f};

	p2->output_channels[0] = 4;
	p2->output_poly[0] = {0.5f, 0.5f, 0.5f, 0.5f};

	// (1+2+3) + (0.5*4) = 6 + 2 = 8
	CHECK(player.get_panel_output(0) == doctest::Approx(8.0f));
}

TEST_CASE("Poly Sum: poly M + mono M -> Panel Out") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: MpMm_to_p
  module_slugs:
    0: HubMedium
    1: TestPoly
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

	auto *p1 = get_test_poly(player, 1);
	auto *m2 = get_test_module(player, 2);
	REQUIRE(p1);
	REQUIRE(m2);

	p1->output_channels[0] = 3;
	p1->output_poly[0] = {1.0f, 2.0f, 3.0f, 0.f};
	m2->set_input(0, 4.0f);

	// poly sums to 6, mono adds 4 => 10
	CHECK(player.get_panel_output(0) == doctest::Approx(10.0f));
}

TEST_CASE("Poly Sum: poly M + Panel In -> Panel Out") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: MpP_to_p
  module_slugs:
    0: HubMedium
    1: TestPoly
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

	auto *p1 = get_test_poly(player, 1);
	REQUIRE(p1);

	p1->output_channels[0] = 3;
	p1->output_poly[0] = {1.0f, 2.0f, 3.0f, 0.f};
	player.set_panel_input(0, 4.5f);

	// poly sums to 6, panel in adds 4.5 => 10.5
	CHECK(player.get_panel_output(1) == doctest::Approx(10.5f));
}

TEST_CASE("Poly Sum: poly M + mono MIDI -> Panel Out") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: MpDm_to_p
  module_slugs:
    0: HubMedium
    1: TestPoly
  int_cables:
  mapped_ins:
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
	player.set_midi_connected();

	auto *p1 = get_test_poly(player, 1);
	REQUIRE(p1);

	p1->output_channels[0] = 4;
	p1->output_poly[0] = {0.5f, 0.5f, 0.5f, 0.5f};
	player.set_midi_note_pitch(0, 3.0f, 0);

	// poly sums to 2, MIDI contributes 3 => 5
	CHECK(player.get_panel_output(1) == doctest::Approx(5.0f));
}

// ============================================================================
// 3-way sums
// ============================================================================

TEST_CASE("Poly Sum: poly M + poly M + poly M -> poly m (per-channel)") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: Mp3_to_mp
  module_slugs:
    0: HubMedium
    1: TestPoly
    2: TestPoly
    3: TestPoly
    4: TestPoly
  int_cables:
    - out:
        module_id: 1
        jack_id: 0
      ins:
        - module_id: 4
          jack_id: 0
    - out:
        module_id: 2
        jack_id: 0
      ins:
        - module_id: 4
          jack_id: 0
    - out:
        module_id: 3
        jack_id: 0
      ins:
        - module_id: 4
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

	auto *p1 = get_test_poly(player, 1);
	auto *p2 = get_test_poly(player, 2);
	auto *p3 = get_test_poly(player, 3);
	auto *p4 = get_test_poly(player, 4);
	REQUIRE(p1);
	REQUIRE(p2);
	REQUIRE(p3);
	REQUIRE(p4);

	p1->output_channels[0] = 1;
	p1->output_poly[0] = {100.0f, 0.f, 0.f, 0.f};

	p2->output_channels[0] = 3;
	p2->output_poly[0] = {1.0f, 2.0f, 3.0f, 0.f};

	p3->output_channels[0] = 4;
	p3->output_poly[0] = {0.1f, 0.2f, 0.3f, 0.4f};

	player.update_patch();

	CHECK(p4->input_channels[0] == 4);
	CHECK(p4->input_poly[0][0] == doctest::Approx(101.1f));
	CHECK(p4->input_poly[0][1] == doctest::Approx(2.2f));
	CHECK(p4->input_poly[0][2] == doctest::Approx(3.3f));
	CHECK(p4->input_poly[0][3] == doctest::Approx(0.4f));
}

TEST_CASE("Poly Sum: poly M + poly M + mono M -> poly m") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: MpMpMm_to_mp
  module_slugs:
    0: HubMedium
    1: TestPoly
    2: TestPoly
    3: TestModule
    4: TestPoly
  int_cables:
    - out:
        module_id: 1
        jack_id: 0
      ins:
        - module_id: 4
          jack_id: 0
    - out:
        module_id: 2
        jack_id: 0
      ins:
        - module_id: 4
          jack_id: 0
    - out:
        module_id: 3
        jack_id: 0
      ins:
        - module_id: 4
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

	auto *p1 = get_test_poly(player, 1);
	auto *p2 = get_test_poly(player, 2);
	auto *m3 = get_test_module(player, 3);
	auto *p4 = get_test_poly(player, 4);
	REQUIRE(p1);
	REQUIRE(p2);
	REQUIRE(m3);
	REQUIRE(p4);

	p1->output_channels[0] = 2;
	p1->output_poly[0] = {1.0f, 2.0f, 0.f, 0.f};

	p2->output_channels[0] = 3;
	p2->output_poly[0] = {10.0f, 20.0f, 30.0f, 0.f};

	m3->set_input(0, 100.0f);

	player.update_patch();

	CHECK(p4->input_channels[0] == 3);
	CHECK(p4->input_poly[0][0] == doctest::Approx(111.0f));
	CHECK(p4->input_poly[0][1] == doctest::Approx(22.0f));
	CHECK(p4->input_poly[0][2] == doctest::Approx(30.0f));
}

// ============================================================================
// Split + Sum combinations
// ============================================================================

TEST_CASE("Poly Split+Sum: poly M splits to {poly m, mono m} where poly m also sums with another poly M") {
	// Module 1 (poly) -> Module 3 (poly) and Module 4 (mono).
	// Module 2 (poly) -> Module 3 (poly). So Module 3 input is summed.
	// Module 4 still receives ch0 of Module 1 only (not summed).
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: Mp_splitsum
  module_slugs:
    0: HubMedium
    1: TestPoly
    2: TestPoly
    3: TestPoly
    4: TestModule
  int_cables:
    - out:
        module_id: 1
        jack_id: 0
      ins:
        - module_id: 3
          jack_id: 0
        - module_id: 4
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

	auto *p1 = get_test_poly(player, 1);
	auto *p2 = get_test_poly(player, 2);
	auto *p3 = get_test_poly(player, 3);
	auto *m4 = get_test_module(player, 4);
	REQUIRE(p1);
	REQUIRE(p2);
	REQUIRE(p3);
	REQUIRE(m4);

	p1->output_channels[0] = 2;
	p1->output_poly[0] = {1.0f, 2.0f, 0.f, 0.f};

	p2->output_channels[0] = 3;
	p2->output_poly[0] = {10.0f, 20.0f, 30.0f, 0.f};

	player.update_patch();

	// Module 3 gets per-channel sum
	CHECK(p3->input_channels[0] == 3);
	CHECK(p3->input_poly[0][0] == doctest::Approx(11.0f));
	CHECK(p3->input_poly[0][1] == doctest::Approx(22.0f));
	CHECK(p3->input_poly[0][2] == doctest::Approx(30.0f));

	// Module 4 (mono, non-summed path): uses ch0 of module 1's poly buffer
	CHECK(m4->get_output(0) == doctest::Approx(1.0f));
}

TEST_CASE("Poly Split+Sum: poly M splits to {poly m, Panel Out} where poly m sums with mono M") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: Mp_splitsum_panel
  module_slugs:
    0: HubMedium
    1: TestPoly
    2: TestModule
    3: TestPoly
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

	auto *p1 = get_test_poly(player, 1);
	auto *m2 = get_test_module(player, 2);
	auto *p3 = get_test_poly(player, 3);
	REQUIRE(p1);
	REQUIRE(m2);
	REQUIRE(p3);

	p1->output_channels[0] = 3;
	p1->output_poly[0] = {2.0f, 4.0f, 6.0f, 0.f};
	m2->set_input(0, 10.0f);

	player.update_patch();

	// Summed at module 3: poly channels from mod 1 + mono adds to ch0
	CHECK(p3->input_channels[0] == 3);
	CHECK(p3->input_poly[0][0] == doctest::Approx(12.0f));
	CHECK(p3->input_poly[0][1] == doctest::Approx(4.0f));
	CHECK(p3->input_poly[0][2] == doctest::Approx(6.0f));

	// Panel Out: sums channels from mod 1 only (not summed with mod 2 here)
	CHECK(player.get_panel_output(0) == doctest::Approx(12.0f));
}
