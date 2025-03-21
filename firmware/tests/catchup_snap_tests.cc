#include "CoreModules/CoreProcessor.hh"
#include "doctest.h"
#include "params/catchup_manager.hh"
#include "params/catchup_param.hh"
#include <cmath>
#include <memory>

// These tests use a module that has 'snapping' params:
// Param 0-6: only values N/4 are allowed: 0, 0.25, 0.5, 0.75, 1.0
// Param 7: button: snap to 0 or 1 (0.5f threshold)
struct SnapModule : CoreProcessor {
	std::array<float, 8> params{};

	void set_param(int param_id, float val) override {
		if (param_id == 7) {
			params[param_id] = (val > 0.5f) ? 1.f : 0.f;
		} else if (param_id > 0 && param_id < (int)params.size())
			params[param_id] = std::round(val * 4.f) / 4.f;
	}
	float get_param(int param_id) const override {
		if (param_id > 0 && param_id < (int)params.size())
			return params[param_id];
		else
			return 0;
	}
	void update() override {
	}
	void set_samplerate(float sr) override {
	}
	void set_input(int input_id, float val) override {
	}
	float get_output(int output_id) const override {
		return 0;
	}
};

TEST_CASE("Basic usage of ResumeOnEqual") {
	using namespace MetaModule;

	std::array<std::unique_ptr<CoreProcessor>, 1> modules;
	modules[0] = std::make_unique<SnapModule>();

	CatchupManager catchup_manager;
	std::array<ParamSet, MaxKnobSets> knob_maps;

	unsigned active_knobset = 0;

	SUBCASE("Normal mapping (0-1 => 0-1). Test for pickup on equal, module changing value, switching knobsets") {
		unsigned panel_knob = 1;
		unsigned param_id = 2;

		auto &p = knob_maps[active_knobset][panel_knob].emplace_back();
		p.map.panel_knob_id = panel_knob;
		p.map.module_id = 0;
		p.map.param_id = param_id;
		p.catchup.set_mode(CatchupParam::Mode::ResumeOnEqual);
		p.map.min = 0;
		p.map.max = 1;

		// Starting (default) value
		CHECK(modules[0]->get_param(param_id) == 0.0f);
		CHECK(p.catchup.is_tracking() == false);

		// Moving knob has no effect
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.2f);
		CHECK(modules[0]->get_param(param_id) == 0.0f);
		CHECK(p.catchup.is_tracking() == false);

		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.4f);
		CHECK(modules[0]->get_param(param_id) == 0.0f);
		CHECK(p.catchup.is_tracking() == false);

		// Moving knob to 0, then to a new value makes it track (snapping to nearest N/4)
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.0f);
		CHECK(modules[0]->get_param(param_id) == 0.0f);
		CHECK(p.catchup.is_tracking() == true);

		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.3f);
		CHECK(modules[0]->get_param(param_id) == 0.25f);
		CHECK(p.catchup.is_tracking() == true);

		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.4f);
		CHECK(modules[0]->get_param(param_id) == 0.5f);
		CHECK(p.catchup.is_tracking() == true);

		// Module changes own value -> stop tracking until knob value matches
		modules[0]->set_param(param_id, 0.75f);
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.5f);
		CHECK(modules[0]->get_param(param_id) == 0.75f);
		CHECK(p.catchup.is_tracking() == false);

		// It's not enough for the knob to be a value that would normally caused the current module's value...
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.7f);
		CHECK(modules[0]->get_param(param_id) == 0.75f);
		CHECK(p.catchup.is_tracking() == false);

		// ...knob value must match snapped module value to start tracking
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.75f);
		CHECK(modules[0]->get_param(param_id) == 0.75);
		CHECK(p.catchup.is_tracking() == true);

		//User switches knobset, moves knob (which is mapped to something else)
		active_knobset = 1;
		catchup_manager.reset(modules, knob_maps[active_knobset]);
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.2f);
		// User switches knobset back -> stop tracking
		active_knobset = 0;
		catchup_manager.reset(modules, knob_maps[active_knobset]);
		CHECK(modules[0]->get_param(param_id) == 0.75);
		CHECK(p.catchup.is_tracking() == false);

		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.2f);
		CHECK(p.catchup.is_tracking() == false);

		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.3f);
		CHECK(p.catchup.is_tracking() == false);

		// Move knob close to module value -> start tracking again
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.75001f);
		CHECK(modules[0]->get_param(param_id) == 0.75f);
		CHECK(p.catchup.is_tracking() == true);

		//// User switches knobset and then back again, without moving knob -> still tracking
		active_knobset = 1;
		catchup_manager.reset(modules, knob_maps[active_knobset]);
		active_knobset = 0;
		catchup_manager.reset(modules, knob_maps[active_knobset]);
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.75001f);
		CHECK(p.catchup.is_tracking() == true);

		//// Module changes own value (so that tracking mode stops)
		modules[0]->set_param(param_id, 0.25f);
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.75001f);
		CHECK(modules[0]->get_param(param_id) == 0.25f);
		CHECK(p.catchup.is_tracking() == false);

		// User switches knobset and then back again, without moving knob -> still not tracking
		active_knobset = 1;
		catchup_manager.reset(modules, knob_maps[active_knobset]);
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.75001f);
		active_knobset = 0;
		catchup_manager.reset(modules, knob_maps[active_knobset]);
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.75001f);
		CHECK(p.catchup.is_tracking() == false);
		CHECK(modules[0]->get_param(param_id) == 0.25f);
	}

	SUBCASE("Inverted mapping") {
		unsigned panel_knob = 1;
		unsigned param_id = 7;

		auto &p = knob_maps[active_knobset][panel_knob].emplace_back();
		p.map.panel_knob_id = panel_knob;
		p.map.module_id = 0;
		p.map.param_id = param_id;
		p.catchup.set_mode(CatchupParam::Mode::ResumeOnEqual);
		p.map.min = 0.51f;
		p.map.max = 0.f;

		catchup_manager.set_default_mode(CatchupParam::Mode::ResumeOnEqual, true);

		// Starting param value is 1 (which is what our panel knob at 0 maps to)
		modules[0]->set_param(param_id, 1.f);
		CHECK(modules[0]->get_param(param_id) == 1.0f);

		// Load the patch
		catchup_manager.reset(modules, knob_maps[active_knobset]);

		// Moving knob should track
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.01f);
		CHECK(modules[0]->get_param(param_id) == 1.0f);
		CHECK(p.catchup.is_tracking() == true);
	}
}

