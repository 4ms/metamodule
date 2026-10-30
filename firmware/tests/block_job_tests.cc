#include "doctest.h"
#include "coreproc_plugin/block_job_control.hh"
#include "threads/block_job.hh"

using namespace MetaModule;

namespace
{

struct TestModule : CoreProcessor {
	void update() override {
	}
	void set_param(int, float) override {
	}
	void set_input(int, float) override {
	}
	float get_output(int) const override {
		return 0;
	}
	void set_samplerate(float) override {
	}
};

// Stands in for Core 2's runner: counts wakeups, and the test runs jobs when it chooses.
// Declare it after the jobs, so it finishes them before they're destroyed
// (destroying a busy job waits for it)
unsigned notified = 0;
void count_notify() {
	notified++;
}

struct RunnerInstalled {
	RunnerInstalled() {
		notified = 0;
		BlockJobControl::set_runner_notify(count_notify);
	}
	~RunnerInstalled() {
		while (BlockJobControl::run_next_job())
			;
		BlockJobControl::set_runner_notify(nullptr);
	}
};

} // namespace

TEST_CASE("Without a runner, submit() runs the job in place") {
	TestModule module;
	unsigned runs = 0;
	BlockJob job{&module, [&runs] { runs++; }};

	CHECK(job.submit(32));
	CHECK(runs == 1);
	CHECK_FALSE(job.is_busy());
	CHECK(BlockJobControl::run_next_job() == nullptr);
}

TEST_CASE("A submitted job waits for the runner") {
	TestModule module;
	unsigned runs = 0;
	BlockJob job{&module, [&runs] { runs++; }};
	RunnerInstalled runner;

	CHECK(BlockJobControl::has_block_job(&module));

	CHECK(job.submit(32));
	CHECK(notified == 1);
	CHECK(runs == 0);
	CHECK(job.is_busy());

	SUBCASE("Can't submit again until it's done") {
		CHECK_FALSE(job.submit(32));
		CHECK(notified == 1);
	}

	CHECK(BlockJobControl::run_next_job() == &module);
	CHECK(runs == 1);
	CHECK_FALSE(job.is_busy());
	CHECK(BlockJobControl::run_next_job() == nullptr);

	CHECK(job.submit(32));
	CHECK(job.is_busy());
}

TEST_CASE("Frames before the deadline don't wait for the job") {
	TestModule module;
	BlockJob job{&module, [] {}};
	RunnerInstalled runner;

	CHECK(job.submit(4));
	// begin_frame() spins if a busy job is due, so returning at all means it didn't wait
	for (auto i = 0; i < 3; i++)
		BlockJobControl::begin_frame();
	CHECK(job.is_busy());
}

TEST_CASE("The runner takes the job that's due soonest") {
	TestModule module_a;
	TestModule module_b;
	BlockJob job_a{&module_a, [] {}};
	BlockJob job_b{&module_b, [] {}};
	RunnerInstalled runner;

	CHECK(job_a.submit(64));
	CHECK(job_b.submit(16));

	CHECK(BlockJobControl::run_next_job() == &module_b);
	CHECK(BlockJobControl::run_next_job() == &module_a);
	CHECK(BlockJobControl::run_next_job() == nullptr);
}

TEST_CASE("A destroyed job frees its slot") {
	TestModule module;
	{
		BlockJob job{&module, [] {}};
		CHECK(BlockJobControl::has_block_job(&module));
	}
	CHECK_FALSE(BlockJobControl::has_block_job(&module));
}
