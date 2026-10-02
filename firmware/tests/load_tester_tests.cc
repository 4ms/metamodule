#include "doctest.h"
#include "load_test/tester.hh"
#include "stubs/test_module.hh"
#include <chrono>
#include <thread>

// ModuleLoadTester: one-time work at the start (e.g. a module building tables when its params
// are first set) is reported as first_run_time, and doesn't count towards the block loads.
// Work that repeats is still caught by the block loads.

namespace
{

using namespace std::chrono_literals;

// Spike once, a little after the test first sets the params. This is like Befaco Random8,
// which re-creates its random sequences on its next control update after a param changes.
// (Note: the player runs modules while loading a patch, so the spike can't be at a fixed update)
struct OneTimeSpike : TestModule {
	unsigned updates_until_spike = 0;

	void set_param(int param_id, float val) override {
		TestModule::set_param(param_id, val);
		if (updates_until_spike == 0)
			updates_until_spike = 30;
	}

	void update() override {
		if (updates_until_spike > 0 && --updates_until_spike == 0)
			std::this_thread::sleep_for(2ms);
	}

	static std::unique_ptr<CoreProcessor> create() {
		return std::make_unique<OneTimeSpike>();
	}
};

// Spike every 512 samples (like a module that processes in blocks)
struct PeriodicSpike : TestModule {
	unsigned num_updates = 0;

	void update() override {
		if (++num_updates % 512 == 0)
			std::this_thread::sleep_for(2ms);
	}

	static std::unique_ptr<CoreProcessor> create() {
		return std::make_unique<PeriodicSpike>();
	}
};

// One knob, so the test sets a param
struct SpikeModuleInfo : MetaModule::ModuleInfoBase {
	static constexpr uint32_t width_hp = 4;
	static constexpr std::array<MetaModule::Element, 1> Elements{{MetaModule::Knob{}}};
};

const bool registered =
	MetaModule::ModuleFactory::registerModuleType(
		"TestOneTimeSpike", OneTimeSpike::create, MetaModule::ModuleInfoView::makeView<SpikeModuleInfo>(), "") &&
	MetaModule::ModuleFactory::registerModuleType(
		"TestPeriodicSpike", PeriodicSpike::create, MetaModule::ModuleInfoView::makeView<SpikeModuleInfo>(), "") &&
	MetaModule::ModuleFactory::registerModuleType(
		"TestNoSpike", TestModule::create, MetaModule::ModuleInfoView::makeView<SpikeModuleInfo>(), "");

using namespace MetaModule;

// Block load as a fraction of the time the block takes to play
float block_load(ModuleLoadTester::Measurements const &m) {
	constexpr float sampletime_us = 1'000'000.f / 48000.f;
	return m.average_run_time / sampletime_us;
}

} // namespace

TEST_CASE("ModuleLoadTester: one-time spike is reported as first run time, not block load") {
	REQUIRE(registered);

	PatchPlayer player;

	ModuleLoadTester tester{player, "TestOneTimeSpike"};
	auto m = tester.run_test(32, KnobTestType::AllStill, JackTestType::NonePatched);

	// The 2ms spike is the longest sample during the first run
	CHECK(m.first_run_time >= 2000);

	// ...and the blocks after the first run don't include it. Without the first run, a 2ms
	// spike in a 32-sample block would be a load of 300%
	CHECK(block_load(m) < 0.5f);
}

TEST_CASE("ModuleLoadTester: a spike that repeats is reported in the block load") {
	REQUIRE(registered);

	PatchPlayer player;

	ModuleLoadTester tester{player, "TestPeriodicSpike"};
	auto m = tester.run_test(32, KnobTestType::AllStill, JackTestType::NonePatched);

	CHECK(m.first_run_time >= 2000);

	// The worst 32-sample block has a 2ms spike: 2000us / (32 * 20.8us) = 300%
	CHECK(block_load(m) > 2.5f);
}

TEST_CASE("ModuleLoadTester: no spikes") {
	REQUIRE(registered);

	PatchPlayer player;

	ModuleLoadTester tester{player, "TestNoSpike"};
	auto m = tester.run_test(32, KnobTestType::AllStill, JackTestType::NonePatched);

	CHECK(m.first_run_time < 1000);
	CHECK(block_load(m) < 0.5f);
}
