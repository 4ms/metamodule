#include "CoreModules/CoreProcessor.hh"
#include "audio/panel_encoders.hh"
#include "doctest.h"
#include "params/catchup_manager.hh"
#include <cmath>
#include <memory>
#include <vector>

// Param 1-3: continuous
// Param 4: the module rounds the values it's set to N/4 (but it isn't declared as discrete)
// Param 5: discrete, 5 positions (the mapping's num_pos says so)
struct EncoderTestModule : CoreProcessor {
	std::array<float, 8> params{};

	void set_param(int param_id, float val) override {
		if (param_id == 4)
			params[param_id] = std::round(val * 4.f) / 4.f;
		else if (param_id > 0 && param_id < (int)params.size())
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

TEST_CASE("Panel encoders step their mapped params") {
	using namespace MetaModule;

	std::array<std::unique_ptr<CoreProcessor>, 1> modules;
	modules[0] = std::make_unique<EncoderTestModule>();
	auto &module = *modules[0];

	CatchupManager catchup_manager;
	ParamSet knob_maps;

	unsigned panel_knob = 2;

	auto add_map = [&](uint16_t param_id, float min, float max, uint16_t num_pos = 0) -> MappedParam & {
		auto &p = knob_maps[panel_knob].emplace_back();
		p.map.panel_knob_id = panel_knob;
		p.map.module_id = 0;
		p.map.param_id = param_id;
		p.map.min = min;
		p.map.max = max;
		p.num_pos = num_pos;
		return p;
	};

	auto turn = [&](int clicks, float step = 0.01f) {
		catchup_manager.step_panel_encoder(modules, knob_maps, panel_knob, clicks, step);
	};

	SUBCASE("Steps from the param's value, and stops at the ends") {
		add_map(1, 0, 1);
		module.set_param(1, 0.5f);

		turn(3);
		CHECK(module.get_param(1) == doctest::Approx(0.53f));
		turn(-5);
		CHECK(module.get_param(1) == doctest::Approx(0.48f));

		turn(100, 0.05f);
		CHECK(module.get_param(1) == 1.f);
		turn(-127, 0.05f);
		CHECK(module.get_param(1) == 0.f);
	}

	SUBCASE("Steps in the map's range, and its direction") {
		add_map(1, 0.2f, 0.6f);
		add_map(2, 1.f, 0.f);
		module.set_param(1, 0.4f);
		module.set_param(2, 0.5f);

		turn(10);
		CHECK(module.get_param(1) == doctest::Approx(0.44f));
		CHECK(module.get_param(2) == doctest::Approx(0.4f));

		// A value outside the map's range moves into it
		module.set_param(1, 0.9f);
		turn(1);
		CHECK(module.get_param(1) == doctest::Approx(0.6f));
	}

	SUBCASE("Steps from a value the module was given by something else") {
		add_map(1, 0, 1);
		module.set_param(1, 0.5f);

		turn(1);
		CHECK(module.get_param(1) == doctest::Approx(0.51f));

		module.set_param(1, 0.9f);
		turn(1);
		CHECK(module.get_param(1) == doctest::Approx(0.91f));
	}

	SUBCASE("A module that rounds its values can still be stepped in small steps") {
		add_map(4, 0, 1);
		module.set_param(4, 0.5f);

		// 0.5 + 0.12 rounds to 0.5, but 0.5 + 0.13 rounds to 0.75
		for (int i = 0; i < 12; i++)
			turn(1);
		CHECK(module.get_param(4) == 0.5f);
		turn(1);
		CHECK(module.get_param(4) == 0.75f);

		// And back down: 0.63 - 0.01 rounds to 0.5
		turn(-1);
		CHECK(module.get_param(4) == 0.5f);
	}

	SUBCASE("A discrete param steps one position per click, whatever the step size") {
		auto &p = add_map(5, 0, 1, 5);
		module.set_param(5, 0.5f);

		turn(1, 0.05f);
		CHECK(module.get_param(5) == doctest::Approx(0.75f));
		turn(-3, 0.01f);
		CHECK(module.get_param(5) == doctest::Approx(0.f));
		turn(-1);
		CHECK(module.get_param(5) == doctest::Approx(0.f));

		// Reversed map: clockwise goes down
		p.map.min = 1;
		p.map.max = 0;
		module.set_param(5, 0.5f);
		turn(1);
		CHECK(module.get_param(5) == doctest::Approx(0.25f));
	}

	SUBCASE("Every param mapped to the encoder steps") {
		add_map(1, 0, 1);
		add_map(2, 0, 0.5f);
		module.set_param(1, 0.5f);
		module.set_param(2, 0.25f);

		turn(10);
		CHECK(module.get_param(1) == doctest::Approx(0.6f));
		CHECK(module.get_param(2) == doctest::Approx(0.3f));
	}

	SUBCASE("Other encoders' maps don't move") {
		add_map(1, 0, 1);
		module.set_param(1, 0.5f);

		catchup_manager.step_panel_encoder(modules, knob_maps, panel_knob + 1, 5, 0.01f);
		CHECK(module.get_param(1) == 0.5f);

		// Out of range: ignored
		catchup_manager.step_panel_encoder(modules, knob_maps, PanelDef::NumKnobs, 5, 0.01f);
		CHECK(module.get_param(1) == 0.5f);
	}
}

namespace
{
struct StepRecorder {
	struct Step {
		unsigned panel_knob_id;
		int clicks;
		float step;
	};
	std::vector<Step> steps;

	void step_panel_encoder(unsigned panel_knob_id, int clicks, float step) {
		steps.push_back({panel_knob_id, clicks, step});
	}
};
} // namespace

TEST_CASE("Panel encoder acceleration") {
	using namespace MetaModule;

	using Encoders = PanelEncoders<4>;

	SUBCASE("Step size goes from 1% per click (slow) to 5% (fast)") {
		CHECK(Encoders::step_size(1.f) == doctest::Approx(0.01f));
		CHECK(Encoders::step_size(0.080f) == doctest::Approx(0.01f));
		CHECK(Encoders::step_size(0.050f) == doctest::Approx(0.03f));
		CHECK(Encoders::step_size(0.020f) == doctest::Approx(0.05f));
		CHECK(Encoders::step_size(0.001f) == doctest::Approx(0.05f));
	}

	SUBCASE("The time between clicks sets the step size") {
		Encoders encoders;
		StepRecorder player;
		ParamsState param_state{};
		param_state.clear();

		constexpr uint32_t SampleRate = 48000;
		constexpr uint32_t BlockFrames = 48; // 1ms blocks

		EncoderClicks<4> none{};
		EncoderClicks<4> one_click{};
		one_click.clicks[1] = 1;

		auto blocks = [&](unsigned n) {
			for (unsigned i = 0; i < n; i++)
				encoders.process(none, BlockFrames, SampleRate, player, param_state);
		};

		// First click: slow
		encoders.process(one_click, BlockFrames, SampleRate, player, param_state);
		REQUIRE(player.steps.size() == 1);
		CHECK(player.steps[0].panel_knob_id == 1);
		CHECK(player.steps[0].clicks == 1);
		CHECK(player.steps[0].step == doctest::Approx(0.01f));
		CHECK(param_state.knobs[1].changed);
		CHECK_FALSE(param_state.knobs[0].changed);

		// 50ms later: in between
		blocks(49);
		encoders.process(one_click, BlockFrames, SampleRate, player, param_state);
		REQUIRE(player.steps.size() == 2);
		CHECK(player.steps[1].step == doctest::Approx(0.03f));

		// 20ms later: fast
		blocks(19);
		encoders.process(one_click, BlockFrames, SampleRate, player, param_state);
		REQUIRE(player.steps.size() == 3);
		CHECK(player.steps[2].step == doctest::Approx(0.05f));

		// Four clicks in one block, 80ms after the last: 20ms per click, so fast
		EncoderClicks<4> four_ccw{};
		four_ccw.clicks[1] = -4;
		blocks(79);
		encoders.process(four_ccw, BlockFrames, SampleRate, player, param_state);
		REQUIRE(player.steps.size() == 4);
		CHECK(player.steps[3].clicks == -4);
		CHECK(player.steps[3].step == doctest::Approx(0.05f));
	}

	SUBCASE("A click keeps the GUI's changed flag set for 100ms, with or without a patch") {
		Encoders encoders;
		StepRecorder player;
		ParamsState param_state{};
		param_state.clear();

		constexpr uint32_t SampleRate = 48000;
		constexpr uint32_t BlockFrames = 48; // 1ms blocks

		EncoderClicks<4> none{};
		EncoderClicks<4> one_click{};
		one_click.clicks[2] = -1;

		// As the audio loop does: the flags are cleared after each block
		auto block = [&](EncoderClicks<4> const &enc, bool playing) {
			param_state.reset_change_flags();
			if (playing)
				encoders.process(enc, BlockFrames, SampleRate, player, param_state);
			else
				encoders.mark_moved(enc, BlockFrames, SampleRate, param_state);
			return param_state.knobs[2].changed;
		};

		for (bool playing : {true, false}) {
			CAPTURE(playing);
			CHECK_FALSE(block(none, playing));

			CHECK(block(one_click, playing));
			for (unsigned i = 1; i < 100; i++)
				CHECK(block(none, playing));
			CHECK_FALSE(block(none, playing));
			CHECK_FALSE(param_state.knobs[1].changed);
		}

		// Without a patch, nothing steps
		CHECK(player.steps.size() == 1);
	}
}
