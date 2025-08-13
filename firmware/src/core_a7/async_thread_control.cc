#include "async_thread_control.hh"
#include "console/pr_dbg.hh"
#include "debug.hh"
#include "drivers/timekeeper.hh"
#include "util/fixed_vector.hh"
#include <atomic>
#include <optional>

namespace MetaModule
{

namespace
{

constexpr int MAX_TASKS = 64;

static FixedVector<Async::Task, MAX_TASKS> tasks;

std::array<mdrivlib::Timekeeper, 2> async_task_timer;

std::array<std::atomic<bool>, 2> is_paused = {false, false};
std::array<std::atomic<bool>, 2> is_executing = {false, false};

uint32_t core() {
	uint32_t raw = __get_MPIDR();
	return (raw & 0b1) ? 1 : 0; //0 = CA7 Core 1, 1 = CA7 Core 2
}

std::optional<uint32_t> task_index(uint32_t id) {
	if (auto found = std::ranges::find(tasks, id, &Async::Task::id); found != tasks.end()) {
		return std::distance(tasks.begin(), found);
	} else {
		pr_warn("Cannot find task with id %u\n", (unsigned)id);
		return std::nullopt;
	}
}

} // namespace

std::optional<uint32_t> create_async_task(CoreProcessor *module) {
	if (auto id = tasks.push_back_for_overwrite(); id != tasks.max_size()) {
		tasks[id].module = module;
		tasks[id].enabled = false;
		tasks[id].core_id = 0;
		tasks[id].id = std::rand();
		return tasks[id].id;
	} else {
		pr_err("Maximum async tasks already created (%u) -- cannot add more\n", unsigned(tasks.max_size()));
		return std::nullopt;
	}
}

void destroy_async_task(uint32_t id) {
	if (auto idx = task_index(id)) {
		pr_trace("Erase task id %u (index %u)\n", (unsigned)id, (unsigned)(*idx));
		tasks.erase(*idx);
	}
}

void start_module_threads() {
	const uint32_t current_core = core();
	pr_trace("Start module threads on core %u\n", (unsigned)current_core);

	auto &task_runner = async_task_timer[current_core];

	mdrivlib::TimekeeperConfig task_config{
		.TIMx = current_core == 0 ? TIM7 : TIM6,
		.period_ns = mdrivlib::TimekeeperConfig::Hz(2000),
		.priority1 = 3,
		.priority2 = 3,
	};

	task_runner.init(task_config, [current_core = current_core]() {
		async_task_timer[current_core].pause();

		// current_core == 0 ? Debug::Pin2::high() : Debug::Pin1::high();

		is_executing[current_core].store(true, std::memory_order_seq_cst);
		for (auto &task : tasks) {
			if (task.enabled && task.core_id == current_core) {
				task.action();

				if (task.one_shot)
					task.enabled = false;
			}
			// Stop running tasks if another core sent a pause request while we were executing a task
			if (is_paused[current_core].load(std::memory_order_seq_cst))
				break;
		}
		is_executing[current_core].store(false, std::memory_order_seq_cst);

		// current_core == 0 ? Debug::Pin2::low() : Debug::Pin1::low();

		if (!is_paused[current_core].load(std::memory_order_seq_cst))
			async_task_timer[current_core].resume();
	});
	task_runner.start();
}

void pause_module_threads() {
	pause_module_threads(0);
	pause_module_threads(1);
}

bool is_any_thread_executing() {
	return is_executing[0].load(std::memory_order_acquire) || is_executing[1].load(std::memory_order_acquire);
}

void pause_module_threads(unsigned core_id) {
	is_paused[core_id & 1].store(true, std::memory_order_seq_cst);
	auto &task_runner = async_task_timer[core_id & 1];
	task_runner.pause();
}

void resume_module_threads() {
	resume_module_threads(0);
	resume_module_threads(1);
}

void resume_module_threads(unsigned core_id) {
	is_paused[core_id & 1].store(false, std::memory_order_seq_cst);
	auto &task_runner = async_task_timer[core_id & 1];
	task_runner.resume();
}

void kill_module_threads() {
	async_task_timer[0].stop();
	async_task_timer[1].stop();
}

void peg_task_to_core(uint32_t module_id, uint32_t core_id) {
	for (auto &task : tasks) {
		if (task.module && task.module->id == module_id) {
			pr_dbg("Peg task for module id %u: task id %u -> core %u\n", module_id, task.id, core_id);
			task.core_id = core_id;
		}
	}
}

Async::Task *get_task(unsigned id) {
	if (auto idx = task_index(id))
		return &tasks[*idx];
	else
		return nullptr;
}

} // namespace MetaModule
