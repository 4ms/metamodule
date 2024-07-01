#include "doctest.h"
#include "patch/patch_data.hh"
#include "patch_play/auto_map.hh"

TEST_CASE("Basic usage: knob") {
	using namespace MetaModule;

	PatchData p;

	uint16_t mod1 = p.add_module("Module1");
	uint16_t mod2 = p.add_module("Module2");
	uint16_t mod3 = p.add_module("Module3");

	SUBCASE("Map some knobs") {
		unsigned expected_panel_knob_id = 0;

		// Auto map a knob
		{
			const unsigned set_id = 0;
			const unsigned param_id = 3;

			// Check that the knob is initially not mapped
			for (unsigned set_i : std::views::iota(0u, MaxKnobSets)) {
				CHECK(p.find_mapped_knob(set_i, mod2, param_id) == nullptr);
			}

			CHECK(AutoMapper::make(mod2, {.param_idx = param_id}, p) == true);

			// Check that the map is in the patch, in the first knob set
			auto map = p.find_mapped_knob(set_id, mod2, param_id);
			CHECK(map != nullptr);
			CHECK(map->panel_knob_id == expected_panel_knob_id);
			CHECK(map->param_id == param_id);
			CHECK(map->module_id == mod2);

			// check we can't auto map the same knob again, because it's already mapped
			CHECK(AutoMapper::make(mod2, {.param_idx = param_id}, p) == false);
		}

		{
			const unsigned set_id = 0;
			const unsigned param_id = 6;

			// Check that the knob is initially not mapped
			for (unsigned set_i : std::views::iota(0u, MaxKnobSets)) {
				CHECK(p.find_mapped_knob(set_i, mod1, param_id) == nullptr);
			}

			CHECK(AutoMapper::make(mod1, {.param_idx = param_id}, p) == true);
			expected_panel_knob_id++;

			auto map = p.find_mapped_knob(set_id, mod1, param_id);
			CHECK(map != nullptr);
			CHECK(map->panel_knob_id == expected_panel_knob_id);
			CHECK(map->param_id == param_id);
			CHECK(map->module_id == mod1);

			// check we auto map fails for the same knob again, because it's already mapped
			CHECK(AutoMapper::make(mod1, {.param_idx = param_id}, p) == false);
		}
	}

	SUBCASE("Fill all knobsets") {
		const unsigned leave_open_set_id = 4;
		const unsigned leave_open_knob_id = 3;

		uint16_t param_id = 0;
		for (unsigned set_i : std::views::iota(0u, MaxKnobSets)) {
			for (uint16_t panel_knob_id : std::views::iota(0u, PanelDef::NumKnobs)) {

				// Leave one space open:
				if (panel_knob_id == leave_open_knob_id && set_i == leave_open_set_id)
					continue;

				for ([[maybe_unused]] auto multi_map : std::views::iota(0u, 8u)) {
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

		CHECK(AutoMapper::make(mod1, {.param_idx = 250}, p) == true);
		auto map = p.find_mapped_knob(leave_open_set_id, mod1, 250);
		CHECK(map != nullptr);
		CHECK(map->param_id == 250);
		CHECK(map->module_id == mod1);
		CHECK(map->panel_knob_id == leave_open_knob_id);

		CHECK(AutoMapper::make(mod1, {.param_idx = 1}, p) == false);
	}
}
