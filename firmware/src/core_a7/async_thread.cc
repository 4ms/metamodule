#include "CoreModules/async_thread.hh"
#include "async_thread_control.hh"
#include "drivers/stm32xx.h"

namespace MetaModule
{

struct AsyncThread::Internal {
	unsigned id = 0;
};

AsyncThread::AsyncThread()
	: internal{new Internal} {
}

AsyncThread::AsyncThread(Callback &&new_action)
	: action(std::move(new_action))
	, internal{new Internal} {
}

void AsyncThread::start(unsigned module_id) {
	if (auto task = get_task(internal->id)) {
		internal->id = module_id;

		task->action = action;
		__DSB();
		task->enabled = true;
		task->one_shot = false;
		__DSB();
	}
}

void AsyncThread::start(unsigned module_id, Callback &&new_action) {
	action = std::move(new_action);
	start(module_id);
}

void AsyncThread::run_once(unsigned module_id) {
	if (auto task = get_task(internal->id)) {
		internal->id = module_id;

		task->action = action;
		__DSB();
		task->enabled = true;
		task->one_shot = true;
		__DSB();
	}
}

void AsyncThread::stop() {
	if (auto task = get_task(internal->id)) {
		task->enabled = false;
		__DSB();
	}
}

AsyncThread::~AsyncThread() {
	stop();
}

} // namespace MetaModule
