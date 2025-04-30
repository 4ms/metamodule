#include "CoreModules/CoreProcessor.hh"
#include "doctest.h"
#include "params/catchup_manager.hh"
#include "params/catchup_param.hh"
#include <memory>

struct TestModule : CoreProcessor {
	std::array<float, 8> params{};

	void set_param(int param_id, float val) override {
		if (param_id > 0 && param_id < (int)params.size())
			params[param_id] = val;
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
	modules[0] = std::make_unique<TestModule>();

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
	p.catchup.set_mode(CatchupParam::Mode::ResumeOnEqual);

	SUBCASE("Normal mapping (0-1 => 0-1). Test for pickup on equal, module changing value, switching knobsets") {
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

		// Moving knob to 0, then to a new value makes it track
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.0f);
		CHECK(modules[0]->get_param(param_id) == 0.0f);
		CHECK(p.catchup.is_tracking() == true);

		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.3f);
		CHECK(modules[0]->get_param(param_id) == 0.3f);
		CHECK(p.catchup.is_tracking() == true);

		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.4f);
		CHECK(modules[0]->get_param(param_id) == 0.4f);
		CHECK(p.catchup.is_tracking() == true);

		// Module changes own value -> stop tracking until knob value matches
		modules[0]->set_param(param_id, 0.8f);
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.5f);
		CHECK(modules[0]->get_param(param_id) == 0.8f);
		CHECK(p.catchup.is_tracking() == false);

		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.7f);
		CHECK(modules[0]->get_param(param_id) == 0.8f);
		CHECK(p.catchup.is_tracking() == false);

		//.79999 vs 0.8, within tolerance -> start tracking
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.79999f);
		CHECK(modules[0]->get_param(param_id) == 0.79999f);
		CHECK(p.catchup.is_tracking() == true);

		//User switches knobset, moves knob (which is mapped to something else)
		active_knobset = 1;
		catchup_manager.reset(modules, knob_maps[active_knobset]);
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.2f);

		// User switches knobset back -> stop tracking
		active_knobset = 0;
		catchup_manager.reset(modules, knob_maps[active_knobset]);
		CHECK(modules[0]->get_param(param_id) == 0.79999f);
		CHECK(p.catchup.is_tracking() == false);

		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.2f);
		CHECK(p.catchup.is_tracking() == false);

		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.3f);
		CHECK(p.catchup.is_tracking() == false);

		// Move knob close to module value -> start tracking again
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.80001f);
		CHECK(modules[0]->get_param(param_id) == 0.80001f);
		CHECK(p.catchup.is_tracking() == true);

		// User switches knobset and then back again, without moving knob -> still tracking
		active_knobset = 1;
		catchup_manager.reset(modules, knob_maps[active_knobset]);
		active_knobset = 0;
		catchup_manager.reset(modules, knob_maps[active_knobset]);
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.80001f);
		CHECK(p.catchup.is_tracking() == true);

		// Module changes own value (so that tracking mode stops)
		modules[0]->set_param(param_id, 0.1f);
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.80001f);
		CHECK(modules[0]->get_param(param_id) == 0.1f);
		CHECK(p.catchup.is_tracking() == false);

		// User switches knobset and then back again, without moving knob -> still not tracking
		active_knobset = 1;
		catchup_manager.reset(modules, knob_maps[active_knobset]);
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.80001f);
		active_knobset = 0;
		catchup_manager.reset(modules, knob_maps[active_knobset]);
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.80001f);
		CHECK(p.catchup.is_tracking() == false);
		CHECK(modules[0]->get_param(param_id) == 0.1f);
	}

	SUBCASE("Inverted partial range mapping. Test for pickup on equal, module changing value, switching knobsets") {
		p.map.min = 0.9f; // knob at 0 => module set to 0.9
		p.map.max = 0.4f; // knob at 1 => module set to 0.4

		// Starting (default) value
		CHECK(modules[0]->get_param(param_id) == 0.0f);
		CHECK(p.catchup.is_tracking() == false);

		// Moving knob has no effect
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.2f);
		CHECK(modules[0]->get_param(param_id) == 0.0f);
		CHECK(p.catchup.is_tracking() == false);

		// Even moving to min or max (1.0) has no effect, because module value is out of range
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 1.0f);
		CHECK(modules[0]->get_param(param_id) == 0.0f);
		CHECK(p.catchup.is_tracking() == false);
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.0f);
		CHECK(modules[0]->get_param(param_id) == 0.0f);
		CHECK(p.catchup.is_tracking() == false);

		// Now let's have the module set its value to be in our range (0.4 is knob at 1)
		// It will now track
		modules[0]->set_param(param_id, 0.5f);
		CHECK(p.catchup.is_tracking() == false); //Note: is_tracking() does not update until set_panel_param is called!
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.8f);
		CHECK(modules[0]->get_param(param_id) == doctest::Approx(0.5f));
		CHECK(p.catchup.is_tracking() == true);

		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.4f);
		CHECK(modules[0]->get_param(param_id) == doctest::Approx(0.7f)); //knob 0.4 maps to module 0.7
		CHECK(p.catchup.is_tracking() == true);

		// Module changes own value -> stop tracking until knob value matches
		modules[0]->set_param(param_id, 0.8f);
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.5f);
		CHECK(modules[0]->get_param(param_id) == 0.8f);
		CHECK(p.catchup.is_tracking() == false);

		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.7f);
		CHECK(modules[0]->get_param(param_id) == 0.8f);
		CHECK(p.catchup.is_tracking() == false);

		//.79995 vs 0.8 (which is what 0.2001 maps to) is within tolerance -> start tracking
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.2001f);
		CHECK(modules[0]->get_param(param_id) == doctest::Approx(0.79995));
		CHECK(p.catchup.is_tracking() == true);

		//User switches knobset, moves knob (which is mapped to something else)
		active_knobset = 1;
		catchup_manager.reset(modules, knob_maps[active_knobset]);
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.7f);

		// User switches knobset back -> stop tracking
		active_knobset = 0;
		catchup_manager.reset(modules, knob_maps[active_knobset]);
		CHECK(modules[0]->get_param(param_id) == doctest::Approx(0.79995f));
		CHECK(p.catchup.is_tracking() == false);

		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.6f);
		CHECK(p.catchup.is_tracking() == false);

		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.5f);
		CHECK(p.catchup.is_tracking() == false);

		// Move knob close to module value -> start tracking again
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.19999f);
		CHECK(modules[0]->get_param(param_id) == doctest::Approx(0.800005f));
		CHECK(p.catchup.is_tracking() == true);

		// User switches knobset and then back again, without moving knob -> still tracking
		active_knobset = 1;
		catchup_manager.reset(modules, knob_maps[active_knobset]);
		active_knobset = 0;
		catchup_manager.reset(modules, knob_maps[active_knobset]);
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.19999f);
		CHECK(p.catchup.is_tracking() == true);

		// Module changes own value (so that tracking mode stops)
		modules[0]->set_param(param_id, 0.1f);
		// Note: is_tracking() does not update until set_panel_param is called
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.19999f);
		CHECK(modules[0]->get_param(param_id) == 0.1f);
		CHECK(p.catchup.is_tracking() == false);

		// User switches knobset and then back again, without moving knob -> still not tracking
		active_knobset = 1;
		catchup_manager.reset(modules, knob_maps[active_knobset]);
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.19999f);
		active_knobset = 0;
		catchup_manager.reset(modules, knob_maps[active_knobset]);
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.19999f);
		CHECK(p.catchup.is_tracking() == false);
		CHECK(modules[0]->get_param(param_id) == 0.1f);
	}
}

