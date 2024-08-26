#include "CoreModules/async_thread.hh"
#include "debug.hh"
#include "drivers/timekeeper.hh"
#include "util/zip.hh"
#include <array>
#include <optional>

namespace MetaModule
{

namespace //anonymous
{

constexpr int MAX_MODULES_IN_PATCH = 32;

struct Task {
	Callback action;
	bool enabled = false;
};

static std::array<Task, MAX_MODULES_IN_PATCH> tasks_core0;
static std::array<Task, MAX_MODULES_IN_PATCH> tasks_core1;

mdrivlib::Timekeeper async_task_core0;
mdrivlib::Timekeeper async_task_core1;

uint32_t core() {
	return (__get_MPIDR() & 0b1); //0 = CA7 Core 1, 1 = CA7 Core 2
}

// static std::optional<size_t> first_available_id() {
// 	auto &tasks = core() == 1 ? tasks_core1 : tasks_core0;
// 	unsigned i = 0;
// 	for (auto &task : tasks) {
// 		if (!task.enabled)
// 			return i;
// 		i++;
// 	}
// 	return std::nullopt;
// }

} // namespace

AsyncThread::AsyncThread() = default;

AsyncThread::AsyncThread(Callback &&new_action)
	: action(std::move(new_action)) {
}

void AsyncThread::start(unsigned module_id) {
	if (action && module_id > 0) {
		auto &tasks = core() == 1 ? tasks_core1 : tasks_core0;

		if (module_id < tasks.size()) {
			id = module_id;

			tasks[id].action = action;
			__DSB();
			tasks[id].enabled = true;
			__DSB();
		}
	}
}

void AsyncThread::start(unsigned module_id, Callback &&new_action) {
	action = std::move(new_action);
	start(module_id);
}

AsyncThread::~AsyncThread() {
	auto &tasks = core() == 1 ? tasks_core1 : tasks_core0;
	if (id < tasks.size()) {
		tasks[id].enabled = false;
		__DSB();
	}
}

void start_module_threads() {
	uint32_t current_core = core();
	auto &task_runner = current_core == 1 ? async_task_core1 : async_task_core0;

	mdrivlib::TimekeeperConfig task_config{
		.TIMx = current_core == 0 ? TIM7 : TIM6,
		.period_ns = mdrivlib::TimekeeperConfig::Hz(1000),
		.priority1 = 3,
		.priority2 = 3,
	};

	task_runner.init(task_config, []() {
		if (core() == 0)
			Debug::Pin2::high();
		else
			Debug::Pin3::high();

		auto &tasks = core() == 1 ? tasks_core1 : tasks_core0;

		for (auto &task : tasks) {
			if (task.enabled) {
				task.action();
			}
		}

		if (core() == 0)
			Debug::Pin2::low();
		else
			Debug::Pin3::low();
	});
	task_runner.start();
}

void pause_module_threads(unsigned core_id = core()) {
	auto &task_runner = core_id == 1 ? async_task_core1 : async_task_core0;
	task_runner.stop();
}

} // namespace MetaModule
