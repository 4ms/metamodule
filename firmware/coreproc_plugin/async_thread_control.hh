#pragma once
#include "CoreModules/CoreProcessor.hh"
#include "util/callable.hh"
#include <optional>

namespace MetaModule
{

void start_module_threads();
void pause_module_threads();
void pause_module_threads(unsigned core_id);
void resume_module_threads();
void resume_module_threads(unsigned core_id);
void kill_module_threads();

std::optional<uint32_t> create_async_task(CoreProcessor *module);
void destroy_async_task(uint32_t id);

void peg_task_to_core(uint32_t module_id, uint32_t core_id);

bool is_any_thread_executing();

namespace Async
{

struct Task {
	uint32_t id;

	Callback action;
	CoreProcessor *module = nullptr;
	uint32_t core_id = 0;
	bool enabled = false;
	bool one_shot = false;
};

} // namespace Async

Async::Task *get_task(unsigned id);

} // namespace MetaModule
