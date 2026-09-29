#include "CoreModules/elements/element_info.hh"
#include "CoreModules/elements/element_info_view.hh"
#include "CoreModules/moduleFactory.hh"
#include "doctest.h"
#include "params/param_num_positions.hh"
#include "params/toggle_param.hh"
#include "patch-serial/yaml_to_patch.hh"
#include "patch_play/patch_player.hh"
#include "stubs/test_module.hh"

namespace
{

struct CycleFixture {
	std::unique_ptr<CoreProcessor> module = TestModule::create();
	MappedKnob map{.panel_knob_id = 0, .module_id = 1, .param_id = 2, .curve_type = MappedKnob::Cycle, .min = 0, .max = 1};

	float val() const {
		return module->get_param(map.param_id);
	}
	void press(unsigned num_pos) {
		latch_button(module, map, num_pos, 1.f);
	}
};

} // namespace

TEST_CASE("Cycle map steps through all positions of a 3-position switch, wrapping around") {
	CycleFixture f;
	f.module->set_param(2, 0.f);

	f.press(3);
	CHECK(f.val() == doctest::Approx(0.5f));
	f.press(3);
	CHECK(f.val() == doctest::Approx(1.f));
	f.press(3);
	CHECK(f.val() == doctest::Approx(0.f));
	f.press(3);
	CHECK(f.val() == doctest::Approx(0.5f));
}

TEST_CASE("Cycle map: falling edge does nothing") {
	CycleFixture f;
	f.module->set_param(2, 0.f);
	latch_button(f.module, f.map, 3, 0.f);
	CHECK(f.val() == 0.f);
}

TEST_CASE("Cycle map is limited to positions within min/max") {
	CycleFixture f;

	SUBCASE("5 positions, min=25% max=75% -> positions 1,2,3") {
		f.map.min = 0.25f;
		f.map.max = 0.75f;
		f.module->set_param(2, 0.25f);
		f.press(5);
		CHECK(f.val() == doctest::Approx(0.5f));
		f.press(5);
		CHECK(f.val() == doctest::Approx(0.75f));
		f.press(5);
		CHECK(f.val() == doctest::Approx(0.25f));
	}

	SUBCASE("7 positions, min/max set with 1% sliders: 17%..83% -> positions 1..5") {
		f.map.min = 0.17f;
		f.map.max = 0.83f;
		f.module->set_param(2, 5.f / 6.f);
		f.press(7);
		CHECK(f.val() == doctest::Approx(1.f / 6.f));
	}

	SUBCASE("Current value outside of range jumps to the min") {
		f.map.min = 0.5f;
		f.map.max = 1.f;
		f.module->set_param(2, 0.f);
		f.press(3);
		CHECK(f.val() == doctest::Approx(0.5f));
	}
}

TEST_CASE("Cycle map with max < min steps backwards") {
	CycleFixture f;
	f.map.min = 1.f;
	f.map.max = 0.f;
	f.module->set_param(2, 1.f);

	f.press(4);
	CHECK(f.val() == doctest::Approx(2.f / 3.f));
	f.press(4);
	CHECK(f.val() == doctest::Approx(1.f / 3.f));
	f.press(4);
	CHECK(f.val() == doctest::Approx(0.f));
	f.press(4);
	CHECK(f.val() == doctest::Approx(1.f));
}

TEST_CASE("Cycle map falls back to toggle for continuous params or ranges with < 2 positions") {
	CycleFixture f;
	f.map.min = 0.2f;
	f.map.max = 0.8f;
	f.module->set_param(2, 0.2f);

	SUBCASE("Continuous") {
		f.press(0);
		CHECK(f.val() == doctest::Approx(0.8f));
		f.press(0);
		CHECK(f.val() == doctest::Approx(0.2f));
	}

	SUBCASE("2-position switch with range 20%..80% contains no positions") {
		f.press(2);
		CHECK(f.val() == doctest::Approx(0.8f));
	}
}

TEST_CASE("Toggle map ignores num_pos") {
	CycleFixture f;
	f.map.curve_type = MappedKnob::Toggle;
	f.module->set_param(2, 0.f);
	f.press(3);
	CHECK(f.val() == 1.f);
	f.press(3);
	CHECK(f.val() == 0.f);
}

// Module with a 3-position switch (param 0), a snapped 5-position knob (param 1), and a continuous knob (param 2)
namespace
{

constexpr MetaModule::SlideSwitch make_switch(unsigned num_pos) {
	MetaModule::SlideSwitch s{};
	s.num_pos = num_pos;
	return s;
}

constexpr MetaModule::KnobSnapped make_snapped_knob(unsigned num_pos) {
	MetaModule::KnobSnapped k{};
	k.num_pos = num_pos;
	return k;
}

struct TestSwitchModuleInfo : MetaModule::ModuleInfoBase {
	static constexpr uint32_t width_hp = 4;
	static constexpr std::array<MetaModule::Element, 3> Elements{{
		make_switch(3),
		make_snapped_knob(5),
		MetaModule::Knob{},
	}};
};

[[maybe_unused]] bool s_test_switch_registered = MetaModule::ModuleFactory::registerModuleType(
	"TestSwitchModule",
	TestModule::create,
	MetaModule::ModuleInfoView::makeView<TestSwitchModuleInfo>(),
	"");

[[maybe_unused]] bool s_test_hub_registered = MetaModule::ModuleFactory::registerModuleType(
	"HubMedium", TestPanel::create, MetaModule::ModuleInfoView{.description = "Test panel", .width_hp = 8}, "");

} // namespace

