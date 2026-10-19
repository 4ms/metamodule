#include "coreproc_plugin/async_thread_control.hh"
#include "console/pr_dbg.hh"
#include "util/fixed_vector.hh"
#include <algorithm>
#include <cstdlib>
#include <optional>

// MP2 version of src/core_a7/async_thread_control.cc, without the task runners.
// FIXME: on MP1 a 2kHz timer interrupt on each A7 core runs the modules' async tasks. MP2 doesn't
// play patches yet, so the tasks are kept track of but never run.

namespace MetaModule
{

namespace
{

constexpr int MAX_TASKS = 64;

FixedVector<Async::Task, MAX_TASKS> tasks;

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
	if (auto idx = task_index(id))
		tasks.erase(*idx);
}

void start_module_threads() {
}

void pause_module_threads() {
}

bool is_any_thread_executing() {
	return false;
}

void pause_module_threads(unsigned core_id) {
}

void resume_module_threads() {
}

void resume_module_threads(unsigned core_id) {
}

void kill_module_threads() {
}

void peg_task_to_core(uint32_t module_id, uint32_t core_id) {
	for (auto &task : tasks) {
		if (task.module && task.module->id == module_id)
			task.core_id = core_id;
	}
}

Async::Task *get_task(unsigned id) {
	if (auto idx = task_index(id))
		return &tasks[*idx];
	else
		return nullptr;
}

} // namespace MetaModule
