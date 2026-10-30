#include "threads/block_job.hh"
#include "block_job_control.hh"
#include "console/pr_dbg.hh"
#include <array>
#include <atomic>
#include <cstdint>
#include <optional>

namespace MetaModule
{

namespace
{

enum class State : uint32_t { Free, Idle, Submitted, Running };

struct Slot {
	std::atomic<State> state{State::Free};
	CoreProcessor *module = nullptr;
	Callback work;
	uint32_t due_frame = 0;
};

constexpr unsigned MaxJobs = 16;
std::array<Slot, MaxJobs> slots;

// Number of jobs submitted and not yet finished, so begin_frame() can skip
// checking the slots when there's nothing to wait for
std::atomic<uint32_t> num_busy{0};

// Counts frames, for working out when jobs are due. Written by Core 1 at the
// start of each frame, before either core runs that frame's modules
std::atomic<uint32_t> frame{0};

std::atomic<void (*)()> runner_notify{nullptr};

bool is_due(uint32_t due_frame, uint32_t now) {
	return (int32_t)(now - due_frame) >= 0;
}

bool in_progress(State state) {
	return state == State::Submitted || state == State::Running;
}

void finish(Slot &slot) {
	slot.state.store(State::Idle, std::memory_order_release);
	num_busy.fetch_sub(1, std::memory_order_release);
}

} // namespace

struct BlockJob::Internal {
	std::optional<unsigned> slot_idx;

	// Only used if there was no free slot
	Callback work_in_place;
};

BlockJob::BlockJob(CoreProcessor *module, Callback &&work)
	: internal{std::make_unique<Internal>()} {
	for (auto i = 0u; auto &slot : slots) {
		if (slot.state.load(std::memory_order_acquire) == State::Free) {
			slot.module = module;
			slot.work = std::move(work);
			slot.state.store(State::Idle, std::memory_order_release);
			internal->slot_idx = i;
			return;
		}
		i++;
	}
	pr_err("Maximum block jobs already created (%u) -- job will run in place\n", MaxJobs);
	internal->work_in_place = std::move(work);
}

BlockJob::~BlockJob() {
	if (internal->slot_idx) {
		auto &slot = slots[*internal->slot_idx];

		// The runner preempts whatever destroys modules (the GUI on Core 2, or
		// Core 1), so a job in progress always gets to finish
		while (in_progress(slot.state.load(std::memory_order_acquire)))
			;

		slot.work = Callback{};
		slot.module = nullptr;
		slot.state.store(State::Free, std::memory_order_release);
	}
}

bool BlockJob::submit(unsigned frames) {
	if (!internal->slot_idx) {
		internal->work_in_place();
		return true;
	}

	auto &slot = slots[*internal->slot_idx];
	if (slot.state.load(std::memory_order_acquire) != State::Idle)
		return false;

	auto notify = runner_notify.load(std::memory_order_acquire);
	if (!notify) {
		slot.work();
		return true;
	}

	slot.due_frame = frame.load(std::memory_order_relaxed) + frames;
	num_busy.fetch_add(1, std::memory_order_relaxed);
	slot.state.store(State::Submitted, std::memory_order_release);
	notify();
	return true;
}

bool BlockJob::is_busy() const {
	return internal->slot_idx && in_progress(slots[*internal->slot_idx].state.load(std::memory_order_acquire));
}

namespace BlockJobControl
{

void begin_frame() {
	auto now = frame.load(std::memory_order_relaxed) + 1;
	frame.store(now, std::memory_order_relaxed);

	if (num_busy.load(std::memory_order_acquire) == 0)
		return;

	for (auto &slot : slots) {
		if (!in_progress(slot.state.load(std::memory_order_acquire)))
			continue;

		if (is_due(slot.due_frame, now)) {
			while (in_progress(slot.state.load(std::memory_order_acquire)))
				;
		}
	}
}

CoreProcessor *run_next_job() {
	if (num_busy.load(std::memory_order_acquire) == 0)
		return nullptr;

	// Earliest deadline first
	Slot *next = nullptr;
	for (auto &slot : slots) {
		if (slot.state.load(std::memory_order_acquire) != State::Submitted)
			continue;
		if (!next || (int32_t)(slot.due_frame - next->due_frame) < 0)
			next = &slot;
	}

	if (!next)
		return nullptr;

	// Only the runner moves a job out of Submitted, so this can't race
	next->state.store(State::Running, std::memory_order_relaxed);
	next->work();
	auto module = next->module;
	finish(*next);
	return module;
}

void set_runner_notify(void (*notify)()) {
	runner_notify.store(notify, std::memory_order_release);
}

bool has_block_job(CoreProcessor const *module) {
	for (auto &slot : slots) {
		if (slot.state.load(std::memory_order_acquire) != State::Free && slot.module == module)
			return true;
	}
	return false;
}

} // namespace BlockJobControl

} // namespace MetaModule