TEST_CASE("Basic usage of ResumeOnMotion") {
	using namespace MetaModule;

	std::array<std::unique_ptr<CoreProcessor>, 1> modules;
	modules[0] = std::make_unique<TestModule>();

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
		CHECK(modules[0]->get_param(param_id) == 0.2f);
		CHECK(p.catchup.is_tracking() == true);

		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.4f);
		CHECK(modules[0]->get_param(param_id) == 0.4f);
		CHECK(p.catchup.is_tracking() == true);

		// Module changes own value -> immediately tracks knob
		// technically, this is not "resume on motion" since the knob did not move
		// but the engine only calls set_panel_param() if the knob changed values, so
		// effecively it works as "resume on motion"
		modules[0]->set_param(param_id, 0.8f);
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.4f);
		CHECK(modules[0]->get_param(param_id) == 0.4f);
		CHECK(p.catchup.is_tracking() == true);

		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.7f);
		CHECK(modules[0]->get_param(param_id) == 0.7f);
		CHECK(p.catchup.is_tracking() == true);

		//User switches knobset, moves knob (which is mapped to something else)
		active_knobset = 1;
		catchup_manager.reset(modules, knob_maps[active_knobset]);
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.2f);
		// User switches knobset back -> stop tracking
		active_knobset = 0;
		catchup_manager.reset(modules, knob_maps[active_knobset]);
		CHECK(modules[0]->get_param(param_id) == 0.7f);
		CHECK(p.catchup.is_tracking() == false);

		// Starts tracking when knob moved
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.3f);
		CHECK(modules[0]->get_param(param_id) == 0.3f);
		CHECK(p.catchup.is_tracking() == true);
	}

	SUBCASE("Inverted partial mapping. Test for pickup, module changing value, switching knobsets") {
		//0 to 1 => .9 to .4
		p.map.min = 0.9f;
		p.map.max = 0.4f;
		auto map = [&](float knob) {
			return 0.9f - knob / 2.f;
		};

		// Starting (default) value
		CHECK(modules[0]->get_param(param_id) == 0.0f);
		CHECK(p.catchup.is_tracking() == false);

		// Moving knob has immediate effect
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.2f);
		CHECK(modules[0]->get_param(param_id) == map(0.2f));
		CHECK(p.catchup.is_tracking() == true);

		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.4f);
		CHECK(modules[0]->get_param(param_id) == map(0.4f));
		CHECK(p.catchup.is_tracking() == true);

		// Module changes own value -> immediately tracks knob
		// technically, this is not "resume on motion" since the knob did not move
		// but the engine only calls set_panel_param() if the knob changed values, so
		// effecively it works as "resume on motion"
		modules[0]->set_param(param_id, 0.8f);
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.4f);
		CHECK(modules[0]->get_param(param_id) == doctest::Approx(map(0.4f)));
		CHECK(p.catchup.is_tracking() == true);

		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.7f);
		CHECK(modules[0]->get_param(param_id) == doctest::Approx(map(0.7f)));
		CHECK(p.catchup.is_tracking() == true);

		//User switches knobset, moves knob (which is mapped to something else)
		active_knobset = 1;
		catchup_manager.reset(modules, knob_maps[active_knobset]);
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.2f);
		// User switches knobset back -> stop tracking
		active_knobset = 0;
		catchup_manager.reset(modules, knob_maps[active_knobset]);
		CHECK(modules[0]->get_param(param_id) == doctest::Approx(map(0.7f)));
		CHECK(p.catchup.is_tracking() == false);

		// Starts tracking when knob moved
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.3f);
		CHECK(modules[0]->get_param(param_id) == doctest::Approx(map(0.3f)));
		CHECK(p.catchup.is_tracking() == true);
	}
}

