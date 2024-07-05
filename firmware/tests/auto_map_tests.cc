#include "doctest.h"
#include "patch/patch_data.hh"
#include "patch_play/auto_map.hh"

TEST_CASE("Basic usage: knob") {
	using namespace MetaModule;

	PatchData p;
	PatchModQueue pq;
	AutoMapper automap{pq};

	uint16_t mod1 = p.add_module("Module1");
	uint16_t mod2 = p.add_module("Module2");
	uint16_t mod3 = p.add_module("Module3");

	SUBCASE("Map some knobs") {
		unsigned expected_panel_knob_id = 0;

		auto test_map_knob = [&](unsigned set_id, uint16_t module_id, uint8_t param_id) {
			// Check that the knob is initially not mapped
			for (unsigned set_i = 0; set_i < MaxKnobSets; set_i++) {
				CHECK(p.find_mapped_knob(set_i, module_id, param_id) == nullptr);
			}

			auto index = ElementCount::mark_unused_indices({.param_idx = param_id}, {.num_params = 1});
			auto res = automap.map(module_id, index, p);

			// Check result is expected mapping
			CHECK(res.has_value());
			CHECK(res->panel_el_id == expected_panel_knob_id);
			CHECK(res->set_id == set_id);

			// Check map shows up in the patch
			auto map = p.find_mapped_knob(set_id, module_id, param_id);
			CHECK(map != nullptr);
			CHECK(map->panel_knob_id == expected_panel_knob_id);
			CHECK(map->param_id == param_id);
			CHECK(map->module_id == module_id);

			// check we auto map fails for the same knob again, because it's already mapped
			CHECK(automap.map(module_id, {.param_idx = param_id}, p).has_value() == false);

			expected_panel_knob_id++;
		};

		// First 12 knobs go in set 0
		test_map_knob(0, mod1, 1);
		test_map_knob(0, mod2, 2);
		test_map_knob(0, mod3, 3);
		test_map_knob(0, mod3, 4);
		test_map_knob(0, mod3, 5);
		test_map_knob(0, mod3, 6);
		test_map_knob(0, mod3, 7);
		test_map_knob(0, mod3, 8);
		test_map_knob(0, mod3, 9);
		test_map_knob(0, mod3, 10);
		test_map_knob(0, mod3, 11);
		test_map_knob(0, mod3, 12);

		// Next 12 knobs go in set 1
		expected_panel_knob_id = 0;
		test_map_knob(1, mod3, 13);
		test_map_knob(1, mod3, 14);
		//etc..
	}

	SUBCASE("Fill all knobsets") {
		const unsigned leave_open_set_id = 4;
		const unsigned leave_open_knob_id = 3;

		uint16_t param_id = 0;
		for (unsigned set_i = 0; set_i < MaxKnobSets; set_i++) {
			for (uint16_t panel_knob_id = 0; panel_knob_id < PanelDef::NumKnobs; panel_knob_id++) {

				// Leave one space open:
				if (panel_knob_id == leave_open_knob_id && set_i == leave_open_set_id)
					continue;

				for ([[maybe_unused]] auto multi_map = 0u; multi_map < 8; multi_map++) {
					bool ok = p.add_update_mapped_knob(set_i,
													   MappedKnob{.panel_knob_id = panel_knob_id,
																  .module_id = mod3,
																  .param_id = param_id,
																  .min = 0,
																  .max = 1,
																  .alias_name = ""});
					CHECK(ok);
					param_id++;
				}
			}
		}

		auto res = automap.map(mod1, {.param_idx = 250}, p);
		CHECK(res.has_value());
		CHECK(res->panel_el_id == leave_open_knob_id);
		CHECK(res->set_id == leave_open_set_id);

		auto map = p.find_mapped_knob(leave_open_set_id, mod1, 250);
		CHECK(map != nullptr);
		CHECK(map->param_id == 250);
		CHECK(map->module_id == mod1);
		CHECK(map->panel_knob_id == leave_open_knob_id);

		CHECK(automap.map(mod1, {.param_idx = 1}, p).has_value() == false);
	}
}