TEST_CASE("Basic usage of ResumeOnMotion") {
	using namespace MetaModule;

	std::array<std::unique_ptr<CoreProcessor>, 1> modules;
	modules[0] = std::make_unique<SnapModule>();

	CatchupManager catchup_manager;
	std::array<ParamSet, MaxKnobSets> knob_maps;

	// Knob 1: set to .3
	unsigned active_knobset = 0;
	unsigned panel_knob = 1;
	unsigned param_id = 2;

	auto &p = knob_maps[active_knobset][panel_knob].emplace_back();
	p.map.panel_knob_id = panel_knob;
	p.map.module_id = 0;
	p.map.param_id = param_id;
	p.catchup.set_mode(CatchupParam::Mode::ResumeOnMotion);

	SUBCASE("Normal mapping (0-1 => 0-1). Test for pickup, module changing value, switching knobsets") {
		p.map.min = 0;
		p.map.max = 1;

		// Starting (default) value
		CHECK(modules[0]->get_param(param_id) == 0.0f);
		CHECK(p.catchup.is_tracking() == false);

		// Moving knob has immediate effect
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.2f);
		CHECK(modules[0]->get_param(param_id) == 0.25f);
		CHECK(p.catchup.is_tracking() == true);

		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.4f);
		CHECK(modules[0]->get_param(param_id) == 0.5f);
		CHECK(p.catchup.is_tracking() == true);

		// Module changes own value -> immediately tracks knob
		// technically, this is not "resume on motion" since the knob did not move
		// but the engine only calls set_panel_param() if the knob changed values, so
		// effecively it works as "resume on motion"
		modules[0]->set_param(param_id, 0.75f);
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.4f);
		CHECK(modules[0]->get_param(param_id) == 0.5f);
		CHECK(p.catchup.is_tracking() == true);

		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.7f);
		CHECK(modules[0]->get_param(param_id) == 0.75f);
		CHECK(p.catchup.is_tracking() == true);

		//User switches knobset, moves knob (which is mapped to something else)
		active_knobset = 1;
		catchup_manager.reset(modules, knob_maps[active_knobset]);
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.2f);
		// User switches knobset back -> stop tracking
		active_knobset = 0;
		catchup_manager.reset(modules, knob_maps[active_knobset]);
		CHECK(modules[0]->get_param(param_id) == 0.75f);
		CHECK(p.catchup.is_tracking() == false);

		// Starts tracking when knob moved
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.3f);
		CHECK(modules[0]->get_param(param_id) == 0.25f);
		CHECK(p.catchup.is_tracking() == true);
	}
}