TEST_CASE("Basic usage of LinearFade") {
	using namespace MetaModule;

	std::array<std::unique_ptr<CoreProcessor>, 1> modules;
	modules[0] = std::make_unique<TestModule>();

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
		CHECK(modules[0]->get_param(param_id) == 0.2f);
		CHECK(p.catchup.is_tracking() == true);

		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.6f);
		CHECK(modules[0]->get_param(param_id) == 0.6f);
		CHECK(p.catchup.is_tracking() == true);

		// Switching knob sets, moving the module or phys knob, then switching back
		// will enter catchup mode
		active_knobset = 1;
		catchup_manager.reset(modules, knob_maps[active_knobset]);
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.2f);
		active_knobset = 0;
		catchup_manager.reset(modules, knob_maps[active_knobset]);
		CHECK(modules[0]->get_param(param_id) == 0.6f);
		CHECK(p.catchup.is_tracking() == false);

		// Tracks with 2 segment function:
		// knob 0-0.2 => module 0-0.6
		// knob 0.2-1 => module 0.6-1

		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.1f);
		CHECK(modules[0]->get_param(param_id) == 0.3f);
		CHECK(p.catchup.is_tracking() == false);

		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.2f);
		CHECK(modules[0]->get_param(param_id) == 0.6f);
		CHECK(p.catchup.is_tracking() == false);

		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.3f);
		CHECK(modules[0]->get_param(param_id) == doctest::Approx(0.65));
		CHECK(p.catchup.is_tracking() == false);

		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.4f);
		CHECK(modules[0]->get_param(param_id) == doctest::Approx(0.7));
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
			modules[0]->set_param(param_id, 0.2f);
			catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.4f);
			// inflection point is now at: knob 0.4, module 0.2
			CHECK(modules[0]->get_param(param_id) == doctest::Approx(0.2f));
			CHECK(p.catchup.is_tracking() == false);

			// Switching knobsets and then back, with the knob set to the module value
			// is in tracking mode
			active_knobset = 1;
			catchup_manager.reset(modules, knob_maps[active_knobset]);
			catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.2f);
			active_knobset = 0;
			catchup_manager.reset(modules, knob_maps[active_knobset]);
			CHECK(modules[0]->get_param(param_id) == doctest::Approx(0.2f));
			CHECK(p.catchup.is_tracking() == true);

			catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.3f);
			CHECK(modules[0]->get_param(param_id) == doctest::Approx(0.3f));
		}
	}

	SUBCASE("Inverted mapping. Test for 2-segment linear fade, tracking if hitting 0 or 1, module changing "
			"value recalcs segments, switching knobsets") {
		p.map.min = 0.9f;
		p.map.max = 0.4f;
		auto map = [&](float knob) {
			return 0.9f - knob / 2.f;
		};

		// Starting (default) value
		CHECK(modules[0]->get_param(param_id) == 0.0f);

		// Starts in tracking mode by default
		CHECK(p.catchup.is_tracking() == true);

		// Moving knob tracks
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.2f);
		CHECK(modules[0]->get_param(param_id) == map(0.2f));
		CHECK(p.catchup.is_tracking() == true);

		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.4f);
		CHECK(modules[0]->get_param(param_id) == map(0.4f));
		CHECK(p.catchup.is_tracking() == true);

		// Switching knob sets, moving the phys knob, then switching back
		// will enter catchup mode
		active_knobset = 1;
		catchup_manager.reset(modules, knob_maps[active_knobset]);
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.8f);
		active_knobset = 0;
		catchup_manager.reset(modules, knob_maps[active_knobset]);
		CHECK(modules[0]->get_param(param_id) == 0.7f); //map(0.4) == 0.7
		CHECK(p.catchup.is_tracking() == false);

		// Tracks with 2 segment function:
		// inflection point is at knob@0.8 (mapped val = 0.7), module@ 0.7

		// above 0.8: knob moves +0.05 => module moves -0.035
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.85f);
		CHECK(modules[0]->get_param(param_id) == doctest::Approx(0.665f));
		CHECK(p.catchup.is_tracking() == false);

		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.9f);
		CHECK(modules[0]->get_param(param_id) == doctest::Approx(0.630f));
		CHECK(p.catchup.is_tracking() == false);

		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.95f);
		CHECK(modules[0]->get_param(param_id) == doctest::Approx(0.595f));
		CHECK(p.catchup.is_tracking() == false);

		// below 0.8: knob moves -0.05 => module moves +0.030
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.7f);
		CHECK(modules[0]->get_param(param_id) == doctest::Approx(0.73f));
		CHECK(p.catchup.is_tracking() == false);

		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.6f);
		CHECK(modules[0]->get_param(param_id) == doctest::Approx(0.76));
		CHECK(p.catchup.is_tracking() == false);

		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.5f);
		CHECK(modules[0]->get_param(param_id) == doctest::Approx(0.79));
		CHECK(p.catchup.is_tracking() == false);

		//Module moves its own knob => linear fade is re-calculated
		CHECK(p.catchup.is_tracking() == false);
		modules[0]->set_param(param_id, 0.2f);
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.5f);

		// inflection point is now at: knob 0.4, module 0.2
		CHECK(modules[0]->get_param(param_id) == doctest::Approx(0.2f));
		CHECK(p.catchup.is_tracking() == false);

		// knob moves +0.1, module moves -0.015385
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.6f);
		CHECK(modules[0]->get_param(param_id) == doctest::Approx(0.2 - 0.015385));
		CHECK(p.catchup.is_tracking() == false);

		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.7f);
		CHECK(modules[0]->get_param(param_id) == doctest::Approx(0.2 - 0.015385 - 0.015385));
		CHECK(p.catchup.is_tracking() == false);

		// knob moves -0.1, module moves 0.114286
		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.4f);
		CHECK(modules[0]->get_param(param_id) == doctest::Approx(0.2 + 0.114286));
		CHECK(p.catchup.is_tracking() == false);

		catchup_manager.set_panel_param(modules, knob_maps[active_knobset], panel_knob, 0.3f);
		CHECK(modules[0]->get_param(param_id) == doctest::Approx(0.2 + 0.114286 + 0.114286));
		CHECK(p.catchup.is_tracking() == false);
	}
}