TEST_CASE("Map jacks") {
	using namespace MetaModule;

	PatchData p;
	PatchModQueue pq;
	AutoMapper automap{pq};

	uint16_t mod1 = p.add_module("Module1");
	uint16_t mod2 = p.add_module("Module2");

	unsigned expected_panel_jack_id = 0;

	// Define some test procedures:

	auto test_map_injack = [&](uint16_t module_id, uint8_t jack_id) {
		Jack jack{.module_id = module_id, .jack_id = jack_id};

		// Check that the jack is initially not mapped
		CHECK(p.find_mapped_injack(jack) == nullptr);

		auto index = ElementCount::mark_unused_indices({.input_idx = jack_id}, {.num_inputs = 1});

		auto res = automap.map(module_id, index, p);

		// Check result is expected mapping
		CHECK(res.has_value());
		CHECK(res->panel_el_id == expected_panel_jack_id);

		// Check map shows up in the patch
		auto map = p.find_mapped_injack(jack);
		CHECK(map != nullptr);
		CHECK(map->panel_jack_id == expected_panel_jack_id);
		CHECK(map->ins.size() == 1);
		CHECK(map->ins[0].module_id == module_id);
		CHECK(map->ins[0].jack_id == jack_id);

		// check that auto map fails for the same jack again, because it's already mapped
		CHECK(automap.map(module_id, index, p).has_value() == false);

		expected_panel_jack_id++;
	};

	auto test_fail_map_injack = [&](uint16_t module_id, uint8_t jack_id) {
		Jack jack{.module_id = module_id, .jack_id = jack_id};
		auto index = ElementCount::mark_unused_indices({.input_idx = jack_id}, {.num_inputs = 1});

		// Check that the jack is initially not mapped
		CHECK(p.find_mapped_injack(jack) == nullptr);

		// Check mapping fails
		auto res = automap.map(module_id, index, p);
		CHECK_FALSE(res.has_value());
	};

	auto test_map_outjack = [&](uint16_t module_id, uint8_t jack_id) {
		Jack jack{.module_id = module_id, .jack_id = jack_id};

		// Check that the jack is initially not mapped
		CHECK(p.find_mapped_outjack(jack) == nullptr);

		auto index = ElementCount::mark_unused_indices({.output_idx = jack_id}, {.num_outputs = 1});

		auto res = automap.map(module_id, index, p);

		// Check result is expected mapping
		CHECK(res.has_value());
		CHECK(res->panel_el_id == expected_panel_jack_id);

		// Check map shows up in the patch
		auto map = p.find_mapped_outjack(jack);
		CHECK(map != nullptr);
		CHECK(map->panel_jack_id == expected_panel_jack_id);
		CHECK(map->out.module_id == module_id);
		CHECK(map->out.jack_id == jack_id);

		// check that auto map fails for the same jack again, because it's already mapped
		CHECK(automap.map(module_id, index, p).has_value() == false);

		expected_panel_jack_id++;
	};

	auto test_fail_map_outjack = [&](uint16_t module_id, uint8_t jack_id) {
		Jack jack{.module_id = module_id, .jack_id = jack_id};
		auto index = ElementCount::mark_unused_indices({.output_idx = jack_id}, {.num_outputs = 1});

		// Check that the jack is initially not mapped
		CHECK(p.find_mapped_outjack(jack) == nullptr);

		// Check mapping fails
		auto res = automap.map(module_id, index, p);
		CHECK_FALSE(res.has_value());
	};

	// Test input mapping:

	for (auto i = 0u; i < PanelDef::NumAudioIn; i++) {
		test_map_injack(mod2, i);
	}

	// Max input jacks already mapped, so auto mapping fails:
	test_fail_map_injack(mod1, 0);
	test_fail_map_injack(mod1, 1);
	test_fail_map_injack(mod1, 2);

	// Test output mapping:

	expected_panel_jack_id = 0;

	for (auto i = 0u; i < PanelDef::NumAudioOut; i++) {
		test_map_outjack(mod2, i);
	}

	// Max output jacks already mapped, so auto mapping fails:
	test_fail_map_outjack(mod1, 0);
	test_fail_map_outjack(mod1, 1);
	test_fail_map_outjack(mod1, 2);
}