TEST_CASE("Basic usage of LinearFade") {
	using namespace MetaModule;

	std::array<std::unique_ptr<CoreProcessor>, 1> modules;
	modules[0] = std::make_unique<SnapModule>();

	CatchupManager catchup_manager;
	std::array<ParamSet, MaxKnobSets> knob_maps;

	// Knob 1: set to .3
	unsigned active_knobset = 0;
	unsigned panel_knob = 1;
	unsigned param_id = 2;

	auto &p = knob_maps[active_knobset][panel_knob].emplace_back();
	p.map.panel_knob_id = panel_knob;
	p.map.module_id = 0;
	p.map.param_id = param_id;
	p.catchup.set_mode(CatchupParam::Mode::LinearFade);

	SUBCASE("Normal mapping (0-1 => 0-1). Test for 2-segment linear fade, tracking if hitting 0 or 1, module changing "
			"value recalcs segments, switching knobsets") {
		p.map.min = 0;
		p.map.max = 1;

		// Starting (default) value
		CHECK(modules[0]->get_param(param_id) == 0.0f);

		// Starts in tracking mode by default
		CHECK(p.catchup.is_tracking() == true);

		// Moving knob tracks 1:1
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.2f);
		CHECK(modules[0]->get_param(param_id) == 0.25f);
		CHECK(p.catchup.is_tracking() == true);

		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.6f);
		CHECK(modules[0]->get_param(param_id) == 0.5f);
		CHECK(p.catchup.is_tracking() == true);

		// Switching knob sets, moving the module or phys knob, then switching back
		// will enter catchup mode
		active_knobset = 1;
		catchup_manager.reset(modules, knob_maps[active_knobset]);
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.2f);
		active_knobset = 0;
		catchup_manager.reset(modules, knob_maps[active_knobset]);
		CHECK(modules[0]->get_param(param_id) == 0.5f);
		CHECK(p.catchup.is_tracking() == false);

		// Tracks with 2 segment function:
		// knob 0-0.2 => module 0-0.5
		// knob 0.2-1 => module 0.5-1

		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.1f);
		CHECK(modules[0]->get_param(param_id) == 0.25f);
		CHECK(p.catchup.is_tracking() == false);

		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.2f);
		CHECK(modules[0]->get_param(param_id) == 0.5f);
		CHECK(p.catchup.is_tracking() == false);

		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.3f);
		CHECK(modules[0]->get_param(param_id) == 0.5); //would be 0.5625, snaps to 0.5
		CHECK(p.catchup.is_tracking() == false);

		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.45f);
		CHECK(modules[0]->get_param(param_id) == 0.75); //would be 0.65625, snaps to 0.75
		CHECK(p.catchup.is_tracking() == false);

		SUBCASE("Moving to 1 will end tracking") {
			catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 1.f);
			CHECK(modules[0]->get_param(param_id) == 1.f);
			CHECK(p.catchup.is_tracking() == true);
		}

		SUBCASE("Moving to 0 will end tracking") {
			catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.f);
			CHECK(modules[0]->get_param(param_id) == 0.f);
			CHECK(p.catchup.is_tracking() == true);
		}

		SUBCASE("Module moves its own knob => linear fade is re-calculated") {
			CHECK(p.catchup.is_tracking() == false);
			modules[0]->set_param(param_id, 0.25f);
			catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.4f);
			// inflection point is now at: knob 0.4, module 0.25
			CHECK(modules[0]->get_param(param_id) == 0.25f);
			CHECK(p.catchup.is_tracking() == false);

			// Switching knobsets, moving knob to the module's snapped value,
			// then switching knobsets back, it goes into 1:1 tracking mode
			active_knobset = 1;
			catchup_manager.reset(modules, knob_maps[active_knobset]);
			catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.25f);
			active_knobset = 0;
			catchup_manager.reset(modules, knob_maps[active_knobset]);
			CHECK(modules[0]->get_param(param_id) == 0.25f);
			CHECK(p.catchup.is_tracking() == true);

			catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.55f);
			CHECK(modules[0]->get_param(param_id) == 0.5f);
		}
	}
}
