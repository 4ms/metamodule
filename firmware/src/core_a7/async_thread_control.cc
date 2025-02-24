#include "async_thread_control.hh"
#include "console/pr_dbg.hh"
#include "debug.hh"
#include "drivers/timekeeper.hh"
#include "util/fixed_vector.hh"
#include <optional>

namespace MetaModule
{

namespace
{

constexpr int MAX_TASKS = 64;

static FixedVector<Async::Task, MAX_TASKS> tasks;

mdrivlib::Timekeeper async_task_core0;
mdrivlib::Timekeeper async_task_core1;

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

	auto &task_runner = current_core == 1 ? async_task_core1 : async_task_core0;

	mdrivlib::TimekeeperConfig task_config{
		.TIMx = current_core == 0 ? TIM7 : TIM6,
		.period_ns = mdrivlib::TimekeeperConfig::Hz(2000),
		.priority1 = 3,
		.priority2 = 3,
	};

	task_runner.init(task_config, [=]() {
		// if (current_core == 0)
		// 	Debug::Pin2::high();
		// else
		// 	Debug::Pin1::high();

		for (auto &task : tasks) {
			if (task.enabled && task.core_id == current_core) {
				task.action();

				if (task.one_shot)
					task.enabled = false;
			}
		}

		// if (current_core == 0)
		// 	Debug::Pin2::low();
		// else
		// 	Debug::Pin1::low();
	});
	task_runner.start();
}

void pause_module_threads() {
	pause_module_threads(0);
	pause_module_threads(1);
}

void pause_module_threads(unsigned core_id) {
	auto &task_runner = core_id == 1 ? async_task_core1 : async_task_core0;
	task_runner.stop();
}

void resume_module_threads() {
	resume_module_threads(0);
	resume_module_threads(1);
}

void resume_module_threads(unsigned core_id) {
	auto &task_runner = core_id == 1 ? async_task_core1 : async_task_core0;
	task_runner.start();
}

void kill_module_threads() {
	async_task_core0.stop();
	async_task_core1.stop();
}

void peg_task_to_core(uint32_t module_id, uint32_t core_id) {
	for (auto &task : tasks) {
		if (task.module && task.module->id == module_id) {
			pr_trace("Peg task for module id %u: task id %u -> core %u\n", module_id, task.id, core_id);
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
