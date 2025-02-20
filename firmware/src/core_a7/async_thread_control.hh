#pragma once
#include "util/callable.hh"

namespace MetaModule
{

void start_module_threads();
void pause_module_threads();
void kill_module_threads();

namespace Async
{

struct Task {
	Callback action;
	bool enabled = false;
	bool one_shot = false;
};

} // namespace Async

Async::Task *get_task(unsigned id);

} // namespace MetaModule
