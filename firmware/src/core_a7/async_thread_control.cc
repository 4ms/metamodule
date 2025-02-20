#include "async_thread_control.hh"
#include "drivers/timekeeper.hh"
#include <array>

namespace MetaModule
{

namespace
{

constexpr int MAX_MODULES_IN_PATCH = 64;

static std::array<Async::Task, MAX_MODULES_IN_PATCH> tasks_core0;
static std::array<Async::Task, MAX_MODULES_IN_PATCH> tasks_core1;

mdrivlib::Timekeeper async_task_core0;
mdrivlib::Timekeeper async_task_core1;

uint32_t core() {
	return (__get_MPIDR() & 0b1); //0 = CA7 Core 1, 1 = CA7 Core 2
}

} // namespace

void start_module_threads() {
	uint32_t current_core = core();
	auto &task_runner = current_core == 1 ? async_task_core1 : async_task_core0;

	mdrivlib::TimekeeperConfig task_config{
		.TIMx = current_core == 0 ? TIM7 : TIM6,
		.period_ns = mdrivlib::TimekeeperConfig::Hz(2000),
		.priority1 = 3,
		.priority2 = 3,
	};

	task_runner.init(task_config, []() {
		// if (core() == 0)
		// 	Debug::Pin2::high();
		// else
		// 	Debug::Pin1::high();

		auto &tasks = core() == 1 ? tasks_core1 : tasks_core0;

		for (auto &task : tasks) {
			if (task.enabled) {
				task.action();
				if (task.one_shot)
					task.enabled = false;
			}
		}

		// if (core() == 0)
		// 	Debug::Pin2::low();
		// else
		// 	Debug::Pin1::low();
	});
	task_runner.start();
}

void pause_module_threads(unsigned core_id = core()) {
	auto &task_runner = core_id == 1 ? async_task_core1 : async_task_core0;
	task_runner.stop();
}

void kill_module_threads() {
	async_task_core0.stop();
	async_task_core1.stop();
}

Async::Task *get_task(unsigned id) {
	if (id >= tasks_core0.size())
		return nullptr;
	else
		return (core() == 1) ? &tasks_core1[id] : &tasks_core0[id];
}

} // namespace MetaModule