TEST_CASE("get_param_num_positions reads num_pos from the param's element") {
	using namespace MetaModule;
	CHECK(get_param_num_positions("TestSwitchModule", 0) == 3);
	CHECK(get_param_num_positions("TestSwitchModule", 1) == 5);
	CHECK(get_param_num_positions("TestSwitchModule", 2) == 0);
	CHECK(get_param_num_positions("TestSwitchModule", 99) == 0);
	CHECK(get_param_num_positions("NoSuchModule", 0) == 0);
}

TEST_CASE("PatchPlayer: button and MIDI note Cycle maps step through the switch positions") {
	// Button 44 (first expander button) -> param 0 (3-pos switch), Cycle
	// MIDI note 60 (0x33C = 828) -> param 1 (5-pos snapped knob), Cycle, range 25%-100%
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: cycle_test
  module_slugs:
    0: HubMedium
    1: TestSwitchModule
  int_cables:
  mapped_ins:
  mapped_outs:
  static_knobs:
  mapped_knobs:
    - name: Knob Set 1
      set:
        - panel_knob_id: 44
          module_id: 1
          param_id: 0
          curve_type: 2
          min: 0
          max: 1
  midi_maps:
    name: MIDI
    set:
      - panel_knob_id: 828
        module_id: 1
        param_id: 1
        curve_type: 2
        min: 0.25
        max: 1
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
	REQUIRE(pd.knob_sets.size() == 1);
	REQUIRE(pd.knob_sets[0].set[0].curve_type == MappedKnob::Cycle);

	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	auto m1 = dynamic_cast<TestModule *>(player.modules[1].get());
	REQUIRE(m1);

	auto press_button = [&] {
		player.set_panel_param(44, 1.f);
		player.set_panel_param(44, 0.f);
	};

	CHECK(m1->params[0] == 0.f);
	press_button();
	CHECK(m1->params[0] == doctest::Approx(0.5f));
	press_button();
	CHECK(m1->params[0] == doctest::Approx(1.f));
	press_button();
	CHECK(m1->params[0] == doctest::Approx(0.f));

	auto play_note = [&] {
		player.set_midi_gate(60, 10.f, 0);
		player.set_midi_gate(60, 0.f, 0);
	};

	// Starts out of range (0), so first press goes to min (position 1 = 0.25)
	play_note();
	CHECK(m1->params[1] == doctest::Approx(0.25f));
	play_note();
	CHECK(m1->params[1] == doctest::Approx(0.5f));
	play_note();
	CHECK(m1->params[1] == doctest::Approx(0.75f));
	play_note();
	CHECK(m1->params[1] == doctest::Approx(1.f));
	play_note();
	CHECK(m1->params[1] == doctest::Approx(0.25f));
}

TEST_CASE("New button and MIDI note maps default to Cycle for params with more than 2 positions") {
	using namespace MetaModule;
	PatchData pd;
	pd.module_slugs.push_back("HubMedium");
	pd.module_slugs.push_back("TestSwitchModule");

	auto map_to = [](uint16_t panel_knob_id, uint16_t param_id) {
		return MappedKnob{.panel_knob_id = panel_knob_id, .module_id = 1, .param_id = param_id, .min = 0, .max = 1};
	};
	constexpr uint16_t Button = FirstButton;
	constexpr uint16_t Knob = 0;
	constexpr uint16_t Note = MidiGateNote0 + 60;
	constexpr uint16_t CC = MidiCC0 + 7;

	// Param 0: 3-pos switch, param 1: 5-pos snapped knob, param 2: continuous knob
	CHECK(default_curve_type(map_to(Button, 0), pd) == MappedKnob::Cycle);
	CHECK(default_curve_type(map_to(Button, 1), pd) == MappedKnob::Cycle);
	CHECK(default_curve_type(map_to(Button, 2), pd) == MappedKnob::Normal);
	CHECK(default_curve_type(map_to(Note, 0), pd) == MappedKnob::Cycle);
	CHECK(default_curve_type(map_to(Note, 2), pd) == MappedKnob::Normal);

	// Knobs and CCs sweep through the positions
	CHECK(default_curve_type(map_to(Knob, 0), pd) == MappedKnob::Normal);
	CHECK(default_curve_type(map_to(CC, 0), pd) == MappedKnob::Normal);

	// Unknown module
	auto bad = map_to(Button, 0);
	bad.module_id = 5;
	CHECK(default_curve_type(bad, pd) == MappedKnob::Normal);
}
